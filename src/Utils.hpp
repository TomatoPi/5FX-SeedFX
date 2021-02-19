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
 ///  \file Utils.hpp
 /// 
 ///  \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
 ///  \date 2021-02-18
 ///

#pragma once
#include <cmath>
#include <dev/sdram.h>

namespace sfx
{
  template <size_t Size>
  struct Buffer
  {
    float buffer[Size];
    size_t write_h;

    void Init();
    void Write(float x);
    float Read(float t) const;
    float Read(size_t s) const;
  };

  constexpr inline float db2rms(float db)
  {
    return powf(10.f, db / 10.f);
  }
  constexpr inline size_t ms2sample(float ms, float sr)
  {
    return ms * 0.001f * sr;
  }
  constexpr inline size_t uppow2(size_t n)
  {
    return 1 < n ? uppow2(n >> 1) << 1 : 1;
  }
}

constexpr float operator"" dB(long double db)
{
  return sfx::db2rms(db);
}
constexpr float operator"" dB(unsigned long long int db)
{
  return sfx::db2rms(db);
}

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

namespace sfx
{
  /* Buffer */

  template <size_t Size>
  void Buffer<Size>::Init()
  {
    write_h = 0;
  }
  template <size_t Size>
  void Buffer<Size>::Write(float x)
  {
    buffer[write_h] = x;
    write_h = (write_h + 1) & (Size - 1);
  }
  template <size_t Size>
  float Buffer<Size>::Read(float t) const
  {
    size_t ti = static_cast<size_t>(t);
    float tf = t - ti;
    float a = buffer[ti];
    float b = buffer[(ti + 1) & (Size - 1)];
    return (1.f - tf) * a + tf * b;
  }
  template <size_t Size>
  float Buffer<Size>::Read(size_t s) const
  {
    return buffer[s];
  }
}