#include "jack.hpp"

#include "../alloc/heterogenous_allocator.hpp"

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
        uint8_t* memory = (uint8_t*) _main_allocator->alloc(req_size);
        if (nullptr == memory)
          return OutOfMemory;

        *allocator = pool_allocator_t(memory, objsize, poolsize);
        return Success;
      }

      template <typename pool_allocator_t>
      err_t free_pool(pool_allocator_t* allocator)
      {
        if (nullptr != allocator->raw_memory())
          if (0 != _main_allocator->free(allocator->raw_memory()))
            return MemoryError;
        *allocator = pool_allocator_t(nullptr);
        return Success;
      }

      err_t realloc_buffers()
      {
        return Success;
      }
    }
    // namespace impl

    /// Methods

    err_t engine::init(size_t max_modules_count, size_t max_ports_count)
    {
      blocksize = 0;
      this->max_modules_count = max_modules_count;
      this->max_ports_count = max_ports_count;
      max_connections_count = max_ports_count;
      max_buffers_count = max_ports_count;

      err_t err;
      if ( (err = impl::alloc_pool(&modules_allocator, sizeof(module_t), max_modules_count))
        || (err = impl::alloc_pool(&ports_allocator, sizeof(port_t), max_ports_count))
        || (err = impl::alloc_pool(&connections_allocator, sizeof(connection_t), max_connections_count))
        || (err = impl::alloc_pool(&buffers_allocator, 0, 0))
        )
        return err;
      
      return Success;
    }

    err_t engine::deinint()
    {
      err_t err;
      if ( (err = impl::free_pool(&modules_allocator))
        || (err = impl::free_pool(&ports_allocator))
        || (err = impl::free_pool(&connections_allocator))
        || (err = impl::free_pool(&buffers_allocator)))
        return err;
      else
        return Success;
    }

    err_t engine::set_blocksize(size_t blocksize)
    {
      blocksize = blocksize;

      if (nullptr != buffers_allocator.raw_memory())
        if (0 != _main_allocator->free(buffers_allocator.raw_memory()))
          return MemoryError;

      err_t err;
      if ((err = impl::alloc_pool(&buffers_allocator, sizeof(buffer_t) + blocksize, max_buffers_count)))
        return err;

      return impl::realloc_buffers();
    }
    
    err_t engine::recompute_process_graph()
    {
      // Meh, complex things here
      return Success;
    }

    module_t* engine::create_module(const module_descriptor_t* desc)
    {
      module_t* module = (module_t*) modules_allocator.alloc();
      if (nullptr == module)
        return nullptr;
      else
      {
        module->descriptor = desc;
        
        module->ports = nullptr;
        module->uid = modules_allocator.indexof(module);
        
        module->args = nullptr;
        return module;
      }
    }
    err_t engine::destroy_module(module_t* module)
    {
      for (port_t* tmp = module->ports ; tmp != nullptr ; tmp = module->ports)
        if (err_t err = destroy_port(tmp); Success != err)
          return err;
      if (0 != modules_allocator.free(module))
        return MemoryError;
      return Success;
    }

    port_t* engine::create_port(module_t* module, const port_descriptor_t* desc)
    {
      port_t* port = (port_t*) ports_allocator.alloc();
      if (nullptr == port)
        return nullptr;
      else
      {
        port->descriptor = desc;

        port->buffer = nullptr;
        port->module = module;
        port->uid = ports_allocator.indexof(port);

        port->connections = nullptr;
        port_t** link;
        for (link = &(module->ports) ; *link != nullptr ; link = &((*link)->next))
          { /* empty body */ }
        *link = port;

        return port;
      }
    }
    err_t engine::destroy_port(port_t* port)
    {
      port_t** link;
      for (
        link = &(port->module->ports) ;
        *link != port && *link != nullptr ;
        link = &((*link)->next))
      { /* empty body */ }
      if (nullptr == *link)
        return InvalidState;

      *link = port->next;
      ports_allocator.free(port);

      return Success;
    }

    err_t engine::connect(port_id_t id_src, port_id_t id_dst)
    {
      port_t* src = (port_t*) ports_allocator.get(id_src);
      port_t* dst = (port_t*) ports_allocator.get(id_dst);
      if (nullptr == src || nullptr == dst)
        return InvalidArguments;

      if ((src->descriptor->flags & PORT_IS_PHYSICAL) 
        && (dst->descriptor->flags & PORT_IS_PHYSICAL))
        return IllegalConnection;
      if (!(src->descriptor->flags & PORT_IS_OUTPUT)
        || !(dst->descriptor->flags & PORT_IS_INPUT))
        return IllegalConnection;
      
      // Only one connection is allowed for input ports
      if (nullptr != dst->connections)
        return InputPortAlreadyConnected;
      
      // Avoid duplicate connections
      connection_t** tmp;
      for (tmp = &src->connections ; *tmp != nullptr ; tmp = &(*tmp)->next)
        if ((*tmp)->dst == id_dst)
          return ExistingConnection;

      // Alloc a new handle and populate it
      connection_t* newcon = (connection_t*) connections_allocator.alloc();
      if (nullptr == newcon)
        return OutOfMemory;

      newcon->src = id_src;
      newcon->dst = id_dst;
      newcon->next = nullptr;

      // Append the connection at the end of linked list
      *tmp = newcon;
      dst->connections = newcon;
        
      return Success;
    }
    err_t engine::disconnect(port_id_t id_src, port_id_t id_dst)
    {
      port_t* src = (port_t*) ports_allocator.get(id_src);
      port_t* dst = (port_t*) ports_allocator.get(id_dst);
      if (nullptr == src || nullptr == dst)
        return InvalidArguments;

      connection_t* conn = dst->connections;
      if (nullptr == conn || conn->src != id_src || conn->dst != id_dst)
        return PortsNotConnected;

      // Search for the connection in src's list
      connection_t** tmp;
      for (tmp = &src->connections ; *tmp != nullptr && *tmp != conn ; tmp = &(*tmp)->next)
        { /* empty loop body */ }
      if (nullptr == *tmp)
        return InvalidState; // Holly shit ... connections linked list is broken ...

      // remove the connection and free memory
      *tmp = conn->next;
      dst->connections = nullptr;
      if (0 != connections_allocator.free(conn))
        return MemoryError;

      // done
      return Success;
    }

    err_t engine::process_callback(const float* const* physical_in, float** physical_out)
    {
      // Call each modules of the process graph
      return Success;
    }
  }
  // namespace jack
}
// namespace sfx
