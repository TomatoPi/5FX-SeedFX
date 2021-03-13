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
 ///  \file Decibel.hpp
 /// 
 ///  \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
 ///  \date 2021-03-13
 ///

#pragma once

#include <cmath>

struct decibel_gain
{
  float value;

  explicit constexpr decibel_gain(long double v = 0.f) : value(v) {}
  explicit constexpr decibel_gain(unsigned long long int v = 0) : value(v) {}

  constexpr inline float rms() const;
  constexpr inline decibel_gain operator- () const;
};

constexpr inline decibel_gain operator+ (const decibel_gain& a, const decibel_gain& b)
{
  return decibel_gain{ (long double)(a.value + b.value) };
}
constexpr inline decibel_gain operator- (const decibel_gain& a, const decibel_gain& b)
{
  return decibel_gain{ (long double)(a.value - b.value) };
}
constexpr inline decibel_gain operator* (float x, const decibel_gain& a)
{
  return decibel_gain{ (long double)(a.value * x) };
}

constexpr decibel_gain operator"" dB(long double db)
{
  return decibel_gain(db);
}
constexpr decibel_gain operator"" dB(unsigned long long int db)
{
  return decibel_gain(db);
}

///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////

constexpr inline float decibel_gain::rms() const
{
  return powf(10.f, value / 10.f);
}
constexpr decibel_gain decibel_gain::operator- () const
{
  return decibel_gain{ -(long double)value };
}