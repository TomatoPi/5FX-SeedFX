#pragma once

#include <stddef.h>

namespace sfx
{
  namespace alloc
  {
    class allocator_i {
    public:
      virtual void* alloc(size_t size) = 0;
      virtual int free(void* ptr) = 0;
      virtual void clear() = 0;
    };
  }
  // namespace alloc
}
// namespace sfx
