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

    sfx::Buffer<BufferSize> DSY_SDRAM_BSS _buffer;
    float DSY_SDRAM_BSS _window[GrainMaxSize];

    struct Granulator
    {
      struct Grain
      {
        LFO lfo;
        size_t time;
        float read_h;

        void Init(float sr, float freq, float phase, const Granulator& g);
        float Read(const Granulator& g);
      };

      void Init(float sr, float freq, float delay, float grain);
      void SetDepth(float d);
      float Read();

      Grain ga, gb;
      size_t anchor, grain_length;
      float depth;

    } _granulators[CloudMaxSize];

    struct Params
    {
      size_t cloud_size;
      float dry;
      float wet;
      float feedback;

    } _params;

    void Init(float sr);
    float Read();
    float Process(float x);
  }
}

/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////

namespace sfx
{
  namespace Chorus
  {
    /* Grain */

    void Granulator::Grain::Init(float sr, float freq, float phase, const Granulator& g)
    {
      time += g.grain_length * phase;
      read_h = static_cast<float>(g.anchor);

      lfo.Init(sr);
      lfo.SetFreq(freq);
    }

    float Granulator::Grain::Read(const Granulator& g)
    {
      float sample = _window[time] * _buffer.Read(read_h);
      time = (time + 1) % g.grain_length;
      if (0 == time) {
        read_h = static_cast<float>(g.anchor);
      } else {
        read_h += 1.f;
      }
      read_h = fmod(read_h + g.depth * lfo.Process(), BufferSize);
      return sample;
    }

    /* Granulator */

    void Granulator::Init(float sr, float freq, float delay, float grain)
    {
      anchor = BufferSize - (delay * 0.001f * sr);
      grain_length = grain * 0.001f * sr;

      depth = 0.f;

      ga.Init(sr, freq, 0.f, *this);
      gb.Init(sr, freq, 0.5f, *this);
    }

    void Granulator::SetDepth(float d)
    {
      depth = d;
    }

    float Granulator::Read()
    {
      float sample = ga.Read(*this) + gb.Read(*this);
      anchor = (anchor + 1) & (BufferSize - 1);
      return sample;
    }

    /* Engine */

    void Init(float sr)
    {
      float freqs[] = { 25.f, 10.f };
      float delays[] = { 17.f, 10.f };
      float depths[] = { 0.015f, 0.021f };
      float grain_length = 100.f;
      size_t size = 2;

      _params.cloud_size = size;
      _params.dry = _params.wet = -3db;
      _params.feedback = 0.f;

      _buffer.Init();

      for (size_t i = 0; i < _params.cloud_size; ++i) {
        _granulators[i].Init(sr, freqs[i], delays[i], grain_length);
        _granulators[i].SetDepth(depths[i]);
      }
      size_t N = _granulators[0].grain_length;
      for (size_t i = 0; i < N; ++i) {
        _window[i] = sin((M_PI * i) / (float)(N));
      }
    }

    float Read()
    {
      float sample = 0.0f;
      for (size_t i = 0; i < _params.cloud_size; ++i) {
        sample += _granulators[i].Read();
      }
      return sample / float(_params.cloud_size);
    }

    float Process(float x)
    {
      float wet_sample = Read();
      float output = _params.dry * x + _params.wet * wet_sample;
      _buffer.Write(x + _params.feedback * wet_sample);
      return output;
    }
  }
}