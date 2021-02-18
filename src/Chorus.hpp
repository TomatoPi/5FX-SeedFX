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
 ///  \file Chorus.hpp
 /// 
 ///  \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
 ///  \date 2021-02-18
 ///

#pragma once

#include "Utils.hpp"

#include <cmath>
#include <stddef.h>
#include <type_traits>

namespace sfx
{
  template <size_t CloudSizeMax, typename LFO>
  struct ChorusEngine
  {
    struct Granulator
    {
      struct Grain
      {
        LFO lfo;
        size_t time;
        float read_h;

        void Init(float sr, float freq, float phase, const Granulator& g);
        float Read(
          const Granulator& g,
          const float* window,
          const Buffer& buffer);
      };

      void Init(float sr, float freq, float delay, float grain, size_t bufferlength);
      void SetDepth(float d);
      float Read(
        const float* window,
        const Buffer& buffer);

      Grain ga, gb;
      size_t anchor, grain_length;
      float depth;
    };

    Granulator granulators[CloudSizeMax];
    Buffer buffer;
    float* window;
    size_t size;

    float dry;
    float wet;
    float feedback;

    void Init(
      float sr, float grain,
      float* fs, float* ds,
      float maxlength,
      size_t size);
    void SetDepths(float* depths);
    float Read();
    float Process(float x);
  };
}

/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////

namespace sfx
{

  /* Grain */

  template <size_t CloudSizeMax, typename LFO>
  void ChorusEngine<CloudSizeMax, LFO>::Granulator::Grain::Init(float sr, float freq, float phase, const Granulator& g)
  {

    time += g.grain_length * phase;
    read_h = static_cast<float>(g.anchor);

    lfo.Init(sr);
    lfo.SetFreq(freq);
  }

  template <size_t CloudSizeMax, typename LFO>
  float ChorusEngine<CloudSizeMax, LFO>::Granulator::Grain::Read(
    const Granulator& g,
    const float* window,
    const Buffer& buffer)
  {

    float sample = window[time] * buffer.Readf(read_h);
    time = (time + 1) % g.grain_length;
    if (0 == time) {
      read_h = static_cast<float>(g.anchor);
    } else {
      read_h += 1.f;
    }
    read_h = fmod(read_h + g.depth * lfo.Process(), buffer.length);
    return sample;
  }

  /* Granulator */

  template <size_t CloudSizeMax, typename LFO>
  void ChorusEngine<CloudSizeMax, LFO>::Granulator::Init(
    float sr, float freq, float delay, float grain, size_t bufferlength)
  {

    anchor = bufferlength - (delay * 0.001f * sr);
    grain_length = grain * 0.001f * sr;

    depth = 0.f;

    ga.Init(sr, freq, 0.f, *this);
    gb.Init(sr, freq, 0.5f, *this);
  }

  template <size_t CloudSizeMax, typename LFO>
  void ChorusEngine<CloudSizeMax, LFO>::Granulator::SetDepth(float d)
  {
    depth = d;
  }

  template <size_t CloudSizeMax, typename LFO>
  float ChorusEngine<CloudSizeMax, LFO>::Granulator::Read(
    const float* window,
    const Buffer& buffer)
  {
    float sample = ga.Read(*this, window, buffer) + gb.Read(*this, window, buffer);
    anchor = (anchor + 1) & buffer.lengthmod;
    return sample;
  }

  /* Engine */

  template <size_t CloudSizeMax, typename LFO>
  void ChorusEngine<CloudSizeMax, LFO>::Init(
    float sr, float grain,
    float* fs, float* ds,
    float maxlength,
    size_t s)
  {
    size = s;
    buffer.Init(maxlength * 0.001f * sr);
    for (size_t i = 0; i < size; ++i) {
      granulators[i].Init(sr, fs[i], ds[i], grain, buffer.length);
    }
    window = new float[granulators[0].grain_length];
  }

  template <size_t CloudSizeMax, typename LFO>
  void ChorusEngine<CloudSizeMax, LFO>::SetDepths(float* depths)
  {
    for (size_t i = 0; i < size; ++i) {
      granulators[i].SetDepth(depths[i]);
    }
  }

  template <size_t CloudSizeMax, typename LFO>
  float ChorusEngine<CloudSizeMax, LFO>::Read()
  {
    float sample = 0.0f;
    for (size_t i = 0; i < size; ++i) {
      sample += granulators[i].Read(window, buffer);
    }
    return sample / float(size);
  }

  template <size_t CloudSizeMax, typename LFO>
  float ChorusEngine<CloudSizeMax, LFO>::Process(float x)
  {
    float wet_sample = Read();
    float output = dry * x + wet * wet_sample;
    buffer.Write(x + feedback * wet_sample);
    return output;
  }
}