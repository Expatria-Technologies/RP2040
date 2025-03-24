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
    #if 1
    hal.driver_cap.toolsetter = 1;
    gpio_set_function(SPI_MOSI_PIN, GPIO_FUNC_SIO);
    gpio_set_dir(SPI_MOSI_PIN, 1);
    gpio_put(SPI_MOSI_PIN,1);
    gpio_set_function(SPI_MOSI_PIN, GPIO_FUNC_SIO);
    gpio_set_dir(SPI_MISO_PIN, 1);
    gpio_put(SPI_MISO_PIN,1);  
    gpio_set_function(SPI_SCK_PIN, GPIO_FUNC_SIO);
    gpio_set_dir(SPI_SCK_PIN, 1);
    gpio_put(SPI_SCK_PIN,1);      
    gpio_set_function(SD_CS_PIN, GPIO_FUNC_SIO);
    gpio_set_dir(SD_CS_PIN, 1);
    gpio_put(SD_CS_PIN,1);
    gpio_set_function(33, GPIO_FUNC_SIO);
    gpio_set_dir(33, 1);
    gpio_put(33,1);


    volatile uint32_t dly = 1000;
    volatile uint32_t count = 100;

    while(--dly)
      tight_loop_contents();
    
      while(--count) {
        gpio_put(SPI_SCK_PIN,1);        
        dly = 100;  // Reset dly before first delay
        while(--dly)    
          tight_loop_contents();

            gpio_put(SPI_SCK_PIN,0);        
        dly = 100;  // Reset dly before second delay
        while(--dly)
          tight_loop_contents();;
      }

    sdcard_getfs(); // Mounts SD card if not already mounted      
    #endif

}

#endif
