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
 ///  \file Looper.hpp
 /// 
 ///  \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
 ///  \date 2021-02-18
 ///

#pragma once

#include "Global.hpp"
#include "Utils.hpp"

#include <dev/sdram.h>
#include <array>

namespace sfx
{
  namespace Looper
  {
    sfx::Buffer<BufferSize> DSY_SDRAM_BSS _buffer;
    size_t _max_height;
    size_t _height, _stacksize;
    size_t _play_h, _rec_length;

    enum class State
    {
      Idle,
      Recording,
      Overdubing,
      Playback,
      Overdubed,
      Muted,
    } _status, _muteback;

    float _monitor;
    float _playback;

    void Init(float sr);

    void HitUndo();
    void HitRedo();
    void HitOverdub();
    void HitRecord();
    void HitMute();

    float Process(float x);

    void setMonitorGain(decibel_gain gain);
    void setPlaybackGain(decibel_gain gain);
  };
}

//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////

namespace sfx
{
  namespace Looper
  {
    namespace details
    {
      void StartRecord()
      {
        _buffer.write_h = 0;
        _max_height = 0;
        _height = _stacksize = 0;
        _play_h = _rec_length = 0;
        _status = State::Recording;
      }
      void CancelRecord()
      {
        _status = State::Idle;
      }
      void EndRecord()
      {
        _height = _stacksize = 0;
        _play_h = 0;
        _max_height = (BufferSize / _rec_length) - 1;
        _status = State::Playback;
      }

      void TryStartOverdub()
      {
        if (_height < _max_height) {
          memset(
            _buffer.buffer + _rec_length * (_height + 1),
            0,
            _rec_length * sizeof(_buffer.buffer[0]));
          _status = State::Overdubing;
        }
      }
      void CancelOverdub()
      {
        _status = 0 < _height ? State::Overdubed : State::Playback;
      }
      void EndOverdub()
      {
        _height = std::min(_height + 1, _max_height);
        _stacksize = _height;
        _status = State::Overdubed;
      }

      void Unstack()
      {
        _height = _height - 1;
        if (_height <= 0) {
          _height = 0;
          _status = State::Playback;
        }
      }
      void StopPlayback()
      {
        _status = State::Idle;
      }
      void TryReplay()
      {
        if (0 < _rec_length) {
          _play_h = 0;
          _status = State::Playback;
        }
      }
      void TryRestack()
      {
        if (_height < _stacksize) {
          _height = _height + 1;
          _status = State::Overdubed;
        }
      }

      void Mute()
      {
        _muteback = _status;
        _status = State::Muted;
      }
      void Unmute()
      {
        _status = _muteback;
        _muteback = State::Idle;
      }

      float Idle(float x)
      {
        return _monitor * x;
      }
      float Record(float x)
      {
        _buffer.Write(x);
        _rec_length += 1;
        if (BufferSize <= _rec_length) {
          EndRecord();
        }
        return _monitor * x;
      }
      float Playback(float x)
      {
        float sample = _buffer.Read(_play_h);
        _play_h = (_play_h + 1) % _rec_length;
        return sample * _playback + x * _monitor;
      }
      float Overdubed(float x)
      {
        float sample = _buffer.Read(_play_h);
        for (size_t i = 0; i < _height; ++i)
          sample += _buffer.Read((i + 1) * _rec_length + _play_h);
        _play_h = (_play_h + 1) % _rec_length;
        return sample * _playback + x * _monitor;
      }
      float Muted(float x)
      {
        _play_h = (_play_h + 1) % _rec_length;
        return x * _monitor;
      }
      float Overdub(float x)
      {
        _buffer.buffer[(_height + 1) * _rec_length + _play_h] += x;
        return Overdubed(x);
      }
    }
    void Init(float sr)
    {
      _buffer.Init();

      _max_height = 0;
      _height = _stacksize = 0;
      _play_h = _rec_length = 0;
      _status = State::Idle;
      _muteback = State::Idle;

      setMonitorGain(Settings.Looper.monitor_gain);
      setPlaybackGain(Settings.Looper.playback_gain);
    }

    float Process(float x)
    {
      switch (_status) {
      case State::Idle: return details::Idle(x);
      case State::Recording: return details::Record(x);
      case State::Overdubing: return details::Overdub(x);
      case State::Playback: return details::Playback(x);
      case State::Overdubed: return details::Overdubed(x);
      case State::Muted: return details::Muted(x);
      }
      return x;
    }

    void HitUndo()
    {
      switch (_status) {
      case State::Idle:
        break;
      case State::Recording:
        details::CancelRecord();
        break;
      case State::Overdubing:
        details::CancelOverdub();
        break;
      case State::Playback:
        details::StopPlayback();
        break;
      case State::Overdubed:
        details::Unstack();
        break;
      case State::Muted:
        details::Unmute();
        break;
      }
    }
    void HitRedo()
    {
      switch (_status) {
      case State::Idle:
        details::TryReplay();
        break;
      case State::Recording:
        break;
      case State::Overdubing:
        break;
      case State::Playback:
        details::TryRestack();
        break;
      case State::Overdubed:
        details::TryRestack();
        break;
      case State::Muted:
        details::Unmute();
        HitRedo();
        break;
      }
    }
    void HitOverdub()
    {
      switch (_status) {
      case State::Idle:
        details::StartRecord();
        break;
      case State::Recording:
        details::EndRecord();
        details::TryStartOverdub();
        break;
      case State::Overdubing:
        details::EndOverdub();
        break;
      case State::Playback:
      case State::Overdubed:
        details::TryStartOverdub();
        break;
      case State::Muted:
        details::Unmute();
        HitOverdub();
        break;
      }
    }
    void HitRecord()
    {
      switch (_status) {
      case State::Idle:
        details::StartRecord();
        break;
      case State::Recording:
        details::EndRecord();
        break;
      case State::Overdubing:
        details::CancelOverdub();
        details::StartRecord();
        break;
      case State::Playback:
      case State::Overdubed:
        details::StartRecord();
        break;
      case State::Muted:
        details::Unmute();
        HitRecord();
        break;
      }
    }
    void HitMute()
    {
      switch (_status) {
      case State::Idle:
        break;
      case State::Recording:
        details::CancelRecord();
        break;
      case State::Overdubing:
        details::CancelOverdub();
        break;
      case State::Playback:
      case State::Overdubed:
        details::Mute();
        break;
      case State::Muted:
        details::Unmute();
        break;
      }
    }

    void setMonitorGain(decibel_gain gain)
    {
      _monitor = gain.rms();
      Settings.Looper.monitor_gain = gain;
      SettingsDirtyFlag = true;
    }
    void setPlaybackGain(decibel_gain gain)
    {
      _playback = gain.rms();
      Settings.Looper.playback_gain = gain;
      SettingsDirtyFlag = true;
    }
  }
}