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
    /// \brief At least 5min (at 48kHz) buffer for looper
    constexpr const size_t BufferSize = sfx::uppow2(sfx::ms2sample(4.f * 60'000.f, 48'000.f));

    struct Settings
    {
      decibel_gain monitor_gain = 0dB;
      decibel_gain playback_gain = -1dB;
    };

    class Engine
    {
    public:

      using Buffer = sfx::Buffer<BufferSize>;

      enum class State
      {
        Idle,
        Recording,
        Overdubing,
        Playback,
        Overdubed,
        Muted,
      };

      void Init(float sr, Buffer* buffer, Settings* settings);

      void HitUndo();
      void HitRedo();
      void HitOverdub();
      void HitRecord();
      void HitMute();

      float Process(float x);

      void setMonitorGain(decibel_gain gain);
      void setPlaybackGain(decibel_gain gain);

      State GetState();

    private:

      void Unstack();
      void TryRestack();

      void StartRecord();
      void CancelRecord();
      void EndRecord();

      void TryStartOverdub();
      void CancelOverdub();
      void EndOverdub();

      void StopPlayback();
      void TryReplay();

      void Mute();
      void Unmute();

      float Idle(float x);
      float Record(float x);
      float Overdub(float x);

      float Playback(float x);
      float Overdubed(float x);
      float Muted(float x);

    public:

      Buffer* _buffer;
      Settings* _settings;
      Engine* _link;
      size_t _max_height;
      size_t _height, _stacksize;
      size_t _play_h, _rec_length;
      State _status, _muteback;
      float _monitor;
      float _playback;
    };
  };
}

//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////

namespace sfx
{
  namespace Looper
  {

    Engine::State Engine::GetState()
    {
      return _status;
    }

    void Engine::StartRecord()
    {
      Engine* tmp = this;
      do {
        tmp->_buffer->write_h = 0;
        tmp->_max_height = 0;
        tmp->_height = tmp->_stacksize = 0;
        tmp->_play_h = tmp->_rec_length = 0;
        tmp->_status = State::Recording;
        tmp = tmp->_link;
      } while (tmp && tmp != this);
    }
    void Engine::CancelRecord()
    {
      Engine* tmp = this;
      do {
        tmp->_status = State::Idle;
        tmp = tmp->_link;
      } while (tmp && tmp != this);
    }
    void Engine::EndRecord()
    {
      Engine* tmp = this;
      do {
        tmp->_height = tmp->_stacksize = 0;
        tmp->_play_h = 0;
        tmp->_max_height = (BufferSize / tmp->_rec_length) - 1;
        tmp->_status = State::Playback;
        tmp = tmp->_link;
      } while (tmp && tmp != this);
    }

    void Engine::TryStartOverdub()
    {
      if (_height < _max_height) {
        memset(
          _buffer->buffer + _rec_length * (_height + 1),
          0,
          _rec_length * sizeof(_buffer->buffer[0]));
        _status = State::Overdubing;
      }
    }
    void Engine::CancelOverdub()
    {
      _status = 0 < _height ? State::Overdubed : State::Playback;
    }
    void Engine::EndOverdub()
    {
      _height = std::min(_height + 1, _max_height);
      _stacksize = _height;
      _status = State::Overdubed;
    }

    void Engine::Unstack()
    {
      _height = _height - 1;
      if (_height <= 0) {
        _height = 0;
        _status = State::Playback;
      }
    }
    void Engine::StopPlayback()
    {
      _status = State::Idle;
    }
    void Engine::TryReplay()
    {
      if (0 < _rec_length) {
        _play_h = 0;
        _status = State::Playback;
      }
    }
    void Engine::TryRestack()
    {
      if (_height < _stacksize) {
        _height = _height + 1;
        _status = State::Overdubed;
      }
    }

    void Engine::Mute()
    {
      _muteback = _status;
      _status = State::Muted;
    }
    void Engine::Unmute()
    {
      _status = _muteback;
      _muteback = State::Idle;
    }

    float Engine::Idle(float x)
    {
      return _monitor * x;
    }
    float Engine::Record(float x)
    {
      _buffer->Write(x);
      _rec_length += 1;
      if (BufferSize <= _rec_length) {
        EndRecord();
      }
      return _monitor * x;
    }
    float Engine::Playback(float x)
    {
      float sample = _buffer->Read(_play_h);
      _play_h = (_play_h + 1) % _rec_length;
      return sample * _playback + x * _monitor;
    }
    float Engine::Overdubed(float x)
    {
      float sample = _buffer->Read(_play_h);
      for (size_t i = 0; i < _height; ++i)
        sample += _buffer->Read((i + 1) * _rec_length + _play_h);
      _play_h = (_play_h + 1) % _rec_length;
      return sample * _playback + x * _monitor;
    }
    float Engine::Muted(float x)
    {
      _play_h = (_play_h + 1) % _rec_length;
      return x * _monitor;
    }
    float Engine::Overdub(float x)
    {
      _buffer->buffer[(_height + 1) * _rec_length + _play_h] += x;
      return Overdubed(x);
    }

    void Engine::Init(float sr, Buffer* buffer, Settings* settings)
    {
      _buffer = buffer;
      _buffer->Init();

      _settings = settings;

      _max_height = 0;
      _height = _stacksize = 0;
      _play_h = _rec_length = 0;
      _status = State::Idle;
      _muteback = State::Idle;

      _link = nullptr;

      setMonitorGain(_settings->monitor_gain);
      setPlaybackGain(_settings->playback_gain);
    }

    float Engine::Process(float x)
    {
      switch (_status) {
      case State::Idle: return Idle(x);
      case State::Recording: return Record(x);
      case State::Overdubing: return Overdub(x);
      case State::Playback: return Playback(x);
      case State::Overdubed: return Overdubed(x);
      case State::Muted: return Muted(x);
      }
      return x;
    }

    void Engine::HitUndo()
    {
      switch (_status) {
      case State::Idle:
        break;
      case State::Recording:
        CancelRecord();
        break;
      case State::Overdubing:
        CancelOverdub();
        break;
      case State::Playback:
        StopPlayback();
        break;
      case State::Overdubed:
        Unstack();
        break;
      case State::Muted:
        Unmute();
        break;
      }
    }
    void Engine::HitRedo()
    {
      switch (_status) {
      case State::Idle:
        TryReplay();
        break;
      case State::Recording:
        break;
      case State::Overdubing:
        break;
      case State::Playback:
        TryRestack();
        break;
      case State::Overdubed:
        TryRestack();
        break;
      case State::Muted:
        Unmute();
        HitRedo();
        break;
      }
    }
    void Engine::HitOverdub()
    {
      switch (_status) {
      case State::Idle:
        StartRecord();
        break;
      case State::Recording:
        EndRecord();
        TryStartOverdub();
        break;
      case State::Overdubing:
        EndOverdub();
        break;
      case State::Playback:
      case State::Overdubed:
        TryStartOverdub();
        break;
      case State::Muted:
        Unmute();
        HitOverdub();
        break;
      }
    }
    void Engine::HitRecord()
    {
      switch (_status) {
      case State::Idle:
        StartRecord();
        break;
      case State::Recording:
        EndRecord();
        break;
      case State::Overdubing:
        CancelOverdub();
        StartRecord();
        break;
      case State::Playback:
      case State::Overdubed:
        StartRecord();
        break;
      case State::Muted:
        Unmute();
        HitRecord();
        break;
      }
    }
    void Engine::HitMute()
    {
      switch (_status) {
      case State::Idle:
        break;
      case State::Recording:
        CancelRecord();
        break;
      case State::Overdubing:
        CancelOverdub();
        break;
      case State::Playback:
      case State::Overdubed:
        Mute();
        break;
      case State::Muted:
        Unmute();
        break;
      }
    }

    void Engine::setMonitorGain(decibel_gain gain)
    {
      _monitor = gain.rms();
      _settings->monitor_gain = gain;
      SettingsDirtyFlag = true;
    }
    void Engine::setPlaybackGain(decibel_gain gain)
    {
      _playback = gain.rms();
      _settings->playback_gain = gain;
      SettingsDirtyFlag = true;
    }
  }
}