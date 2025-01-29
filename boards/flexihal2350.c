/*
  flexihal2350.c - init code for flexihal2350

  Part of grblHAL

  Copyright (c) 2021-2025 Terje Io
  
  grblHAL is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  grblHAL is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with grblHAL. If not, see <http://www.gnu.org/licenses/>.
*/

#include "driver.h"

#if defined(BOARD_FLEXIHAL2350)

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "grbl/hal.h"
#include "grbl/protocol.h"
#include "grbl/settings.h"
#include "grbl/nvs_buffer.h"


void board_init (void)
{

    /*
    settings.motor_fault_enable
    settings.motor_fault_invert
    */

    hal.driver_cap.toolsetter = 1;


}

#endif
