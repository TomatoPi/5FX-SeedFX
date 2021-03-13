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
#include "Decibel.hpp"

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
  namespace Delay
  {
    /// \brief Approx 4s (at 48kHz) buffer for delay
    constexpr const size_t BufferSize = sfx::uppow2(sfx::ms2sample(4'000.f, 48'000.f));
  }

  daisy::DaisySeed Hardware;
  struct
  {
    struct {
      decibel_gain input_gain = 0dB;
      decibel_gain output_gain = 0dB;
    } Channel0, Channel1;

    struct
    {
      float delays[Chorus::CloudMaxSize] = { 11.f, 17.f, 29.f, 5.f, 7.f, 19.f, 23.f, 13.f };
      float frequencies[Chorus::CloudMaxSize] = { 50.f, 20.f, 5.f };
      float depths[Chorus::CloudMaxSize] = { 0.010f, 0.014f, 0.02f };

      float grain_size_ms = 100.f;
      decibel_gain dry_gain = -0dB;
      decibel_gain wet_gain = -0dB;
      decibel_gain feedback_gain = -100dB;

      size_t cloud_size = 3;
      bool bypass = false;
    } Chorus;

    struct
    {
      decibel_gain monitor_gain = 0dB;
      decibel_gain playback_gain = -1dB;
    } Looper;

    struct
    {
      float delay = 500.f;

      decibel_gain dry_gain = 0dB;
      decibel_gain wet_gain = -6dB;
      decibel_gain feedback_gain = -3dB;

      bool bypass = false;
    } Delay;

  } Settings;

  bool SettingsDirtyFlag = false;
}