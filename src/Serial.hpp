#pragma once

#include <stdint.h>

/*
Warning :
  Code written in this file must be platform independant.
*/

namespace serial
{
  namespace flags
  {
    constexpr const uint8_t BeginOfStream = 0xF0;
    constexpr const uint8_t EndOfStream = 0xF7;
  }

  struct Packet
  {
    struct Header { enum : uint8_t { Type, ObjectSize, Size }; };

    static constexpr const uint8_t ObjectSizeMax = 0xFF;
    
    uint8_t header[Header::Size] = {0};
    uint8_t rawobj[ObjectSizeMax] = {0};

    // Packet() = default;
    // Packet& operator= (const Packet& packet)
    // {
    //   for (uint8_t i = 0 ; i < Header::Size ; ++i)
    //     header[i] = packet.header[i];
    //   for (uint8_t i = 0 ; i < Size ; ++i)
    //     rawobj[i] = packet.rawobj[i];
    //   return *this;
    // }

    template <typename T> T read() const { return T(*(T*)rawobj); }

    const uint8_t* serialize() const { return (uint8_t*)&header; }

    size_t size() const { return Header::Size + header[Header::ObjectSize]; }
  };

  template <typename T>
  static Packet Serialize(const T& obj)
  {
    static_assert(sizeof(T) <= Packet::ObjectSizeMax);

    Packet packet;
    packet.header[Packet::Header::Type] = T::TypeFlag;
    packet.header[Packet::Header::ObjectSize] = sizeof(T);

    uint8_t i;
    const uint8_t* raw = (uint8_t*)&obj;
    for (i = 0; i < sizeof(T) ; ++i)
      packet.rawobj[i] = raw[i];
    for ( ; i < Packet::ObjectSizeMax ; ++i)
      packet.rawobj[i] = 0;


    return packet;
  }
  
  struct ParsingResult {
    enum class Status {
      Running = 0,
      Started = 1,
      Finished = 2,
      EndOfStream = 3,
      Error = 4
    };
    Status status = Status::Running;
    Packet packet;
    uint8_t error;

    ParsingResult(Status s, const Packet& p = Packet(), uint8_t e = 0) :
      status(s), packet(p), error(e) {}

    static ParsingResult Started() { return {Status::Started}; }
    static ParsingResult Running() { return {Status::Running}; }
    static ParsingResult Finished(const Packet& packet) { return {Status::Finished, packet}; }
    static ParsingResult EndOfStream() { return {Status::EndOfStream}; }
    static ParsingResult Error(uint8_t err) { return {Status::Error, Packet(), err}; }
  };

  struct SerialParser
  {
    Packet serial_buffer_in;
    uint8_t serial_index = 0;

    ParsingResult parse(uint8_t byte)
    {
      if (serial_index < Packet::Header::Size)
      {
        if (0 == serial_index && static_cast<uint8_t>(flags::EndOfStream) == byte)
          return ParsingResult::EndOfStream();

        serial_buffer_in.header[serial_index] = byte;

        serial_index++;
        return ParsingResult::Started();
      }

      serial_buffer_in.rawobj[serial_index - Packet::Header::Size] = byte; // will write in flags too
      serial_index++;

      if (serial_buffer_in.size() <= serial_index)
      {
        serial_index = 0;
        return ParsingResult::Finished(serial_buffer_in);
      }
      else
      {
        return ParsingResult::Running();
      }
    }

    ParsingResult error(int code)
    {
      serial_buffer_in = Packet();
      serial_index = 0;
      return ParsingResult::Error(code);
    }
  };
}

/////////////////////////////////////////////////////////
// Available packets
/////////////////////////////////////////////////////////

namespace serial
{
  namespace messages
  {
    struct Types {
      enum : uint8_t {
        Unknown = 0,
        Scan = 1,
        QueryDevice = 2,
        ParamDescription = 3,
      };
    };

    struct Scan {
      static constexpr const uint8_t TypeFlag = Types::Scan;

      struct DeviceDescription {
        uint8_t model[16];
        uint8_t uuid;
        uint8_t version;

        uint8_t params_count;
      };

      DeviceDescription device;
      uint8_t scan_uid;
    };

    struct QueryDevice {
      static constexpr const uint8_t TypeFlag = Types::QueryDevice;

      uint8_t uuid;
    };

    struct ParamDescription {
      static constexpr const uint8_t TypeFlag = Types::ParamDescription;

      struct ParamTypes {
        enum : uint8_t {
          Boolean,
          Integer,
          Float,
          Gain,
          Size
        };
      };

      uint8_t name[16];
      uint8_t uuid;
      uint8_t type;
      
      uint8_t array_len;

      uint8_t readable : 1;
      uint8_t writeable : 1;
      uint8_t _ : 6;
    };
  }
}