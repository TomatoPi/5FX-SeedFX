#pragma once

#include <stddef.h>

namespace sfx
{
  static constexpr size_t errstr_size = 1024;

  extern int errno;
  extern char errstr[errstr_size];

  enum err_t {
    Success = 0,
    Failure,

    OutOfMemory,
    MemoryError,
    InvalidState,

    InvalidArguments,

    IllegalConnection,
    InputPortAlreadyConnected,
    ExistingConnection,

    PortsNotConnected,

    ModuleProcessFailed,
  };

  const char* errname(err_t err);
}
// namespace sfx