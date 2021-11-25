#pragma once

#include <stddef.h>

namespace sfx
{
  namespace granulator
  {
    struct grain {
      const float* samples;
      size_t nsamples;
    };
  }
  // namespace granulator
}
// namespace sfx