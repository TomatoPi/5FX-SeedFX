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
 ///  \file Looper.hpp
 /// 
 ///  \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
 ///  \date 2021-02-18
 ///

#pragma once

#include "Global.hpp"
#include "Pedalboard.hpp"
#include "Utils.hpp"

#include <dev/sdram.h>
#include <array>

namespace sfx
{
  namespace Looper
  {
    /// \brief At least 5min (at 48kHz) buffer for looper
    constexpr const size_t BufferSize = sfx::uppow2(sfx::ms2sample(4.f * 60'000.f, 48'000.f));
    constexpr const size_t MaxLayerCount = 128;

    struct Settings
    {
      decibel_gain monitor_gain = 0dB;
      decibel_gain playback_gain = -1dB;
    };

    class Engine
    {
    public:

      using Buffer = sfx::Buffer<BufferSize>;

      enum class State
      {
        Idle,
        Recording,
        Overdubing,
        Multiplying,
        Playback,
        Overdubed,
        Oneshot,
        Muted,
      };

    private:

      struct Layer
      {
        size_t buffer_offset; /*!< first sample offset in the buffer */
        size_t length;        /*!< length in samples */

        size_t loop_start_offset;  /*!< first sample offset in the loop */
        size_t block_count_length; /*!< length in loop count, rounded up */

        const Layer* master; /*!< View on the current block length */
        Buffer* buffer;      /*!< Memory block where samples are stored */

        const Layer** longuest_player_ptr; /*!< Pointer to the pointer on the longuest layer */

        Layer(
          size_t buffer_offset = 0, 
          size_t loop_start_offset = 0,
          const Layer* master = nullptr, 
          Buffer* buffer = nullptr,
          const Layer** longuest_player_ptr = nullptr);

        /// \return the sample at given timestamp
        /// \param clock : masterclock timestamp
        /// \param buffer : Bloc mémoire
        float Read(size_t clock) const;

        /// \brief Summ given sample to playhead's position at current timestamp.
        ///   Doesn't modify the layer, only the buffer
        void Overdub(size_t clock, float overdub_sample) const;

        /// \brief Append given sample at the layer's end. 
        ///   Layer is grown bigger, no overlap prevention is performed
        void Append(float sample);

        /// \return playhead's position in the master layer at given timestamp
        size_t _masterhead(size_t clock) const;

        /// \return Playhead's position in this layer at given timestamp
        ///   May be ahead layer's end, when layer's is smaller than the unitary loop
        size_t _playhead(size_t masterhead) const;

        /// \return _playhead's position in the buffer
        size_t _bufferhead(size_t playhead) const;

        /// \return layer's length, aligned with master's layer's length
        size_t _rounded_length() const;

        /// \return indice of the post last sample of this layer
        size_t _post_last_sample() const;

        /// \return true if layer's length is bigger or equal than master's length
        bool _is_full() const;

        /// Note : Pour implémenter un simili double buffering permettant d'annuler un record, il suffit de modifier la methode _bufferhead pouet qu'elle compte du début ou de la fin du buffer
      };
      using LayersArray = std::array<Layer, MaxLayerCount>;

    public:

      Buffer* _buffer;      /*!< main buffer */
      Settings* _settings;  /*!< settings */
      Engine* _master;      /*!< master engine which to refer for synchronisation */

      LayersArray _layers;
      const Layer* _longuest_layer;

      size_t _height;       /* current height in layers stack */
      size_t _stacksize;    /* current layers stack size */
      size_t _master_clock; /* time since rec was pressed */

      State _status, _muteback;
      float _monitor;
      float _playback;

      void Init(float sr, Buffer* buffer, Settings* settings);

      void HitUndo();
      void HitRedo();
      void HitOverdub();
      void HitRecord();
      void HitMute();
      void HitMultiply();
      void HitOneshot();

      float Process(float x);

      void setMonitorGain(decibel_gain gain);
      void setPlaybackGain(decibel_gain gain);

      State GetState();

      void Unstack();
      void TryRestack();

      void StartRecord();
      void CancelRecord();
      void EndRecord();

      bool TryStartOverdub();
      void CancelOverdub();
      void EndOverdub();

      void TryStartMulitply();
      void CancelMultiply();
      void EndMultiply();

      void EnterOneshot();
      void ExitOneshot();

      void StopPlayback();
      void TryReplay();

      void Mute();
      void Unmute();

      float Idle(float x);
      float Record(float x);
      float Overdub(float x);
      float Multiply(float x);
      float Oneshot(float x);

      float Playback(float x);
      float Overdubed(float x);
      float Muted(float x);

      Layer* _masterlayer()
      {
        return _stacksize ? &_layers[0] : nullptr;
      }
      Layer* _lastlayer() 
      {
        return _stacksize ? &_layers[_height - 1] : nullptr;
      }
    };
  };
}

//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////

namespace sfx
{
  namespace Looper
  {
    Engine::Layer::Layer(
      size_t bo /*= 0*/, 
      size_t so /*= 0*/, 
      const Layer* master /*= nullptr*/,
      Buffer* buffer /*= nullptr*/,
      const Layer** longuest_player_ptr /*= nullptr*/)
      :
      buffer_offset(bo), length(0), loop_start_offset(so), block_count_length(0), 
      master(master), buffer(buffer), 
      longuest_player_ptr(longuest_player_ptr)
    {
    }

    float Engine::Layer::Read(size_t clock) const
    {
      size_t playhead(_playhead(clock));
      return (length < playhead) ? 0.f : buffer->Read(_bufferhead(playhead));
    }

    void Engine::Layer::Append(float sample)
    {
      buffer->buffer[_bufferhead(length)] = sample;
      length += 1;
      block_count_length = !!(length % master->length) + length / master->length;
      if ((*longuest_player_ptr)->length < length)
        *longuest_player_ptr = this;
    }
    void Engine::Layer::Overdub(size_t clock, float overdub_sample) const
    {
      size_t playhead(_playhead(clock));
      buffer->buffer[_bufferhead(playhead)] += overdub_sample;
    }
    
    size_t Engine::Layer::_masterhead(size_t clock) const
    {
      return clock % _rounded_length();
    }
    size_t Engine::Layer::_playhead(size_t clock) const
    {
      size_t masterhead(_masterhead(clock));
      return (masterhead + _rounded_length() * !!(masterhead < loop_start_offset)) - loop_start_offset;
    }
    size_t Engine::Layer::_bufferhead(size_t playhead) const
    {
      return buffer_offset + playhead;
    }
    size_t Engine::Layer::_rounded_length() const
    {
      return (block_count_length * master->length);
    }
    size_t Engine::Layer::_post_last_sample() const
    {
      return buffer_offset + length;
    }
    bool Engine::Layer::_is_full() const
    {
      return master->length <= length;
    }


    Engine::State Engine::GetState()
    {
      return _status;
    }

    void Engine::StartRecord()
    {
      _buffer->write_h = 0;

      _height = 0;
      _stacksize = 0;
      _master_clock = 0;

      _layers[0] = Layer(0, 0, &_layers[0], _buffer, &_longuest_layer);
      _longuest_layer = &_layers[0];

      _status = State::Recording;
    }
    void Engine::CancelRecord()
    {
      _status = State::Idle;
    }
    void Engine::EndRecord()
    {
      EndOverdub();
    }

    bool Engine::TryStartOverdub()
    {
      Layer* ml(_masterlayer());
      Layer* ll(_lastlayer());
      if (ll->_post_last_sample() < BufferSize) {
        _layers[_height] = Layer(ll->_post_last_sample(), ml->_masterhead(_master_clock), ml, _buffer, &_longuest_layer);
        _status = State::Overdubing;
        return true;
      }
      else 
        return false;
    }
    void Engine::CancelOverdub()
    {
      _status = 1 == _height ? State::Playback : State::Overdubed;
    }
    void Engine::EndOverdub()
    {
      _height = _height + 1;
      _stacksize = _height;
      _status = 1 == _height ? State::Playback : State::Overdubed;
    }

    void Engine::Unstack()
    {
      _height = _height - 1;
      if (0 == _height) {
        _height = 0;
        _status = State::Playback;
      }
    }

    void Engine::StopPlayback()
    {
      _status = State::Idle;
    }
    void Engine::TryReplay()
    {
      TryRestack();
    }
    void Engine::TryRestack()
    {
      if (_height < _stacksize) {
        _height = _height + 1;
        _status = 1 == _height ? State::Playback : State::Overdubed;
      }
    }

    void Engine::TryStartMulitply()
    {
      if (TryStartOverdub())
        _status = State::Multiplying;
    }
    void Engine::CancelMultiply()
    {
      _status = 1 == _height ? State::Playback : State::Overdubed;
    }
    void Engine::EndMultiply()
    {
      EndOverdub();
    }

    void Engine::EnterOneshot()
    {
      _status = State::Oneshot;
    }
    void Engine::ExitOneshot()
    {
      _status = 1 == _height ? State::Playback : State::Overdubed;
    }

    void Engine::Mute()
    {
      _muteback = _status;
      _status = State::Muted;
    }
    void Engine::Unmute()
    {
      _status = _muteback;
      _muteback = State::Idle;
    }

    float Engine::Idle(float x)
    {
      return _monitor * x; /// passthrought
    }
    float Engine::Record(float x)
    {
      _layers[_height].Append(x);
      if (BufferSize <= _layers[_height]._post_last_sample()) {
        EndRecord();
      }
      return _monitor * x;
    }
    float Engine::Playback(float x)
    {
      return Overdubed(x);
    }
    float Engine::Overdubed(float x)
    {
      float sample = 0;
      for (size_t i = 0; i < _height; ++i)
        sample += _layers[i].Read(_master_clock);
      return sample * _playback + x * _monitor;
    }
    float Engine::Muted(float x)
    {
      return x * _monitor;
    }
    float Engine::Overdub(float x)
    {
      Layer& layer(_layers[_height]);
      if (layer._is_full())
        layer.Overdub(_master_clock, x);
      else
        Record(x);
      return Overdubed(x);
    }
    
    float Engine::Multiply(float x)
    {
      Record(x);
      return Overdubed(x);
    }

    float Engine::Oneshot(float x)
    {
      const size_t longclock(_longuest_layer->_playhead(_master_clock));
      if (longclock == _longuest_layer->length -1)
      {
        _height = 0;
        _status = State::Idle;
        Pedalboard::dirtyFlag = true;
      }
      return Overdubed(x);
    }


    void Engine::Init(float sr, Buffer* buffer, Settings* settings)
    {
      _buffer = buffer;
      _buffer->Init();
      _settings = settings;
      _master = this;

      _layers.fill(Layer());
      _longuest_layer = nullptr;

      _height = 0;
      _stacksize = 0;
      _master_clock = 0;

      _status = State::Idle;
      _muteback = State::Idle;

      setMonitorGain(_settings->monitor_gain);
      setPlaybackGain(_settings->playback_gain);
    }

    float Engine::Process(float x)
    {
      float sample = [this, x] () -> float {
        switch (_status) {
        case State::Idle: return Idle(x);
        case State::Recording: return Record(x);
        case State::Overdubing: return Overdub(x);
        case State::Multiplying: return Multiply(x);
        case State::Playback: return Playback(x);
        case State::Overdubed: return Overdubed(x);
        case State::Oneshot: return Oneshot(x);
        case State::Muted: return Muted(x);
        }
        return x;
      }();
      _master_clock += 1;
      return sample;
    }

    void Engine::HitUndo()
    {
      switch (_status) {
      case State::Idle:
        break;
      case State::Recording:
        CancelRecord();
        break;
      case State::Overdubing:
        CancelOverdub();
        break;
      case State::Multiplying:
        CancelMultiply();
        break;
      case State::Playback:
        StopPlayback();
        break;
      case State::Overdubed:
        Unstack();
        break;
      case State::Oneshot:
        ExitOneshot();
        break;
      case State::Muted:
        Unmute();
        break;
      }
    }
    void Engine::HitRedo()
    {
      switch (_status) {
      case State::Idle:
        TryReplay();
        break;
      case State::Recording:
        break;
      case State::Overdubing:
        break;
      case State::Multiplying:
        break;
      case State::Playback:
      case State::Overdubed:
      case State::Oneshot:
        TryRestack();
        break;
      case State::Muted:
        Unmute();
        HitRedo();
        break;
      }
    }
    void Engine::HitOverdub()
    {
      switch (_status) {
      case State::Idle:
        StartRecord();
        break;
      case State::Recording:
        EndRecord();
        TryStartOverdub();
        break;
      case State::Overdubing:
        EndOverdub();
        break;
      case State::Multiplying:
        EndMultiply();
        TryStartOverdub();
        break;
      case State::Playback:
      case State::Overdubed:
      case State::Oneshot:
        TryStartOverdub();
        break;
      case State::Muted:
        Unmute();
        HitOverdub();
        break;
      }
    }
    void Engine::HitRecord()
    {
      switch (_status) {
      case State::Idle:
        StartRecord();
        break;
      case State::Recording:
        EndRecord();
        break;
      case State::Overdubing:
        CancelOverdub();
        StartRecord();
        break;
      case State::Multiplying:
        CancelMultiply();
        StartRecord();
        break;
      case State::Playback:
      case State::Overdubed:
      case State::Oneshot:
        StartRecord();
        break;
      case State::Muted:
        Unmute();
        HitRecord();
        break;
      }
    }
    void Engine::HitMute()
    {
      switch (_status) {
      case State::Idle:
        break;
      case State::Recording:
        CancelRecord();
        break;
      case State::Overdubing:
        CancelOverdub();
        break;
      case State::Multiplying:
        CancelMultiply();
        break;
      case State::Playback:
      case State::Overdubed:
      case State::Oneshot:
        Mute();
        break;
      case State::Muted:
        Unmute();
        break;
      }
    }
    void Engine::HitMultiply()
    {
      switch (_status) {
      case State::Idle:
        StartRecord();
        break;
      case State::Recording:
        EndRecord();
        TryStartMulitply();
        break;
      case State::Overdubing:
        EndOverdub();
        TryStartMulitply();
        break;
      case State::Multiplying:
        EndMultiply();
        break;
      case State::Playback:
      case State::Overdubed:
      case State::Oneshot:
        TryStartMulitply();
        break;
      case State::Muted:
        Unmute();
        TryStartMulitply();
        break;
      }
    }
    void Engine::HitOneshot()
    {
      switch (_status) {
      case State::Idle:
        StartRecord();
        break;
      case State::Recording:
        EndRecord();
        EnterOneshot();
        break;
      case State::Overdubing:
        EndOverdub();
        EnterOneshot();
        break;
      case State::Multiplying:
        EndMultiply();
        EnterOneshot();
        break;
      case State::Playback:
      case State::Overdubed:
      case State::Oneshot:
        EnterOneshot();
        break;
      case State::Muted:
        Unmute();
        EnterOneshot();
        break;
      }
    }

    void Engine::setMonitorGain(decibel_gain gain)
    {
      _monitor = gain.rms();
      _settings->monitor_gain = gain;
      SettingsDirtyFlag = true;
    }
    void Engine::setPlaybackGain(decibel_gain gain)
    {
      _playback = gain.rms();
      _settings->playback_gain = gain;
      SettingsDirtyFlag = true;
    }
  }
}