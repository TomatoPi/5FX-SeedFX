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

#include "Utils.hpp"

#include <Utility/smooth_random.h>

#include <cmath>
#include <stddef.h>
#include <type_traits>

namespace sfx
{
  namespace Chorus
  {
    using LFO = daisysp::SmoothRandomGenerator;

    constexpr const size_t BufferSize = 1L << 16;
    constexpr const size_t GrainMaxSize = 1L << 15;
    constexpr const size_t CloudMaxSize = 8;

    float delays[CloudMaxSize] = { 11.f, 17.f, 13.f, 5.f, 7.f, 19.f, 23.f, 29.f };
    float frequencies[CloudMaxSize] = { 25.f, 10.f };
    float depths[CloudMaxSize] = { 0.015f, 0.021f };
    float grain_size_ms = 100.f;
    float dry_gain = -3dB;
    float wet_gain = -3dB;
    float feedback_gain = 0.f;
    size_t cloud_size = 2;

    sfx::Buffer<BufferSize> DSY_SDRAM_BSS _buffer;
    float DSY_SDRAM_BSS _window[GrainMaxSize];

    LFO _lfos[CloudMaxSize];
    size_t _anchors[CloudMaxSize];
    size_t _times[CloudMaxSize * 2];
    float _read_hs[CloudMaxSize * 2];

    size_t _grain_length;

    void Init(float sr);
    float Process(float x);
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
        for (size_t i = 0; i < cloud_size; ++i) {
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
            _read_hs[2 * i + c] = fmod(read_h + depths[i] * _lfos[i].Process(), BufferSize);
          }
          _anchors[i] = (_anchors[i] + 1) & (BufferSize - 1);
        }
        return sample / (float)cloud_size;
      }
    }

    void Init(float sr)
    {
      _buffer.Init();
      _grain_length = grain_size_ms * 0.001f * sr;

      for (size_t i = 0; i < cloud_size; ++i) {
        _lfos[i].Init(sr);
        _lfos[i].SetFreq(frequencies[i]);

        _anchors[i] = BufferSize - (delays[i] * 0.001f * sr);

        for (size_t c = 0; c < 2; ++c) {
          _times[2 * i + c] = 0.5f * c * _grain_length;
          _read_hs[2 * i + c] = static_cast<size_t>(_anchors[i]);
        }
      }
      for (size_t i = 0; i < _grain_length; ++i) {
        _window[i] = sin((M_PI * i) / (float)(_grain_length));
      }
    }
    float Process(float x)
    {
      float wet_sample = details::accumulateVoices();
      float output = dry_gain * x + wet_gain * wet_sample;
      _buffer.Write(x + feedback_gain * wet_sample);
      return output;
    }
  }
}