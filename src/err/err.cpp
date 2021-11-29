#include "err.hpp"

namespace sfx
{
  int errno = 0;
  char errstr[errstr_size] = "";

  const char* errname(err_t err)
  {
    switch (err)
    {
      case Success : return "Success";

      case OutOfMemory : return "OutOfMemory";
      case MemoryError : return "MemoryError";
      case InvalidState : return "InvalidState";
      
      case InvalidArguments : return "InvalidArguments";
      
      case IllegalConnection : return "IllegalConnection";
      case InputPortAlreadyConnected : return "InputPortAlreadyConnected";
      case ExistingConnection : return "ExistingConnection";
      
      case PortsNotConnected : return "PortsNotConnected";

      default : return "Unkown Error";
    }
  }
}