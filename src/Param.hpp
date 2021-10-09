#pragma once

#include "Serial.hpp"
#include "Decibel.hpp"

#include <array>
#include <tuple>

namespace sfx
{

  extern std::array<sfx::messages::ParamDescriptor, 0xFF> _params_descriptors;
  extern size_t _params_descriptors_cout;

  #define Param_T \
      typename T, \
      const char Name[16], \
      uint8_t UUID, uint8_t Type, \
      uint8_t Length, \
      uint8_t Readable, uint8_t Writable

  template <Param_T> struct Param {

    T values[Length];

    Param ()
    {
      static bool initialized = false;
      if (!initialized)
      {
        initialized = true;
        _params_descriptors[_params_descriptors_cout] = descriptor();
        _params_descriptors_cout += 1;
      }
      else
      {
        // Make things explode
      }
    }
    ~Param() {}

    operator T() const { return values[0]; }

    Param& operator= (T val) { values[0] = val; return *this; }

    size_t size() const { return Length; }

    static sfx::messages::ParamDescriptor descriptor() {
      sfx::messages::ParamDescriptor desc;

      uint8_t* name = (uint8_t*) desc.name;
      for (const char* c = Name ; *c != '\0' ; ++c, ++name)
        *name = *c;
      *name = '\0';

      desc.param_uuid = UUID;
      desc.type = Type;

      desc.array_len = Length;
      
      desc.readable = Readable;
      desc.writeable = Writable;

      return desc;
    }
  };

  using ParamTypes = sfx::messages::ParamDescriptor::ParamTypes;


  #define ARRAY_PARAM_T \
    template <const char Name[16], uint8_t UUID, uint8_t Length, uint8_t Readable, uint8_t Writable>

  ARRAY_PARAM_T
  using BooleanArray = Param<bool, Name, UUID, ParamTypes::Boolean, Length, Readable, Writable>;

  ARRAY_PARAM_T
  using IntegerArray = Param<int, Name, UUID, ParamTypes::Integer, Length, Readable, Writable>;

  ARRAY_PARAM_T
  using FloatArray = Param<float, Name, UUID, ParamTypes::Float, Length, Readable, Writable>;

  ARRAY_PARAM_T
  using GainArray = Param<decibel_gain, Name, UUID, ParamTypes::Gain, Length, Readable, Writable>;

  ARRAY_PARAM_T
  using SizeArray = Param<size_t, Name, UUID, ParamTypes::Size, Length, Readable, Writable>;


  #define SINGLE_PARAM_T \
    template <const char Name[16], uint8_t UUID, uint8_t Readable, uint8_t Writable>

  SINGLE_PARAM_T
  using Boolean = Param<bool, Name, UUID, ParamTypes::Boolean, 1, Readable, Writable>;

  SINGLE_PARAM_T
  using Integer = Param<int, Name, UUID, ParamTypes::Integer, 1, Readable, Writable>;

  SINGLE_PARAM_T
  using Float = Param<float, Name, UUID, ParamTypes::Float, 1, Readable, Writable>;

  SINGLE_PARAM_T
  using Gain = Param<decibel_gain, Name, UUID, ParamTypes::Gain, 1, Readable, Writable>;

  SINGLE_PARAM_T
  using Size = Param<size_t, Name, UUID, ParamTypes::Size, 1, Readable, Writable>;
} // namespace sfx