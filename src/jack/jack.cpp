#include "jack.hpp"

#include "../alloc/object_pool_allocator.hpp"
#include "../alloc/heterogenous_allocator.hpp"

#include <stdlib.h>

extern sfx::alloc::heterogenous_allocator_t* _main_allocator;

namespace 
{
  sfx::alloc::pool_allocator_t<int8_t> _jack_modules_allocator;
  sfx::alloc::pool_allocator_t<int8_t> _jack_ports_allocator;
  sfx::alloc::pool_allocator_t<int8_t> _jack_connections_allocator;
  sfx::alloc::pool_allocator_t<int8_t> _jack_buffers_allocator;

  size_t _blocksize;

  size_t _max_modules_count;
  size_t _max_ports_count;
  size_t _max_connections_count;
  size_t _max_buffers_count;
}

namespace sfx
{
  namespace jack
  {
    /// Implementation details
    namespace impl
    {
      template <typename pool_allocator_t>
      result_e alloc_pool(pool_allocator_t* allocator, size_t objsize, size_t poolsize)
      {
        size_t req_size = allocator->required_size(objsize, poolsize);
        uint8_t* memory = (uint8_t*) _main_allocator->alloc(req_size);
        if (nullptr == memory)
          return OutOfMemory;

        *allocator = pool_allocator_t(memory, objsize, poolsize);
        return Success;
      }

      template <typename pool_allocator_t>
      result_e free_pool(pool_allocator_t* allocator)
      {
        if (nullptr != allocator.raw_memory())
          if (0 != _main_allocator->free(allocator.raw_memory()))
            return MemoryError;
        allocator = pool_allocator_t(nullptr);
        return Success;
      }

      result_e realloc_buffers()
      {
        return Success;
      }
    }
    // namespace impl

    /// Methods

    result_e init(size_t max_modules_count, size_t max_ports_count)
    {
      _blocksize = 0;
      _max_modules_count = max_modules_count;
      _max_ports_count = max_ports_count;
      _max_connections_count = max_ports_count;
      _max_buffers_count = _max_ports_count;

      result_e err;
      if ( (err = impl::alloc_pool(&_jack_modules_allocator, sizeof(module_t), _max_modules_count))
        || (err = impl::alloc_pool(&_jack_ports_allocator, sizeof(port_t), _max_ports_count))
        || (err = impl::alloc_pool(&_jack_connections_allocator, sizeof(connection_t), _max_connections_count))
        || (err = impl::alloc_pool(&_jack_buffers_allocator, 0, 0))
        )
        return err;
      
      return Success;
    }

    result_e deinint()
    {
      result_e err;
      if ( (err = impl::free_pool(&_jack_modules_allocator))
        || (err = impl::free_pool(&_jack_ports_allocator))
        || (err = impl::free_pool(&_jack_connections_allocator))
        || (err = impl::free_pool(&_jack_buffers_allocator)))
        return err;
      else
        return Success;
    }

    result_e set_blocksize(size_t blocksize)
    {
      _blocksize = blocksize;

      if (nullptr != _jack_buffers_allocator.raw_memory())
        if (0 != _main_allocator->free(_jack_buffers_allocator.raw_memory()))
          return MemoryError;

      result_e err;
      if ((err = impl::alloc_pool(&_jack_buffers_allocator, sizeof(buffer_t) + blocksize, _max_buffers_count)))
        return err;

      return impl::realloc_buffers();
    }
    
    result_e recompute_process_graph()
    {
      // Meh, complex things here
      return Success;
    }

    module_t* create_module(const module_descriptor_t* desc)
    {
      return nullptr;
    }
    result_e destroy_module(module_t* module)
    {
      return Success;
    }

    port_t* create_port(module_t* module, const port_descriptor_t* desc)
    {
      return nullptr;
    }
    result_e destroy_port(port_t* port)
    {
      return Success;
    }

    result_e connect(port_id_t id_src, port_id_t id_dst)
    {
      port_t* src = (port_t*) _jack_ports_allocator.get(id_src);
      port_t* dst = (port_t*) _jack_ports_allocator.get(id_dst);
      if (nullptr == src || nullptr == dst)
        return InvalidArguments;

      if (src->descriptor->is_physical && dst->descriptor->is_physical)
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
      connection_t* newcon = (connection_t*) _jack_connections_allocator.alloc();
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
    result_e disconnect(port_id_t id_src, port_id_t id_dst)
    {
      port_t* src = (port_t*) _jack_ports_allocator.get(id_src);
      port_t* dst = (port_t*) _jack_ports_allocator.get(id_dst);
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
      if (0 != _jack_connections_allocator.free(conn))
        return MemoryError;

      // done
      return Success;
    }

    result_e process_callback(const float* const* physical_in, float** physical_out)
    {
      // Call each modules of the process graph
      return Success;
    }
  }
  // namespace jack
}
// namespace sfx
