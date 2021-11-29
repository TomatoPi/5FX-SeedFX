#pragma once

#include "../alloc/object_pool_allocator.hpp"
#include "err/err.hpp"
#include "defs.hpp"

namespace sfx
{
  namespace jack
  {

    class engine {
    public:

      sfx::alloc::pool_allocator_t<int8_t> modules_allocator;
      sfx::alloc::pool_allocator_t<int8_t> ports_allocator;
      sfx::alloc::pool_allocator_t<int8_t> connections_allocator;
      sfx::alloc::pool_allocator_t<int8_t> buffers_allocator;

      size_t blocksize;

      size_t max_modules_count;
      size_t max_ports_count;
      size_t max_connections_count;
      size_t max_buffers_count;

    public :

      err_t init(size_t max_modules_count, size_t max_ports_count);
      err_t deinint();

      err_t set_blocksize(size_t blocksize);
      
      err_t recompute_process_graph();

      module_t* create_module(const module_descriptor_t* desc);
      err_t destroy_module(module_t* module);

      port_t* create_port(module_t* module, const port_descriptor_t* desc);
      err_t destroy_port(port_t* port);

      err_t connect(port_id_t src, port_id_t dest);
      err_t disconnect(port_id_t src, port_id_t dest);

      err_t process_callback(const float* const* physical_in, float** physical_out);
    };
  }
  // namespace jack
}
// namespace sfx
