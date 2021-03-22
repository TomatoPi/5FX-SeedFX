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
 ///  \file Save.hpp
 /// 
 ///  \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
 ///  \date 2021-02-20
 ///

#pragma once

#include "Global.hpp"
#include <per/qspi.h>
#include <cstring>

namespace sfx
{
  namespace persist
  {
    constexpr const uint32_t QSPI_BLOCK_SIZE = 4096;

    constexpr const uint32_t SaveSectionSize = roundup(sizeof(GlobalSettings), QSPI_BLOCK_SIZE);
    constexpr const uint32_t SaveSectionBegin = 0x9000'0000;
    constexpr const uint32_t SaveSectionEnd = SaveSectionBegin + SaveSectionSize;
    uint8_t DSY_QSPI_BSS SaveSectionBlock[SaveSectionSize];

    void SaveToQSPI();
    void LoadFromQSPI();
  }
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

namespace sfx
{
  namespace persist
  {
    void SaveToQSPI()
    {
      dsy_qspi_deinit();
      Hardware.qspi_handle.mode = DSY_QSPI_MODE_INDIRECT_POLLING;
      dsy_qspi_init(&Hardware.qspi_handle);

      dsy_qspi_erase(SaveSectionBegin, SaveSectionEnd);
      dsy_qspi_write(
        SaveSectionBegin,
        sizeof(GlobalSettings),
        reinterpret_cast<uint8_t*>(&GlobalSettings));

      dsy_qspi_deinit();
    }

    void LoadFromQSPI()
    {
      dsy_qspi_deinit();
      Hardware.qspi_handle.mode = DSY_QSPI_MODE_DSY_MEMORY_MAPPED;
      dsy_qspi_init(&Hardware.qspi_handle);

      memcpy(
        reinterpret_cast<void*>(&GlobalSettings),
        SaveSectionBlock,
        sizeof(GlobalSettings));

      dsy_qspi_deinit();
    }
  }
}