#pragma once

#include <stddef.h>

namespace sfx
{
  namespace jack
  {
    enum error {
      Success = 0,
      InvalidConnection = -1,
    };

    struct port_descriptor_t {
      const char* name;
      bool is_physical;
      bool is_terminal;
    };

    struct input_port_t {
      const port_descriptor_t* descriptor;
      const float*             buffer;
    };

    struct output_port_t {
      const port_descriptor_t* descriptor;
      float*                   buffer;
    };

    bool is_connected_to(const output_port_t* src, const input_port_t* dst)
    {
      return src->buffer == dst->buffer;
    }

    int connect(output_port_t* src, input_port_t* dst)
    {
      if (src->descriptor->is_physical && dst->descriptor->is_physical)
      {
        return InvalidConnection;
      }
      else if (dst->descriptor->is_physical)
      {
        src->buffer = const_cast<float*>(dst->buffer);
        return Success;
      }
      else
      {
        dst->buffer = src->buffer;
        return Success;
      }
    }

    struct module_descriptor_t {
      const char* name;
      void*       default_settings;
      size_t      sizeof_settings;
    };

    struct module_t {

      const module_descriptor_t* descriptor;

      int (*callback)(module_t*);

      input_port_t*   inputs;
      output_port_t*  outputs;
      void*           settings;

      size_t ninputs;
      size_t noutputs;
      size_t sizeof_settings;
    };

    class graph_t {
    public:


    };
  }
  // namespace jack
}
// namespace sfx