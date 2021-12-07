#include "jack.hpp"

#include "../alloc/heterogenous_allocator.hpp"
#include "../alloc/dllist.hpp"

#include <stdlib.h>

extern sfx::alloc::heterogenous_allocator_t* _main_allocator;

namespace sfx
{
  namespace jack
  {
    /// Implementation details
    namespace impl
    {
      template <typename pool_allocator_t>
      err_t alloc_pool(pool_allocator_t* allocator, size_t objsize, size_t poolsize)
      {
        size_t req_size = allocator->required_size(objsize, poolsize);
        uint8_t* memory = (uint8_t*)_main_allocator->alloc(req_size);
        if (nullptr == memory)
          return OutOfMemory;

        *allocator = pool_allocator_t(memory, objsize, poolsize);
        return Success;
      }

      template <typename pool_allocator_t>
      err_t free_pool(pool_allocator_t* allocator)
      {
        if (nullptr != allocator->raw_memory())
          if (0 != _main_allocator->free(allocator->raw_memory()))           {
            snprintf(sfx::errstr, sfx::errstr_size, "Free failure at free_pool %p", allocator);
            return (err_t)(sfx::errno = MemoryError);
          }
        *allocator = pool_allocator_t(nullptr);
        return Success;
      }

      struct graph_compute_helpers_t
      {
        
        using node_t = sfx::utils::dlnode_t<module_id_t>;
        using queue_t = sfx::utils::dllist_t<node_t>;
        using queue_allocator_t = sfx::alloc::pool_allocator_t<int8_t>;

        int8_t* ranks;
        int8_t rankmax;

        queue_t queue;
        queue_allocator_t qalloc;

        graph_compute_helpers_t() :
          ranks{ nullptr }, rankmax{ 0 }
        {
        }
        ~graph_compute_helpers_t()
        {
          if (ranks)
            _main_allocator->free(ranks);
          if (qalloc.raw_memory())
            free_pool(&qalloc);
        }

        err_t allocate(size_t max_modules_count, size_t nodes_pool_size)
        {
          ranks = (int8_t*)_main_allocator->alloc(max_modules_count * sizeof(int8_t));
          if (nullptr == ranks)
            return OutOfMemory;
          for (size_t i = 0; i < max_modules_count; ++i)
            ranks[i] = 0;

          err_t err;
          if (Success != (err = alloc_pool(&qalloc, sizeof(node_t), nodes_pool_size)))
            return OutOfMemory;

          return Success;
        }

        err_t add_to_todo(module_id_t module)
        {
          if (queue.begin() != queue.end() && queue.back() == module)
            return Success;

          node_t* node = (node_t*) qalloc.alloc();
          if (nullptr == node)
            return OutOfMemory;
          
          queue_t::init(node);
          node->obj = module;

          queue.push_back(node);

          return Success;
        }

        void set_rank(int8_t* ptr, int8_t rank)
        {
          if (*ptr < rank)
            *ptr = rank;
        }
        void set_rank(module_id_t module, int8_t rank)
        {
          set_rank(ranks + module, rank);
          set_rank(&rankmax, rank);
        }
      };
    }
    // namespace impl

    /// Methods

    err_t engine_t::init(size_t max_modules_count, size_t max_ports_count)
    {
      blocksize = 0;
      this->max_modules_count = max_modules_count;
      this->max_ports_count = max_ports_count;
      max_connections_count = max_ports_count;
      max_buffers_count = max_ports_count;

      err_t err;
      if ((err = impl::alloc_pool(&modules_allocator, sizeof(module_t), max_modules_count))
        || (err = impl::alloc_pool(&ports_allocator, sizeof(port_t), max_ports_count))
        || (err = impl::alloc_pool(&connections_allocator, sizeof(connection_t), max_connections_count))
        || (err = impl::alloc_pool(&buffers_allocator, 0, 0))
        )
        return err;

      process_order = (module_id_t*)_main_allocator->alloc(max_modules_count * sizeof(module_id_t));
      if (nullptr == process_order)
        return OutOfMemory;
      for (size_t i = 0; i < max_modules_count; ++i)
        process_order[i] = -1;

      return Success;
    }

    err_t engine_t::deinint()
    {
      err_t err;
      if ((err = impl::free_pool(&modules_allocator))
        || (err = impl::free_pool(&ports_allocator))
        || (err = impl::free_pool(&connections_allocator))
        || (err = impl::free_pool(&buffers_allocator)))
        return err;

      if (process_order)
        if (0 != _main_allocator->free(process_order))         {
          snprintf(sfx::errstr, sfx::errstr_size, "Free failure at free rocess order");
          return (err_t)(sfx::errno = MemoryError);
        }

      return Success;
    }

    err_t engine_t::set_blocksize(size_t blocksize)
    {
      blocksize = blocksize;

      err_t err;
      if ((err = impl::free_pool(&buffers_allocator)))
        return err;
      if ((err = impl::alloc_pool(&buffers_allocator, sizeof(buffer_t) + blocksize, max_buffers_count)))
        return err;

      return realloc_buffers();
    }

    err_t engine_t::realloc_buffers()
    {
      buffers_allocator.clear();

      // Alloc one buffer for each output port
      for (auto itr = ports_allocator.begin(); itr != ports_allocator.end(); ++itr)       {
        port_t* port = itr.get<port_t>();

        if (port->descriptor->flags & PortIsPhysical)
        {
          port->buffer = &physical_buffers[port->descriptor->pid];
          continue;
        }

        if (port->descriptor->flags & PortIsOutput)
        {
          uint8_t* rawmem = (uint8_t*) buffers_allocator.alloc();
          if (nullptr == rawmem)
            return OutOfMemory;

          port->buffer = (buffer_t*) rawmem;
          port->buffer->samples = (float*) &rawmem[sizeof(buffer_t)];
        }
        else
        {
          port->buffer = nullptr;
        }
      }

      // Then apply connections
      for (auto itr = connections_allocator.begin(); itr != connections_allocator.end(); ++itr)
        for (connection_t* con = itr.get<connection_t>(); con != nullptr; con = con->next)         {
          port_t* src = (port_t*)ports_allocator.get(con->src);
          port_t* dst = (port_t*)ports_allocator.get(con->dst);
          if (dst->descriptor->flags & PortIsPhysical && dst->descriptor->flags & PortIsInput)
            src->buffer = dst->buffer;
          else
            dst->buffer = src->buffer;
        }

      return Success;
    }

    err_t engine_t::recompute_process_graph()
    {
      err_t err;
      {
        // List of rank for each module
        size_t modules_count = modules_allocator.used_slots_count();
        impl::graph_compute_helpers_t helpers;

        if (Success != (err = helpers.allocate(max_modules_count, modules_count * 2)))
          return err;

        // Initialisation : fill the todo list with all modules
        //  owning a physical output port
        for (auto itr = ports_allocator.begin(); itr != ports_allocator.end(); ++itr)         {
          const port_t* port = itr.get<port_t>();
          if (port->descriptor->flags & PortIsPhysical)           {
            if (port->descriptor->flags & PortIsInput)             {
              module_id_t module_idx = port->module->uid;
              if (Success != (err = helpers.add_to_todo(module_idx)))
                return err;
              helpers.set_rank(module_idx, 1);
            }
          }
        }
      
        auto dump_status = [&](){
          fprintf(stderr, "\n==================\nGraph Computation Dump\n");
          for (auto itr = modules_allocator.begin(); itr != modules_allocator.end(); ++itr)
          {
            const module_t* m = itr.get<module_t>();
            fprintf(stderr, "\tModule : %d : rank : %d\n", m->uid, helpers.ranks[m->uid]);
          }
          fprintf(stderr, "\tTODO List : ");
          for (auto node = helpers.queue.begin(); node != helpers.queue.end(); node = node->next)
          {
            fprintf(stderr, "%d -> ", node->obj);
          }
          fprintf(stderr, "-1\n");

          fprintf(stderr, "\tRankmax : %d\n", helpers.rankmax);

          fprintf(stderr, "==================\n");
        };

        dump_status();

        // Algorithm : while todo list not empty :
        //  For each input port connected :
        //    Add target module to the todo list
        //    set it's rank to max(target rank, module rank + 1)
        while (helpers.queue.begin() != helpers.queue.end())         {
          auto node = helpers.queue.begin();
          module_id_t module_index = node->obj;
          int8_t module_rank = helpers.ranks[module_index];

          if (max_modules_count < (size_t)helpers.rankmax)
            RETURN_ERROR(Failure, "Graph computation failure, rankmax overflow at module %d", module_index);

          fprintf(stderr, "Processing Module %d ... ", module_index);

          const module_t* module = (const module_t*)modules_allocator.get(module_index);

          for (const port_t* port = module->ports; port != nullptr; port = port->next)
            if (port->descriptor->flags & PortIsInput)             {
              const connection_t* con = port->connections;
              if (nullptr == con)
                continue;
              const port_t* target = (const port_t*)ports_allocator.get(con->src);
              module_id_t target_index = target->module->uid;

              if (Success != (err = helpers.add_to_todo(target_index)))
                return err;

              helpers.set_rank(target_index, module_rank + 1);
            }
          dump_status();
          
          impl::graph_compute_helpers_t::queue_t::extract(node);
          if (0 != helpers.qalloc.free(node))           {
            snprintf(sfx::errstr, sfx::errstr_size, "Free failure at free node");
            return (err_t)(sfx::errno = MemoryError);
          }

          fprintf(stderr, "Done\n");
          dump_status();
        }

        // Prepare final list
        for (size_t i = 0; i < max_modules_count; ++i)
          process_order[i] = -1;

        // At this state each module was assignated a rank
        //  giving a reverse order for processing
        // So we will sort them to generate future queue
        size_t cptr = 0;
        for (int8_t rank = helpers.rankmax; 0 < rank; --rank)
          for (auto itr = modules_allocator.begin(); itr != modules_allocator.end(); ++itr)           {
            const module_t* module = itr.get<module_t>();
            int8_t module_rank = helpers.ranks[module->uid];
            if (rank == module_rank)             {
              process_order[cptr] = module->uid;
              cptr += 1;
            }
          }
        if (modules_count < cptr)         {
          snprintf(sfx::errstr, sfx::errstr_size, "Graph algorithm failure");
          return (err_t)(sfx::errno = InvalidState);
        }

        // Null terminate the list
        if (cptr < max_modules_count)
          process_order[cptr] = -1;

        if (Success != (err = realloc_buffers()))
          return err;
      }
      _main_allocator->optimize_memory();
      return Success;
    }

    module_t* engine_t::create_module(const module_descriptor_t* desc)
    {
      module_t* module = (module_t*)modules_allocator.alloc();
      if (nullptr == module)
        return nullptr;
      else       {
        module->descriptor = desc;

        module->ports = nullptr;
        module->uid = modules_allocator.indexof(module);

        module->args = nullptr;
        return module;
      }
    }
    err_t engine_t::destroy_module(module_t* module)
    {
      for (port_t* tmp = module->ports; tmp != nullptr; tmp = module->ports)
        if (err_t err = destroy_port(tmp); Success != err)
          return err;
      if (0 != modules_allocator.free(module))
        return MemoryError;
      return Success;
    }

    port_t* engine_t::create_port(module_t* module, const port_descriptor_t* desc)
    {
      port_t* port = (port_t*)ports_allocator.alloc();
      if (nullptr == port)
        return nullptr;
      else       {
        port->descriptor = desc;

        port->buffer = nullptr;
        port->module = module;
        port->uid = ports_allocator.indexof(port);

        port->connections = nullptr;
        port_t** link;
        for (link = &(module->ports); *link != nullptr; link = &((*link)->next))           { /* empty body */
        }
        *link = port;

        return port;
      }
    }
    err_t engine_t::destroy_port(port_t* port)
    {
      port_t** link;
      for (
        link = &(port->module->ports);
        *link != port && *link != nullptr;
        link = &((*link)->next))       { /* empty body */
      }
      if (nullptr == *link)
        return InvalidState;

      *link = port->next;
      ports_allocator.free(port);

      return Success;
    }

    err_t engine_t::connect(port_t* src, port_t* dst)
    {
      if (nullptr == src || nullptr == dst)
        return InvalidArguments;

      if ((src->descriptor->flags & PortIsPhysical)
        && (dst->descriptor->flags & PortIsPhysical))
        return IllegalConnection;
      if (!(src->descriptor->flags & PortIsOutput)
        || !(dst->descriptor->flags & PortIsInput))
        return IllegalConnection;

      // Only one connection is allowed for input ports
      if (nullptr != dst->connections)
        return InputPortAlreadyConnected;

      // Avoid duplicate connections
      connection_t** tmp;
      for (tmp = &src->connections; *tmp != nullptr; tmp = &(*tmp)->next)
        if ((*tmp)->dst == src->uid)
          return ExistingConnection;

      // Alloc a new handle and populate it
      connection_t* newcon = (connection_t*)connections_allocator.alloc();
      if (nullptr == newcon)
        return OutOfMemory;

      newcon->src = src->uid;
      newcon->dst = dst->uid;
      newcon->next = nullptr;

      // Append the connection at the end of linked list
      *tmp = newcon;
      dst->connections = newcon;

      return Success;
    }
    err_t engine_t::disconnect(port_t* src, port_t* dst)
    {
      if (nullptr == src || nullptr == dst)
        return InvalidArguments;

      connection_t* conn = dst->connections;
      if (nullptr == conn || conn->src != src->uid || conn->dst != dst->uid)
        return PortsNotConnected;

      // Search for the connection in src's list
      connection_t** tmp;
      for (tmp = &src->connections; *tmp != nullptr && *tmp != conn; tmp = &(*tmp)->next)         { /* empty loop body */
      }
      if (nullptr == *tmp)
        return InvalidState; // Holly shit ... connections linked list is broken ...

      // remove the connection and free memory
      *tmp = conn->next;
      dst->connections = nullptr;
      if (0 != connections_allocator.free(conn))
        RETURN_ERROR(MemoryError, "Free failure at disconnect");

      // done
      return Success;
    }

    err_t engine_t::process_callback(const float* const* physical_in, float** physical_out)
    {
      // Fill physical buffers
      float* pio[4] = { const_cast<float*>(physical_in[0]), const_cast<float*>(physical_in[1]),physical_out[0], physical_out[1] };
      for (size_t i = 0; i < 4; ++i)
          physical_buffers[i].samples = pio[i];

      // Call each modules of the process graph
      for (size_t i = 0; i < max_modules_count && process_order[i] != -1; ++i)
      {
        module_t* module = (module_t*)modules_allocator.get(process_order[i]);
        int err;
        if (0 != (err = module->descriptor->callback(module)))
          RETURN_ERROR(ModuleProcessFailed, "Module %d failed : code %d", module->uid, err);
      }
      return Success;
    }
  }
  // namespace jack
}
// namespace sfx
