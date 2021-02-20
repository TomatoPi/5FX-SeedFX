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

#include <Utility/smooth_random.h>

#include <cmath>
#include <stddef.h>
#include <cstring>

namespace sfx
{
  namespace Chorus
  {
    namespace details
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
    }

    void Init();
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
    namespace details
    {
      float accumulateVoices()
      {
        float sample = 0.f;
        for (size_t i = 0; i < global::Settings.Chorus.cloud_size; ++i) {
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
              read_h + global::Settings.Chorus.depths[i] * _lfos[i].Process(), BufferSize);
          }
          _anchors[i] = (_anchors[i] + 1) & (BufferSize - 1);
        }
        return sample / (float)global::Settings.Chorus.cloud_size;
      }
    }

    void Init()
    {
      using namespace details;
      _sr = global::hardware.AudioSampleRate();
      _buffer.Init();
      for (size_t i = 0; i < CloudMaxSize; ++i)
        _lfos[i].Init(global::hardware.AudioSampleRate());
      memset(_window, 0, GrainMaxSize * sizeof(float));
      Reload();
    }
    void Reload()
    {
      setGrainSize(global::Settings.Chorus.grain_size_ms);
      setDryGain(global::Settings.Chorus.dry_gain);
      setWetGain(global::Settings.Chorus.wet_gain);
      setFeedbackGain(global::Settings.Chorus.feedback_gain);

      setCloudSize(global::Settings.Chorus.cloud_size);
      setBypass(global::Settings.Chorus.bypass);

      for (size_t i = 0; i < global::Settings.Chorus.cloud_size; ++i) {
        setFrequency(i, global::Settings.Chorus.frequencies[i]);
        setDelay(i, global::Settings.Chorus.delays[i]);
        setDepth(i, global::Settings.Chorus.depths[i]);
      }
    }
    float Process(float x)
    {
      float wet_sample = details::accumulateVoices();
      float output = global::Settings.Chorus.dry_gain * x + global::Settings.Chorus.wet_gain * wet_sample;
      details::_buffer.Write(x + global::Settings.Chorus.feedback_gain * wet_sample);
      return global::Settings.Chorus.bypass ? x : output;
    }

    void setFrequency(int i, float frequency)
    {
      global::Settings.Chorus.frequencies[i] = frequency;
      details::_lfos[i].SetFreq(frequency);
      global::dirty_flag = true;
    }
    void setDelay(int i, float delay)
    {
      global::Settings.Chorus.delays[i] = delay;
      details::_anchors[i] = BufferSize - (delay * 0.001f * details::_sr);
      details::_read_hs[2 * i + 0] = static_cast<size_t>(details::_anchors[i]);
      details::_read_hs[2 * i + 1] = static_cast<size_t>(details::_anchors[i]);
      global::dirty_flag = true;
    }
    void setDepth(int i, float depth)
    {
      global::Settings.Chorus.depths[i] = depth;
      global::dirty_flag = true;
    }

    void setGrainSize(float size)
    {
      global::Settings.Chorus.grain_size_ms = size;
      details::_grain_length = global::Settings.Chorus.grain_size_ms * 0.001f * details::_sr;
      for (size_t i = 0; i < global::Settings.Chorus.cloud_size; ++i) {
        details::_times[2 * i + 0] = 0;
        details::_times[2 * i + 1] = details::_grain_length >> 1;
      }
      for (size_t i = 0; i < details::_grain_length; ++i) {
        details::_window[i] = sin((M_PI * i) / (float)(details::_grain_length));
      }
      global::dirty_flag = true;
    }
    void setDryGain(float gain)
    {
      global::Settings.Chorus.dry_gain = gain;
      global::dirty_flag = true;
    }
    void setWetGain(float gain)
    {
      global::Settings.Chorus.wet_gain = gain;
      global::dirty_flag = true;
    }
    void setFeedbackGain(float gain)
    {
      global::Settings.Chorus.feedback_gain = gain;
      global::dirty_flag = true;
    }

    void setCloudSize(size_t size)
    {
      global::Settings.Chorus.cloud_size = size;
      global::dirty_flag = true;
    }
    void setBypass(bool bypass)
    {
      global::Settings.Chorus.bypass = bypass;
      global::dirty_flag = true;
    }
  }
}