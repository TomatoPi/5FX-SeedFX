#pragma once

#include <stddef.h>

namespace sfx
{
  namespace jack
  {
    /// Forward declarations

    struct port_t;
    struct input_port_t;
    struct output_port_t;

    struct module_t;

    /// Descriptors, used to tell jack what is what

    struct port_descriptor_t {
      const char* name;
      bool is_physical;
      bool is_terminal;
      bool is_input;

      port_descriptor_t* next;
    };

    struct module_descriptor_t {
      const char*               name;
      const port_descriptor_t** ports;
      size_t                    nports;

      int (*callback)(module_t*);
    };

    /// Concrete objects manipulated by outside code

    struct input_port_t {
      const float*  buffer;
      input_port_t* next;
    };

    struct output_port_t {
      float*          buffer;
      output_port_t*  next;
    };

    struct module_t {
      const module_descriptor_t* descriptor;
      
      input_port_t*   inputs_lst;
      output_port_t*  outputs_lst;

      void* args;

      size_t uid;
    };
  }
  // namespace jack
}
// namespace sfx