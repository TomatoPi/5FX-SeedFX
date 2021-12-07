#include "io.hpp"

namespace sfx
{
  namespace jack
  {
    namespace io
    {
      err_t Handler::save(const engine_t* jack)
      {
        for (const auto& module : jack->modules_allocator)
        {
          
        }
        return Success;
      }
      err_t Handler::load(engine_t* jack)
      {
        return Success;
      }

      err_t Handler::save(const module_t* module)
      {
        return Success;
      }
      err_t Handler::load(module_t* module)
      {
        return Success;
      }

      err_t Handler::save(const port_t* port)
      {
        return Success;
      }
      err_t Handler::load(port_t* port)
      {
        return Success;
      }
      
      err_t Handler::save(const connection_t* con)
      {
        return Success;
      }
      err_t Handler::load(connection_t* con)
      {
        return Success;
      }
    }
  }
}