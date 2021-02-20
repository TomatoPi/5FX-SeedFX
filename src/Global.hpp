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
 ///  \file Global.hpp
 /// 
 ///  \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
 ///  \date 2021-02-20
 ///

#pragma once

#include "Utils.hpp"
#include <daisy_seed.h>
#include <per/uart.h>

namespace sfx
{
  namespace Chorus
  {
    constexpr const size_t BufferSize = 1L << 16;
    constexpr const size_t GrainMaxSize = 1L << 15;
    constexpr const size_t CloudMaxSize = 8;
  }
  namespace Looper
  {
    /// \brief Approx 120s (at 48kHz) buffer for looper
    constexpr const size_t BufferSize = sfx::uppow2(sfx::ms2sample(120'000.f, 48'000.f));
  }

  daisy::DaisySeed Hardware;
  struct
  {
    struct
    {
      float delays[Chorus::CloudMaxSize] = { 11.f, 17.f, 13.f, 5.f, 7.f, 19.f, 23.f, 29.f };
      float frequencies[Chorus::CloudMaxSize] = { 25.f, 10.f };
      float depths[Chorus::CloudMaxSize] = { 0.015f, 0.021f };

      float grain_size_ms = 100.f;
      float dry_gain = -3dB;
      float wet_gain = -3dB;
      float feedback_gain = 0.f;

      size_t cloud_size = 2;
      bool bypass = false;
    } Chorus;
    struct
    {
      float monitor_gain = 0dB;
      float playback_gain = -3dB;
    } Looper;
  } Settings;

  bool SettingsDirtyFlag = false;
}