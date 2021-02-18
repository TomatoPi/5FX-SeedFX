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

namespace sfx {

  struct Buffer {

    float* buffer;
    size_t length, lengthmod;
    size_t write_h;

    void Init(size_t size);
    void Write(float x);
    float Readf(float t) const;
    float Reads(size_t s) const;
  };

  constexpr inline float db2rms(float db) {
    return powf(10.f, db / 10.f);
  }
}

constexpr float operator"" db(long double db) {
  return sfx::db2rms(db);
}
constexpr float operator"" db(unsigned long long int db) {
  return sfx::db2rms(db);
}

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

namespace sfx {

  /* Buffer */

  void Buffer::Init(size_t size) {
    size_t upbound = 1;
    while (upbound < size) {
      upbound = upbound << 1;
    }
    length = upbound;
    lengthmod = upbound - 1;
    write_h = 0;
    buffer = new float[length];
  }
  void Buffer::Write(float x) {
    buffer[write_h] = x;
    write_h = (write_h + 1) & lengthmod;
  }
  float Buffer::Readf(float t) const {
    size_t ti = static_cast<size_t>(t);
    float tf = t - ti;
    float a = buffer[ti];
    float b = buffer[(ti + 1) & lengthmod];
    return (1.f - tf) * a + tf * b;
  }
  float Buffer::Reads(size_t s) const {
    return buffer[s];
  }
}