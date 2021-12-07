#pragma once

#include "jack.hpp"

namespace sfx
{
  namespace jack
  {
    namespace io
    {
      enum object_type_t {
        UnknownType = 0,

        Module,
        Port,
        Connection,

        Engine,
      };

      class Handler {
      public:
        virtual err_t read_next(void* buffer, object_type_t* type) = 0;
        virtual err_t write(void* object, object_type_t type) = 0;

        err_t save(const engine_t* jack);
        err_t load(engine_t* jack);

        err_t save(const module_t* module);
        err_t load(module_t* module);

        err_t save(const port_t* port);
        err_t load(port_t* port);
        
        err_t save(const connection_t* con);
        err_t load(connection_t* con);
      };
    }
    // namespace io
  }
  // namespace jack
}
// namespace sfx