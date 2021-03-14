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
 ///  \file Pedalboard.hpp
 /// 
 ///  \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
 ///  \date 2021-03-05
 ///

#pragma once

#include "Global.hpp"

#include "Chorus.hpp"
#include "Delay.hpp"
#include "Looper.hpp"

#include <functional>
#include <cstdint>
#include <unordered_map>
#include <array>

namespace sfx
{
  namespace Pedalboard
  {
    namespace Builtin
    {
      const auto identity = [](auto x) -> decltype(x) { return x; };
    }

    constexpr const size_t SwitchCount = 16;

    using SwitchCallback = std::function<void(uint8_t, bool)>;
    using LedBinding = std::function<bool(bool)>;

    std::unordered_map<uint8_t, SwitchCallback> _switches;
    std::unordered_map<uint8_t, LedBinding> _leds;
    std::array<bool, SwitchCount> _states;

    bool dirtyFlag = false;

    void setLed(uint8_t id, bool state);
    void bindSwitch(uint8_t id, const SwitchCallback& callback);
    void bindSwitchOnFall(uint8_t id, const std::function<void(void)>& callback);
    void bindLed(uint8_t id, const LedBinding& binding);

    void bindSwitchAsBypass(
      uint8_t id,
      std::function<bool(void)> isbypassed,
      std::function<void(bool)> setbypass);

    void Init();
    void UpdateLeds();
    void UpdateSwitch(uint8_t id, bool state);
  }
}

/////////////////////////////////////////////////////////////////////////////////
namespace sfx
{
  namespace Pedalboard
  {
    void _BindSwitches()
    {
      const struct
      {
        uint8_t Delay = 0;
        uint8_t Chorus = 1;
        uint8_t Overdub = 6;
        uint8_t Record = 7;
        uint8_t Undo = 14;
        uint8_t Redo = 15;
      } Bindings;

      bindSwitchAsBypass(
        Bindings.Delay, []() -> bool { return Settings.Delay.bypass; }, Delay::setBypass);
      bindSwitchAsBypass(
        Bindings.Chorus, []() -> bool { return Settings.Chorus.bypass; }, Chorus::setBypass);

      bindLed(Bindings.Record,
        [](bool) -> bool { return Looper::State::Recording == Looper::_status; });
      bindSwitchOnFall(Bindings.Record, Looper::HitRecord);

      bindLed(Bindings.Overdub,
        [](bool) -> bool { return Looper::State::Overdubing == Looper::_status; });
      bindSwitchOnFall(Bindings.Overdub, Looper::HitOverdub);

      bindLed(Bindings.Undo,
        [](bool) -> bool
        {
          return Looper::State::Playback == Looper::_status
            || Looper::State::Overdubed == Looper::_status;
        });
      bindSwitchOnFall(Bindings.Undo, Looper::HitUndo);

      bindLed(Bindings.Redo,
        [](bool) -> bool
        {
          return
            (Looper::State::Playback == Looper::_status && 0 < Looper::_stacksize)
            || (Looper::State::Overdubed == Looper::_status && Looper::_height < Looper::_stacksize)
            || (Looper::State::Idle == Looper::_status && 0 < Looper::_rec_length);
        });
      bindSwitchOnFall(Bindings.Redo, Looper::HitRedo);
    }

    void bindSwitch(uint8_t id, const SwitchCallback& callback)
    {
      _switches[id] = callback;
    }
    void bindSwitchOnFall(uint8_t id, const std::function<void(void)>& callback)
    {
      _switches[id] = [callback](uint8_t, bool state) -> void { if (state) callback(); };
    }
    void bindLed(uint8_t id, const LedBinding& binding)
    {
      _leds[id] = binding;
    }

    void bindSwitchAsBypass(
      uint8_t id,
      std::function<bool(void)> isbypassed,
      std::function<void(bool)> setbypass)
    {
      bindSwitch(
        id,
        [setbypass, isbypassed](uint8_t, bool state) -> void
        {
          if (state) setbypass(!isbypassed());
        });
      bindLed(id,
        [isbypassed](bool) -> bool { return !isbypassed(); });
    }

    void Init()
    {
      _BindSwitches();
      _states.fill(false);
      for (const auto& [id, callback] : _switches) {
        callback(id, false);
      }
      for (const auto& [id, binding] : _leds) {
        setLed(id, binding(false));
      }
    }
    void UpdateLeds()
    {
      for (const auto& [id, binding] : _leds) {
        setLed(id, binding(_states[id]));
      }
    }
    void UpdateSwitch(uint8_t id, bool state)
    {
      _states[id] = state;
      if (auto itr = _switches.find(id); _switches.end() != itr) {
        auto [_, callback] = *itr;
        callback(id, state);
        if (auto itr = _leds.find(id); _leds.end() != itr) {
          auto [_, binding] = *itr;
          setLed(id, binding(state));
        }
      }
      dirtyFlag = true;
    }
  }
}