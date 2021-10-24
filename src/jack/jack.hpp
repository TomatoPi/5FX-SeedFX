#pragma once

#include "defs.hpp"

namespace sfx
{
  namespace jack
  {
    int init(size_t max_ports_count);

    int set_blocksize(size_t blocksize);
    
    int recompute_process_graph();

    module_t* create_module(const module_descriptor_t* desc);
    int destroy_module(module_t* module);

    int connect(output_port_t* src, input_port_t* dest);
    int disconnect(output_port_t* src, output_port_t* dest);

    int process_callback(const float* const* physical_in, float** physical_out);
  }
  // namespace jack
}
// namespace sfx
