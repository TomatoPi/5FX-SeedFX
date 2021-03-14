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
    std::array<sfx::Buffer<BufferSize>, LayersCount> DSY_SDRAM_BSS _stack;
    size_t _height, _stacksize;
    size_t _play_h, _rec_length;

    enum class State
    {
      Idle,
      Recording,
      Overdubing,
      Playback,
      Overdubed
    } _status;

    float _monitor;
    float _playback;

    void Init(float sr);

    void HitUndo();
    void HitRedo();
    void HitOverdub();
    void HitRecord();

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
        for (auto& buffer : _stack) buffer.write_h = 0;
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
        _status = State::Playback;
      }

      void StartOverdub()
      {
        if (_height < LayersCount) {
          _stack[_height].write_h = _play_h;
          _status = State::Overdubing;
        }
      }
      void CancelOverdub()
      {
        _status = 0 < _height ? State::Overdubed : State::Playback;
      }
      void EndOverdub()
      {
        _height = std::min(_height + 1, LayersCount);
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

      float Idle(float x)
      {
        return _monitor * x;
      }
      float Record(float x)
      {
        _buffer.Write(x);
        for (auto& buffer : _stack) buffer.Write(0);
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
        for (size_t i = 0; i < _stacksize; ++i)
          sample += _stack[i].Read(_play_h);
        _play_h = (_play_h + 1) % _rec_length;
        return sample * _playback + x * _monitor;
      }
      float Overdub(float x)
      {
        _stack[_height].buffer[_play_h] += x;
        return Overdubed(x);
      }
    }
    void Init(float sr)
    {
      _buffer.Init();
      for (auto& buffer : _stack) buffer.Init();

      _height = _stacksize = 0;
      _play_h = _rec_length = 0;
      _status = State::Idle;

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
        details::StartOverdub();
        break;
      case State::Overdubing:
        details::EndOverdub();
        break;
      case State::Playback:
      case State::Overdubed:
        details::StartOverdub();
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