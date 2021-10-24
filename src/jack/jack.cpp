#include "jack.hpp"

#include "../alloc/object_pool_allocator.hpp"
#include "../alloc/heterogenous_allocator.hpp"

#include <stdlib.h>

extern sfx::alloc::heterogenous_allocator_t* _main_allocator;

namespace 
{
  sfx::alloc::pool_allocator_t<int8_t> _jack_ports_allocator;
  sfx::alloc::pool_allocator_t<int8_t> _jack_connections_allocator;
  sfx::alloc::pool_allocator_t<int8_t> _jack_buffers_allocator;

  size_t _blocksize;
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
      struct connection_t;

      struct port_t {
        union {
          input_port_t in;
          output_port_t out;
        };

        const port_descriptor_t* descriptor;
      };

      static_assert(offsetof(port_t, in) == 0);
      static_assert(offsetof(port_t, out) == 0);

      struct connection_t {
        output_port_t* src;
        input_port_t* dst;
      };

      struct buffer_t {

      };

      template <typename pool_allocator_t>
      int alloc_pool(pool_allocator_t* allocator, size_t objsize, size_t poolsize)
      {
        size_t req_size = allocator->required_size(objsize, poolsize);
        uint8_t* memory = (uint8_t*) _main_allocator->alloc(req_size);
        if (nullptr == memory)
          return -1;
        *allocator = pool_allocator_t(memory, objsize, poolsize);
        return 0;
      }

      int realloc_buffers()
      {
        return 0;
      }
    }
    // namespace impl

    /// Methods

    int init(size_t max_ports_count)
    {
      _blocksize = 0;
      _max_ports_count = max_ports_count;
      _max_connections_count = max_ports_count;
      _max_buffers_count = _max_ports_count;

      int err;
      if ( (err = impl::alloc_pool(&_jack_ports_allocator, sizeof(impl::port_t), _max_ports_count))
        || (err = impl::alloc_pool(&_jack_connections_allocator, sizeof(impl::connection_t), _max_connections_count))
        )
        return err;
      
      return 0;
    }

    int set_blocksize(size_t blocksize)
    {
      _blocksize = blocksize;
      int err;
      if ((err = impl::alloc_pool(&_jack_buffers_allocator, sizeof(impl::buffer_t), _max_buffers_count)))
        return err;
      return impl::realloc_buffers();
    }
    
    int recompute_process_graph()
    {
      return 0;
    }

    module_t* create_module(const module_descriptor_t* desc)
    {
      return 0;
    }
    int destroy_module(module_t* module)
    {
      return 0;
    }

    int connect(output_port_t* src, input_port_t* dest)
    {
      return 0;
    }
    int disconnect(output_port_t* src, output_port_t* dest)
    {
      return 0;
    }

    int process_callback(const float* const* physical_in, float** physical_out)
    {
      return 0;
    }
  }
  // namespace jack
}
// namespace sfx
