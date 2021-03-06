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
 ///  \file Delay.hpp
 /// 
 ///  \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
 ///  \date 2021-02-21
 ///

#pragma once

#include "Global.hpp"
#include "Utils.hpp"

#include <dev/sdram.h>

namespace sfx
{
  namespace Delay
  {
    Buffer<BufferSize> DSY_SDRAM_BSS _buffer;
    size_t _play_h;
    float _sr;
    float _in_gain;

    void Init(float sr);
    void Reload();

    float Process(float x);

    void setDelay(float ms);
    void setBypass(bool bypass);
  }
}

///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////

namespace sfx
{
  namespace Delay
  {
    void Init(float sr)
    {
      _buffer.Init();
      _sr = sr;
      Reload();
    }
    void Reload()
    {
      setDelay(Settings.Delay.delay);
      setBypass(Settings.Delay.bypass);
    }

    float Process(float x)
    {
      float wet_sample = _buffer.Read(_play_h);
      float feed_sample = x * _in_gain + wet_sample * Settings.Delay.feedback_gain;
      _play_h = (_play_h + 1) & (BufferSize - 1);
      _buffer.Write(feed_sample);
      return x * Settings.Delay.dry_gain + wet_sample * Settings.Delay.wet_gain;
    }

    void setDelay(float ms)
    {
      Settings.Delay.delay = ms;
      _play_h = (_buffer.write_h + BufferSize - size_t(ms * 0.001f * _sr)) & (BufferSize - 1);
      SettingsDirtyFlag = true;
    }
    void setBypass(bool bypass)
    {
      Settings.Delay.bypass = bypass;
      _in_gain = bypass ? 0.f : 1.f;
      SettingsDirtyFlag = true;
    }
  }
}