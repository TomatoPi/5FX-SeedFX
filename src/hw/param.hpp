#pragma once

#include "serial.hpp"
#include <stdint.h>

namespace sfx
{
  namespace hw
  {
    /// Serialisable bitfield describing a device's param
    struct param_descriptor {

      struct Types {
        enum : uint8_t {
          Void      = 0,  // Trigger values
          Bool      = 1,  // 0 or 1 stored on uint8_t
          Uint8     = 2,  // 8bits unsigned integer
          Integer   = 2,  // 32bits signed integer
          Float     = 3,  // 32bits floating point value
          Gain      = 4,  // 32bits floating point value with log10 scale
          Size      = 5   // 32bits unsigned integer
        };
      };

      uint8_t uid;              ///!< Param unique identifier
      uint8_t type;             ///!< Value type

      uint8_t array_len;        ///!< Values count

      uint8_t readable : 1;     ///!< 1 if value is accessible via Get
      uint8_t writeable : 1;    ///!< 1 if value can be modified via Set
      uint8_t _ : 2;            ///!< padding
      
      uint8_t name_length : 4;  ///!< Used for message length optimisation
      const char* name;         ///!< Nullterminated string
      
      static uint8_t sizeof_name(const param_descriptor* desc) 
        { return desc->name_length; }
    };

    template <>
    const layout_descriptor* layout_of<param_descriptor>()
    {
      static layout_descriptor blk1 { 4, 0, (size_t(*)(void*)) &param_descriptor::sizeof_name, true, nullptr };
      
      static layout_descriptor blk0 { 0, 4, nullptr, false, &blk1 };
      return &blk0;
    }

    /// Serialisable object describing a subrange of a parameter value
    struct values_array {

      uint8_t descriptor_uid;

      uint8_t first_index;
      uint8_t last_index;

      uint8_t bytesize;
      uint8_t* values;

      static uint8_t sizeof_values(const values_array* array) 
        { return array->bytesize; }
    };

    template <>
    const layout_descriptor* layout_of<values_array>()
    {
      static layout_descriptor blk1 { 4, 0, (size_t(*)(void*)) &values_array::sizeof_values, true, nullptr };
      
      static layout_descriptor blk0 { 0, 4, nullptr, false, &blk1 };
      return &blk0;
    }
  }
  // namespace hw
}
// namespace sfx