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
 ///  \date 2021-02-19
 ///

#pragma once
#include "Utils.hpp"

namespace sfx
{
  template <size_t BufferSize>
  struct LooperEngine
  {
    using Buffer = sfx::Buffer<BufferSize>;
    Buffer buffer;
    size_t play_h, rec_length;
    float dry, wet;
    bool recording;
    bool playing;

    void Init(float sr, float maxrec);

    void StartRecord();
    void StopRecord();

    void StartPlayback();
    void StopPlayback();

    float Process(float x);
    void Record(float x);
    float Playback();
  };
}

///////////////////////////////////////////////////////////////////////

namespace sfx
{
  template <size_t BufferSize>
  void LooperEngine<BufferSize>::Init(float sr, float maxrec)
  {
    buffer.Init();
    play_h = rec_length = 0;
    dry = wet = 1.f;
    recording = playing = false;
  }
}