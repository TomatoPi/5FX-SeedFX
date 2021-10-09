#pragma once

#include "serial.hpp"
#include <stdint.h>

namespace sfx
{
  namespace hw
  {
    struct device_descriptor {
      uint8_t uuid;
      uint8_t version;

      uint8_t model_name_length : 4;
      uint8_t _ : 4;

      const char* model_name;
      
      static uint8_t sizeof_name(const device_descriptor* desc)
        { return desc->model_name_length; }
    };

    template <>
    const layout_descriptor* layout_of<device_descriptor>()
    {
      static layout_descriptor blk1 { 3, 0, (size_t(*)(void*)) &device_descriptor::sizeof_name, true, nullptr };

      static layout_descriptor blk0 { 0, 3, nullptr, false, &blk1 };
      return &blk0;
    }
  }
  // namespace hw
}
// namespace sfx