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
    bool _playing;

    void Init(float sr);

    void StartRecord();
    void StopRecord();

    void StartPlayback();
    void StopPlayback();

    float Process(float x);

    void setMonitorGain(float gain);
    void setPlaybackGain(float gain);
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
      _recording = true;
      _buffer.write_h = 0;
      _rec_length = 0;
    }
    void StopRecord()
    {
      _recording = false;
    }

    void StartPlayback()
    {
      _playing = true;
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
      if (_playing) {
        sample += Settings.Looper.playback_gain * details::Playback();
      }
      return sample + Settings.Looper.monitor_gain * x;
    }

    void setMonitorGain(float gain)
    {
      Settings.Looper.monitor_gain = gain;
      SettingsDirtyFlag = true;
    }
    void setPlaybackGain(float gain)
    {
      Settings.Looper.playback_gain = gain;
      SettingsDirtyFlag = true;
    }
  }
}