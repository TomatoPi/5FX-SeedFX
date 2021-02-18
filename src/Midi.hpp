/*
 * Copyright (C) 2021 DAGO Kokri Esaïe <dago.esaie@protonmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

 ///
 ///  \file Midi.hpp
 /// 
 ///  \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
 ///  \date 2021-02-18
 ///

#pragma once

#include <cstdint>
#include <utility>
#include <util/ringbuffer.h>

namespace sfx
{
  namespace midi
  {
    enum Status : uint8_t
    {
      InvalidType = 0x00,
      NoteOff = 0x80,
      NoteOn = 0x90,
      AfterTouchPoly = 0xA0,
      ControlChange = 0xB0,
      ProgramChange = 0xC0,
      AfterTouchChannel = 0xD0,
      PitchBend = 0xE0,
      SystemExclusive = 0xF0,
      TimeCodeQuarterFrame = 0xF1,
      SongPosition = 0xF2,
      SongSelect = 0xF3,
      TuneRequest = 0xF6,
      Clock = 0xF8,
      Start = 0xFA,
      Continue = 0xFB,
      Stop = 0xFC,
      ActiveSensing = 0xFE,
      SystemReset = 0xFF,
    };

    /// \brief Return message length for given type
    constexpr uint8_t length(Status status);

    /// \brief Return true if given status byte correspond to a realtime message
    constexpr bool isRealtime(Status status);

    /// \brief Split Status byte into (type,channel) for channelled messages
    ///   return (status, 0) for non channeled messages
    constexpr std::pair<uint8_t, uint8_t> split(Status status);

    struct Event
    {
      uint8_t status;
      uint8_t channel;
      uint8_t datas[2];
    };

    template <uint8_t RawBufferSize, uint8_t EventBufferSize>
    struct Parser
    {
      uint8_t rawbuffer[RawBufferSize];
      daisy::RingBuffer<Event, EventBufferSize> events;
      uint8_t cur_length, expected_length;

      void Parse(uint8_t byte);
      Event NextEvent();
      bool HasNext();
    };
  }
}

////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////

namespace sfx
{
  namespace midi
  {
    template<uint8_t Rs, uint8_t Es>
    void Parser<Rs, Es>::Parse(uint8_t byte)
    {
      if (0x80 & byte) { // is status
        Status status = static_cast<Status>(byte);
        if (isRealtime(status)) {
          Event event = { byte, 0 };
          events.Write(event);
        } else if (0 == cur_length) {
          expected_length = length(status);
        } else {
          /// TODO : Signal that messages are smashed
        }
      }
      if (Rs <= cur_length) {
        cur_length = expected_length = 0;
        return; /// TODO : Signal that we have droped a message
      }
      rawbuffer[cur_length] = byte;
      cur_length += 1;
      if (cur_length == expected_length) {
        auto [type, channel] = split(static_cast<Status>(rawbuffer[0]));
        uint8_t d1 = 1 < expected_length ? rawbuffer[1] : 0;
        uint8_t d2 = 2 < expected_length ? rawbuffer[2] : 0;
        Event event = { type, channel, d1, d2 };
        events.Write(event);
        cur_length = 0;
      }
    }
    template<uint8_t Rs, uint8_t Es>
    Event Parser<Rs, Es>::NextEvent()
    {
      return events.Read();
    }
    template<uint8_t Rs, uint8_t Es>
    bool Parser<Rs, Es>::HasNext()
    {
      return 0 < events.readable();
    }

    constexpr uint8_t length(Status status)
    {
      switch (status & 0xF0) {
      case 0xF0:
        switch (status) {
        case 0xF0: return 0;
        case 0xF2: return 3;
        case 0xF3: return 2;
        case 0xF6: return 1;
        case 0xF1: return 2;
        case 0xF8: //
        case 0xFA: //
        case 0xFB: //
        case 0xFC: //
        case 0xFE: //
        case 0xFF: return 1;
        default: //fprintf(stderr, "Invalid Midi Sys : %02x\n", type);
          return 0;
        }
      case 0x80: //
      case 0x90: //
      case 0xA0: //
      case 0xB0: //
      case 0xE0: return 3;
      case 0xD0: //
      case 0xC0: return 2;
      default: //fprintf(stderr, "Invalid Midi Type : %02x", type);
        return 0;
      }
    }
    constexpr bool isRealtime(Status status)
    {
      return Status::Clock == status
        || Status::Start == status
        || Status::Continue == status
        || Status::Stop == status;
    }
    constexpr std::pair<uint8_t, uint8_t> split(Status status)
    {
      if (0xF0 == (0xF0 & status)) {
        return { status, 0 };
      } else {
        return { status & 0xF0, status & 0x0F };
      }
    }
  }
}