#pragma once

#include <stddef.h>
#include <stdint.h>

namespace sfx
{
  namespace jack
  {
    /// Forward declarations

    struct module_t;

    using port_id_t = int8_t;
    using module_id_t = int8_t;

    /// Descriptors, used to tell jack what is what

    enum port_flags_e {
      PORT_NONE         = 0x00,
      PORT_IS_INPUT     = 0x01,
      PORT_IS_OUTPUT    = 0x02,
      PORT_IS_TERMINAL  = 0x04,
      PORT_IS_PHYSICAL  = 0x08,
    };
  
    struct port_descriptor_t {
      const char* name;
      int flags;
    };

    struct module_descriptor_t {
      const char* name;
      int (*callback)(module_t*);
    };

    /// Concrete objects manipulated by outside code

    struct buffer_t {
      float* samples;
    };

    struct connection_t {
      port_id_t     src;
      port_id_t     dst;
      connection_t* next;
    };

    struct port_t {
      const port_descriptor_t* descriptor;

      buffer_t* buffer;
      module_t* module;

      port_id_t uid;

      connection_t* connections;
      port_t*       next;
    };
    
    struct module_t {
      const module_descriptor_t* descriptor;
      
      port_t*  ports;
      module_id_t uid;

      void*       args;
    };
  }
  // namespace jack
}
// namespace sfx