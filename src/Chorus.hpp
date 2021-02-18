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

#include <cmath>
#include <stddef.h>
#include <type_traits>

namespace sfx {

  template<typename T>
  inline constexpr bool ispowof2(T x) {
    static_assert(std::is_integral<T>::value, "T must be integral");
    return x && !(x & (x - static_cast<T>(1)));
  }

  template <size_t BufferSize>
  struct Buffer {
    static_assert(ispowof2(BufferSize), "BufferSize MUST be a power of 2");

    float buffer[BufferSize];
    size_t write_h;

    void Init();
    void Write(float x);
    float Read(float t) const;
  };

  template <
    size_t BufferSize,
    size_t GrainSizeMax,
    size_t CloudSizeMax,
    typename LFO>
    struct ChorusEngine {

    struct Granulator {

      struct Grain {
        LFO lfo;
        size_t time;
        float read_h;

        void Init(float sr, float freq, float phase, const Granulator& g);
        float Read(
          const Granulator& g,
          const float* window,
          const Buffer<BufferSize>& buffer);
      };

      void Init(float sr, float freq, float delay, float grain);
      void SetDepth(float d);
      float Read(
        const float* window,
        const Buffer<BufferSize>& buffer);

      Grain ga, gb;
      size_t anchor, grain_length;
      float depth;
    };


    Buffer<BufferSize> buffer;
    Granulator granulators[CloudSizeMax];
    float *window;
    size_t size;

    float dry;
    float wet;
    float feedback;

    void Init(float sr, float grain, float* fs, float* ds, size_t size);
    void SetDepths(float* depths);
    float Read();
    float Process(float x);
  };
}

/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////

namespace sfx {

  /* Buffer */

  template <size_t BufferSize>
  void Buffer<BufferSize>::Init() {
    write_h = 0;
  }
  template <size_t BufferSize>
  void Buffer<BufferSize>::Write(float x) {
    write_h = (write_h + 1) & (BufferSize - 1);
    buffer[write_h] = x;
  }
  template <size_t BufferSize>
  float Buffer<BufferSize>::Read(float t) const {
    size_t ti = static_cast<size_t>(t);
    float tf = t - ti;
    float a = buffer[ti];
    float b = buffer[(ti + 1) & (BufferSize - 1)];
    return (1.f - tf) * a + tf * b;
  }

  /* Grain */

  template <size_t Bs, size_t Gs, size_t Cs, typename LFO>
  void ChorusEngine<Bs, Gs, Cs, LFO>::Granulator::Grain::Init(float sr, float freq, float phase, const Granulator& g) {

    time += g.grain_length * phase;
    read_h = static_cast<float>(g.anchor);

    lfo.Init(sr);
    lfo.SetFreq(freq);
  }

  template <size_t Bs, size_t Gs, size_t Cs, typename LFO>
  float ChorusEngine<Bs, Gs, Cs, LFO>::Granulator::Grain::Read(
    const Granulator& g,
    const float* window,
    const Buffer<Bs>& buffer) {

    time = (time + 1) % g.grain_length;
    if (0 == time) {
      read_h = static_cast<float>(g.anchor);
    } else {
      read_h += 1.f;
    }
    read_h = fmod(read_h + g.depth * lfo.Process(), Bs);
    return window[time] * buffer.Read(read_h);
  }

  /* Granulator */

  template <size_t Bs, size_t Gs, size_t Cs, typename LFO>
  void ChorusEngine<Bs, Gs, Cs, LFO>::Granulator::Init(float sr, float freq, float delay, float grain) {

    anchor = Bs - (delay * 0.001f * sr);
    grain_length = grain * 0.001f * sr;

    depth = 0.f;

    ga.Init(sr, freq, 0.f, *this);
    gb.Init(sr, freq, 0.5f, *this);
  }

  template <size_t Bs, size_t Gs, size_t Cs, typename LFO>
  void ChorusEngine<Bs, Gs, Cs, LFO>::Granulator::SetDepth(float d) {
    depth = d;
  }

  template <size_t Bs, size_t Gs, size_t Cs, typename LFO>
  float ChorusEngine<Bs, Gs, Cs, LFO>::Granulator::Read(
    const float* window,
    const Buffer<Bs>& buffer) {
    anchor = (anchor + 1) & (Bs - 1);
    return ga.Read(*this, window, buffer) + gb.Read(*this, window, buffer);
  }

  /* Engine */

  template <size_t Bs, size_t Gs, size_t Cs, typename LFO>
  void ChorusEngine<Bs, Gs, Cs, LFO>::Init(float sr, float grain, float* fs, float* ds, size_t s) {
    size = s;
    buffer.Init();
    for (size_t i = 0; i < size; ++i) {
      granulators[i].Init(sr, fs[i], ds[i], grain);
    }
    window = new float[granulators[0].grain_length];
  }

  template <size_t Bs, size_t Gs, size_t Cs, typename LFO>
  void ChorusEngine<Bs, Gs, Cs, LFO>::SetDepths(float* depths) {
    for (size_t i = 0; i < size; ++i) {
      granulators[i].SetDepth(depths[i]);
    }
  }

  template <size_t Bs, size_t Gs, size_t Cs, typename LFO>
  float ChorusEngine<Bs, Gs, Cs, LFO>::Read() {
    float sample = 0.0f;
    for (size_t i = 0; i < size; ++i) {
      sample += granulators[i].Read(window, buffer);
    }
    return sample / float(size);
  }

  template <size_t Bs, size_t Gs, size_t Cs, typename LFO>
  float ChorusEngine<Bs, Gs, Cs, LFO>::Process(float x) {
    float wet_sample = Read();
    float output = dry * x + wet * wet_sample;
    buffer.Write(x + feedback * wet_sample);
    return output;
  }
}