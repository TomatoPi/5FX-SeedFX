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
 ///  \file Chorus.cpp
 /// 
 ///  \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
 ///  \date 2021-02-18
 ///

#pragma once

#include "Global.hpp"
#include "Utils.hpp"

#include <dev/sdram.h>
#include <Utility/smooth_random.h>

#include <cmath>
#include <stddef.h>
#include <cstring>

namespace sfx
{
  namespace Chorus
  {
    constexpr const size_t BufferSize = sfx::uppow2(sfx::ms2sample(1'000.f, 48'000.f));
    constexpr const size_t GrainMaxSize = 1L << 15;
    constexpr const size_t CloudMaxSize = 8;

    struct Settings
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
    };

    class Engine
    {
    public:

      using Buffer = sfx::Buffer<BufferSize>;
      using Window = float[GrainMaxSize];
      using LFO = daisysp::SmoothRandomGenerator;

      void Init(float samplerate, Buffer* buffer, float* window, Settings* settings);
      void Reload();

      float Process(float x);

      void setFrequency(int voice, float frequency);
      void setDelay(int voice, float delay);
      void setDepth(int voice, float depth);

      void setGrainSize(float size);
      void setDryGain(decibel_gain gain);
      void setWetGain(decibel_gain gain);
      void setFeedbackGain(decibel_gain gain);

      void setCloudSize(size_t size);
      void setBypass(bool bypass);

    private:

      float AccumulateVoices();

      Buffer* _buffer;
      float* _window;
      Settings* _settings;

      LFO _lfos[CloudMaxSize];
      size_t _anchors[CloudMaxSize];
      size_t _times[CloudMaxSize * 2];
      float _read_hs[CloudMaxSize * 2];

      size_t _grain_length;
      float _sr;

      float _dry;
      float _wet;
      float _feedback;
    };
  }
}

/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////

namespace sfx
{
  namespace Chorus
  {
    float Engine::AccumulateVoices()
    {
      float sample = 0.f;
      for (size_t i = 0; i < _settings->cloud_size; ++i) {
        for (size_t c = 0; c < 2; ++c) {
          size_t time = _times[2 * i + c];
          float read_h = _read_hs[2 * i + c];
          sample += _window[time] * _buffer->Read(read_h);
          time = (time + 1) % _grain_length;
          if (0 == time) {
            read_h = static_cast<float>(_anchors[i]);
          } else {
            read_h += 1.f;
          }
          _times[2 * i + c] = time;
          _read_hs[2 * i + c] = fmod(
            read_h + _settings->depths[i] * _lfos[i].Process(), BufferSize);
        }
        _anchors[i] = (_anchors[i] + 1) & (BufferSize - 1);
      }
      return sample / (float)_settings->cloud_size;
    }

    float Engine::Process(float x)
    {
      float wet_sample = AccumulateVoices();
      float output = _dry * x + _wet * wet_sample;
      _buffer->Write(x + _feedback * wet_sample);
      return _settings->bypass ? x : output;
    }

    void Engine::Init(float samplerate, Buffer* buffer, float* window, Settings* settings)
    {
      _buffer = buffer;
      _window = window;
      _settings = settings;

      _sr = samplerate;
      _buffer->Init();
      memset(_window, 0, GrainMaxSize * sizeof(float));
      for (size_t i = 0; i < CloudMaxSize; ++i)
        _lfos[i].Init(samplerate);
      Reload();
    }
    void Engine::Reload()
    {
      setGrainSize(_settings->grain_size_ms);
      setDryGain(_settings->dry_gain);
      setWetGain(_settings->wet_gain);
      setFeedbackGain(_settings->feedback_gain);

      setCloudSize(_settings->cloud_size);
      setBypass(_settings->bypass);

      for (size_t i = 0; i < _settings->cloud_size; ++i) {
        setFrequency(i, _settings->frequencies[i]);
        setDelay(i, _settings->delays[i]);
        setDepth(i, _settings->depths[i]);
      }
    }

    void Engine::setFrequency(int i, float frequency)
    {
      _settings->frequencies[i] = frequency;
      _lfos[i].SetFreq(frequency);
      SettingsDirtyFlag = true;
    }
    void Engine::setDelay(int i, float delay)
    {
      _settings->delays[i] = delay;
      _anchors[i] = (_buffer->write_h + BufferSize - size_t(delay * 0.001f * _sr)) & (BufferSize - 1);
      _read_hs[2 * i + 0] = static_cast<size_t>(_anchors[i]);
      _read_hs[2 * i + 1] = static_cast<size_t>(_anchors[i]);
      SettingsDirtyFlag = true;
    }
    void Engine::setDepth(int i, float depth)
    {
      _settings->depths[i] = depth;
      SettingsDirtyFlag = true;
    }

    void Engine::setGrainSize(float size)
    {
      _settings->grain_size_ms = size;
      _grain_length = _settings->grain_size_ms * 0.001f * _sr;
      for (size_t i = 0; i < _settings->cloud_size; ++i) {
        _times[2 * i + 0] = 0;
        _times[2 * i + 1] = _grain_length >> 1;
      }
      for (size_t i = 0; i < _grain_length; ++i) {
        _window[i] = sin((M_PI * i) / (float)(_grain_length));
      }
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

    void Engine::setCloudSize(size_t size)
    {
      _settings->cloud_size = size;
      SettingsDirtyFlag = true;
    }
    void Engine::setBypass(bool bypass)
    {
      _settings->bypass = bypass;
      SettingsDirtyFlag = true;
    }
  }
}