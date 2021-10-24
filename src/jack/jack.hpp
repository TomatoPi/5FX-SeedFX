#pragma once

#include "defs.hpp"

namespace sfx
{
  namespace jack
  {
    enum result_e {
      Success = 0,

      OutOfMemory,
      MemoryError,
      InvalidState,

      InvalidArguments,

      IllegalConnection,
      InputPortAlreadyConnected,
      ExistingConnection,

      PortsNotConnected,
    };

    result_e init(size_t max_modules_count, size_t max_ports_count);
    result_e deinint();

    result_e set_blocksize(size_t blocksize);
    
    result_e recompute_process_graph();

    module_t* create_module(const module_descriptor_t* desc);
    result_e destroy_module(module_t* module);

    port_t* create_port(module_t* module, const port_descriptor_t* desc);
    result_e destroy_port(port_t* port);

    result_e connect(port_id_t src, port_id_t dest);
    result_e disconnect(port_id_t src, port_id_t dest);

    result_e process_callback(const float* const* physical_in, float** physical_out);
  }
  // namespace jack
}
// namespace sfx
