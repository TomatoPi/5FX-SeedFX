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

namespace sfx
{
  namespace Looper
  {
    sfx::Buffer<BufferSize> DSY_SDRAM_BSS _buffer;
    size_t _play_h, _rec_length;
    bool _recording;
    bool _overdubing;
    bool _playing;

    float _monitor;
    float _playback;

    void Init(float sr);

    void StartRecord();
    void StopRecord();

    void StartOverdub();
    void StopOverdub();

    void StartPlayback();
    void StopPlayback();

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
      void Record(float x)
      {
        _buffer.Write(x);
        _rec_length += 1;
        if (BufferSize <= _rec_length) {
          StopRecord();
        }
      }
      void Overdub(float x)
      {
        _buffer.buffer[_buffer.write_h] += x;
        _buffer.write_h = (_buffer.write_h + 1) % _rec_length;
      }
      float Playback()
      {
        float sample = _buffer.Read(_play_h);
        _play_h = (_play_h + 1) % _rec_length;
        return sample;
      }
    }
    void Init(float sr)
    {
      _buffer.Init();
      _play_h = _rec_length = 0;
      _recording = _playing = false;

      setMonitorGain(Settings.Looper.monitor_gain);
      setPlaybackGain(Settings.Looper.playback_gain);
    }

    void StartRecord()
    {
      StopOverdub();
      _recording = true;
      _buffer.write_h = 0;
      _rec_length = 0;
    }
    void StopRecord()
    {
      _recording = false;
    }

    void StartOverdub()
    {
      StopRecord();
      _overdubing = true;
      _buffer.write_h = 0;
    }
    void StopOverdub()
    {
      _overdubing = false;
    }

    void StartPlayback()
    {
      _playing = 0 < _rec_length;
      _play_h = 0;
    }
    void StopPlayback()
    {
      _playing = false;
    }

    float Process(float x)
    {
      float sample = 0.f;
      if (_recording) {
        details::Record(x);
      }
      if (_overdubing) {
        details::Overdub(x);
      }
      if (_playing) {
        sample += _playback * details::Playback();
      }
      return sample + _monitor * x;
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