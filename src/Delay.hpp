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
    /// \brief Approx 4s (at 48kHz) buffer for delay
    constexpr const size_t BufferSize = sfx::uppow2(sfx::ms2sample(4'000.f, 48'000.f));

    struct Settings
    {
      float delay = 500.f;

      decibel_gain dry_gain = 0dB;
      decibel_gain wet_gain = -6dB;
      decibel_gain feedback_gain = -3dB;

      bool bypass = true;
    };

    class Engine
    {
    public:

      using Buffer = sfx::Buffer<BufferSize>;

      void Init(float sr, Buffer* buffer, Settings* settings);
      void Reload();

      float Process(float x);

      void setDelay(float ms);
      void setBypass(bool bypass);

      void setDryGain(decibel_gain gain);
      void setWetGain(decibel_gain gain);
      void setFeedbackGain(decibel_gain gain);

    private:

      Buffer* _buffer;
      Settings* _settings;

      size_t _play_h;
      float _sr;
      float _in_gain;

      float _dry;
      float _wet;
      float _feedback;
    };
  }
}

///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////

namespace sfx
{
  namespace Delay
  {
    void Engine::Init(float sr, Buffer* buffer, Settings* settings)
    {
      _buffer = buffer;
      _settings = settings;
      _buffer->Init();
      _sr = sr;
      Reload();
    }
    void Engine::Reload()
    {
      setDelay(_settings->delay);
      setBypass(_settings->bypass);

      setDryGain(_settings->dry_gain);
      setWetGain(_settings->wet_gain);
      setFeedbackGain(_settings->feedback_gain);
    }

    float Engine::Process(float x)
    {
      float wet_sample = _buffer->Read(_play_h);
      float feed_sample = x * _in_gain + wet_sample * _feedback;
      _play_h = (_play_h + 1) & (BufferSize - 1);
      _buffer->Write(feed_sample);
      return x * _dry + wet_sample * _wet;
    }

    void Engine::setDelay(float ms)
    {
      _settings->delay = ms;
      _play_h = (_buffer->write_h + BufferSize - size_t(ms * 0.001f * _sr)) & (BufferSize - 1);
      SettingsDirtyFlag = true;
    }
    void Engine::setBypass(bool bypass)
    {
      _settings->bypass = bypass;
      _in_gain = bypass ? 0.f : 1.f;
      SettingsDirtyFlag = true;
    }

    void Engine::setDryGain(decibel_gain gain)
    {
      _dry = gain.rms();
      _settings->dry_gain = gain;
      SettingsDirtyFlag = true;
    }
    void Engine::setWetGain(decibel_gain gain)
    {
      _wet = gain.rms();
      _settings->wet_gain = gain;
      SettingsDirtyFlag = true;
    }
    void Engine::setFeedbackGain(decibel_gain gain)
    {
      _feedback = gain.rms();
      _settings->feedback_gain = gain;
      SettingsDirtyFlag = true;
    }
  }
}