#pragma once

#include <stdint.h>

/*
Warning :
  Code written in this file must be platform independant.
*/

namespace sfx
{


  namespace serial
  {

    struct Packet {

      struct Header { enum : uint8_t { Sender, Type, ObjectSize, Size }; };
      static constexpr const uint8_t ObjectSizeMax = 0xFF;

      uint8_t header[Header::Size] = {0};
      uint8_t* rawobj = nullptr;

      uint8_t operator[] (size_t i) const
      {
        if (i < Header::Size) return header[i];
        else if (i < length()) return rawobj[i - Header::Size];
        else return 0; // Error
      }

      uint8_t& sender_uuid() { return header[Header::Sender]; }
      const uint8_t& sender_uuid() const { return header[Header::Sender]; }

      uint8_t& object_type() { return header[Header::Type]; }
      const uint8_t& object_type() const { return header[Header::Type]; }

      uint8_t& object_size() { return header[Header::ObjectSize]; }
      const uint8_t& object_size() const { return header[Header::ObjectSize]; }

      size_t length() const { return Header::Size + object_size(); }

      template <typename T> uint8_t* prepare(const DeviceDescriptor* device, T* obj)
      {
        static_assert(sizeof(T) <= ObjectSizeMax);

        sender_uuid() = device->uuid;

        object_type() = T::TypeFlag;
        object_size() = obj->size();

        rawobj = (uint8_t*) obj;

        return header;
      }

      template <typename T> T read() const { return T(*(T*)rawobj); }
    };

    struct PacketParser {

      struct Result {

        enum class Status {
          Running = 0,
          Started = 1,
          Finished = 2,
          Error = 4
        };
        Status status = Status::Running;
        Packet* packet;
        uint8_t error;

        Result(Status s, Packet* p = nullptr, uint8_t e = 0) :
          status(s), packet(p), error(e) {}

        static Result Started() { return {Status::Started}; }
        static Result Running() { return {Status::Running}; }
        static Result Finished(Packet* packet) { return {Status::Finished, packet}; }
        static Result Error(uint8_t err) { return {Status::Error, nullptr, err}; }
      };

      Packet current_packet;

      uint8_t serial_buffer[Packet::ObjectSizeMax];
      uint8_t serial_index = 0;

      PacketParser()
      {
        current_packet.rawobj = serial_buffer;
      }

      Result parse(uint8_t byte)
      {
        if (serial_index < Packet::Header::Size)
        {
          current_packet.header[serial_index] = byte;

          serial_index++;
          return 1 == serial_index ? Result::Started() : Result::Running();
        }

        current_packet.rawobj[serial_index - Packet::Header::Size] = byte;
        serial_index++;

        if (current_packet.length() <= serial_index)
        {
          serial_index = 0;
          return Result::Finished(&current_packet);
        }
        else
        {
          return Result::Running();
        }
      }

      Result error(int code)
      {
        serial_index = 0;
        return Result::Error(code);
      }
    };
  }
  // namespace serial
}
// namespace sfx

/////////////////////////////////////////////////////////
// Available packets
/////////////////////////////////////////////////////////

namespace sfx
{
  namespace messages
  {
    struct Types {
      enum : uint8_t {

        Unknown = 0x00,

        // Network management

        Scan = 0x01,

        // Device introspection

        QueryDevice = 0x10,
        ParamDescription = 0x11,

        // Device edition

        Command = 0x20,
        
        Get = 0x31,
        GetReply = 0x31,

        Set = 0x38,
      };
    };

    // Network Management

    struct Scan {
      static constexpr const uint8_t TypeFlag = Types::Scan;

      uint8_t scan_uid;
      DeviceDescriptor desc;

      uint8_t size() const { return 1 + desc.size(); }
    };

    // Device Introspection

    struct QueryDevice {
      static constexpr const uint8_t TypeFlag = Types::QueryDevice;

      uint8_t device_uuid;

      uint8_t size() const { return sizeof(QueryDevice); }
    };

    struct ParamDescriptor {
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

      uint8_t device_uuid;

      uint8_t param_uuid;
      uint8_t type;

      uint8_t array_len;

      uint8_t readable : 1;
      uint8_t writeable : 1;
      uint8_t _ : 2;
      
      uint8_t name_length : 4;
      uint8_t name[16];

      uint8_t size() const { return 4 + 1 + name_length; }
    };

    // Device Edition

    struct Command {
      static constexpr const uint8_t TypeFlag = Types::Command;

      uint8_t device_uuid;

      uint8_t length : 7;
      uint8_t _ : 1;

      uint8_t str[0x7F];

      uint8_t size() const { return 2 + length; }
    };

    struct Get {
      static constexpr const uint8_t TypeFlag = Types::Get;

      uint8_t device_uuid;
      uint8_t param_uuid;

      uint8_t first_index;
      uint8_t last_index;

      uint8_t size() const { return sizeof(Get); }
    };

    struct GetReply {
      static constexpr const uint8_t TypeFlag = Types::GetReply;

      uint8_t device_uuid;
      uint8_t param_uuid;

      uint8_t first_index;
      uint8_t last_index;

      uint8_t values[0x7F];

      uint8_t values_count() const { return last_index - first_index; }
      uint8_t size() const { return 4 + values_count(); }
    };

    struct Set {
      static constexpr const uint8_t TypeFlag = Types::Set;

      uint8_t device_uuid;
      uint8_t param_uuid;

      uint8_t first_index;
      uint8_t last_index;

      uint8_t values[0x7F];

      uint8_t values_count() const { return last_index - first_index; }
      uint8_t size() const { return 4 + values_count(); }
    };
  }
}