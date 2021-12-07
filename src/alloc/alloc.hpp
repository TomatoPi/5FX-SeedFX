#pragma once

#include "../err/err.hpp"

#include <stddef.h>
#include <string.h>
#include <stdio.h>

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

    inline void out_of_memory(allocator_i* alloc, size_t requested, size_t available)
    {
      sfx::errno = sfx::OutOfMemory;
      snprintf(sfx::errstr, sfx::errstr_size, "%p : Requested %lu bytes of %lu availables", alloc, requested, available);
    }
  }
  // namespace alloc
}
// namespace sfx
