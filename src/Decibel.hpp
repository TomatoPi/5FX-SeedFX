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
#include <type_traits>

struct decibel_gain
{
  float value;

  template <typename Numeric>
  explicit constexpr decibel_gain(Numeric v = static_cast<Numeric>(0)) :
    value(static_cast<float>(v))
  {
  }

  constexpr inline float rms() const
  {
    return powf(10.f, value / 10.f);
  }
  constexpr inline decibel_gain operator- () const
  {
    return decibel_gain{ -(long double)value };
  }
};

constexpr decibel_gain operator"" dB(long double db)
{
  return decibel_gain(db);
}
constexpr decibel_gain operator"" dB(unsigned long long int db)
{
  return decibel_gain(db);
}

constexpr inline decibel_gain operator+ (const decibel_gain& a, const decibel_gain& b)
{
  return decibel_gain{ (long double)(a.value + b.value) };
}
constexpr inline decibel_gain operator- (const decibel_gain& a, const decibel_gain& b)
{
  return decibel_gain{ (long double)(a.value - b.value) };
}
template <typename Numeric>
constexpr inline decibel_gain operator* (Numeric x, const decibel_gain& a)
{
  static_assert(std::is_arithmetic<Numeric>::value, "x must be a numeric value");
  return decibel_gain{ (long double)(a.value * x) };
}