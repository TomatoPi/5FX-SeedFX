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
 ///  \file Chorus.cpp
 /// 
 ///  \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
 ///  \date 2021-02-18
 ///

#pragma once

#include "Global.hpp"
#include "Utils.hpp"

#include <dev/sdram.h>
#include <Utility/smooth_random.h>

#include <cmath>
#include <stddef.h>
#include <cstring>

namespace sfx
{
  namespace Chorus
  {
    using LFO = daisysp::SmoothRandomGenerator;

    sfx::Buffer<BufferSize> DSY_SDRAM_BSS _buffer;
    float DSY_SDRAM_BSS _window[GrainMaxSize];

    LFO _lfos[CloudMaxSize];
    size_t _anchors[CloudMaxSize];
    size_t _times[CloudMaxSize * 2];
    float _read_hs[CloudMaxSize * 2];

    size_t _grain_length;
    float _sr;

    void Init(float samplerate);
    void Reload();

    float Process(float x);

    void setFrequency(int voice, float frequency);
    void setDelay(int voice, float delay);
    void setDepth(int voice, float depth);

    void setGrainSize(float size);
    void setDryGain(float gain);
    void setWetGain(float gain);
    void setFeedbackGain(float gain);

    void setCloudSize(size_t size);
    void setBypass(bool bypass);
  }
}

/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////

namespace sfx
{
  namespace Chorus
  {
    float accumulateVoices()
    {
      float sample = 0.f;
      for (size_t i = 0; i < Settings.Chorus.cloud_size; ++i) {
        for (size_t c = 0; c < 2; ++c) {
          size_t time = _times[2 * i + c];
          float read_h = _read_hs[2 * i + c];
          sample += _window[time] * _buffer.Read(read_h);
          time = (time + 1) % _grain_length;
          if (0 == time) {
            read_h = static_cast<float>(_anchors[i]);
          } else {
            read_h += 1.f;
          }
          _times[2 * i + c] = time;
          _read_hs[2 * i + c] = fmod(
            read_h + Settings.Chorus.depths[i] * _lfos[i].Process(), BufferSize);
        }
        _anchors[i] = (_anchors[i] + 1) & (BufferSize - 1);
      }
      return sample / (float)Settings.Chorus.cloud_size;
    }

    float Process(float x)
    {
      float wet_sample = accumulateVoices();
      float output = Settings.Chorus.dry_gain * x + Settings.Chorus.wet_gain * wet_sample;
      _buffer.Write(x + Settings.Chorus.feedback_gain * wet_sample);
      return Settings.Chorus.bypass ? x : output;
    }

    void Init(float samplerate)
    {
      _sr = samplerate;
      _buffer.Init();
      memset(_window, 0, GrainMaxSize * sizeof(float));
      for (size_t i = 0; i < CloudMaxSize; ++i)
        _lfos[i].Init(samplerate);
      Reload();
    }
    void Reload()
    {
      setGrainSize(Settings.Chorus.grain_size_ms);
      setDryGain(Settings.Chorus.dry_gain);
      setWetGain(Settings.Chorus.wet_gain);
      setFeedbackGain(Settings.Chorus.feedback_gain);

      setCloudSize(Settings.Chorus.cloud_size);
      setBypass(Settings.Chorus.bypass);

      for (size_t i = 0; i < Settings.Chorus.cloud_size; ++i) {
        setFrequency(i, Settings.Chorus.frequencies[i]);
        setDelay(i, Settings.Chorus.delays[i]);
        setDepth(i, Settings.Chorus.depths[i]);
      }
    }

    void setFrequency(int i, float frequency)
    {
      Settings.Chorus.frequencies[i] = frequency;
      _lfos[i].SetFreq(frequency);
      SettingsDirtyFlag = true;
    }
    void setDelay(int i, float delay)
    {
      Settings.Chorus.delays[i] = delay;
      _anchors[i] = (_buffer.write_h + BufferSize - size_t(delay * 0.001f * _sr)) & (BufferSize - 1);
      _read_hs[2 * i + 0] = static_cast<size_t>(_anchors[i]);
      _read_hs[2 * i + 1] = static_cast<size_t>(_anchors[i]);
      SettingsDirtyFlag = true;
    }
    void setDepth(int i, float depth)
    {
      Settings.Chorus.depths[i] = depth;
      SettingsDirtyFlag = true;
    }

    void setGrainSize(float size)
    {
      Settings.Chorus.grain_size_ms = size;
      _grain_length = Settings.Chorus.grain_size_ms * 0.001f * _sr;
      for (size_t i = 0; i < Settings.Chorus.cloud_size; ++i) {
        _times[2 * i + 0] = 0;
        _times[2 * i + 1] = _grain_length >> 1;
      }
      for (size_t i = 0; i < _grain_length; ++i) {
        _window[i] = sin((M_PI * i) / (float)(_grain_length));
      }
      SettingsDirtyFlag = true;
    }
    void setDryGain(float gain)
    {
      Settings.Chorus.dry_gain = gain;
      SettingsDirtyFlag = true;
    }
    void setWetGain(float gain)
    {
      Settings.Chorus.wet_gain = gain;
      SettingsDirtyFlag = true;
    }
    void setFeedbackGain(float gain)
    {
      Settings.Chorus.feedback_gain = gain;
      SettingsDirtyFlag = true;
    }

    void setCloudSize(size_t size)
    {
      Settings.Chorus.cloud_size = size;
      SettingsDirtyFlag = true;
    }
    void setBypass(bool bypass)
    {
      Settings.Chorus.bypass = bypass;
      SettingsDirtyFlag = true;
    }
  }
}