/*

  PCA9654E.c - driver code for RP2040 ARM processor

  I2C I/O expander, PCA9654

  Part of grblHAL

  Copyright (c) 2018-2023 Terje Io

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "driver.h"

#if IOEXPAND_ENABLE == 2

#include "ioexpand.h"
#include "i2c.h"

#define IOEX_ADDRESS (0x40 >> 1)
#define READ_INPUT   0
#define RW_OUTPUT    1
#define RW_INVERSION 2
#define RW_CONFIG    3

void ioexpand_init (void)
{
    uint8_t cmd[2];

    // 0 = output, 1 = input
    // TODO: move to driver.h?
    const ioexpand_t cfg = {0};

    cmd[0] = RW_CONFIG;
    cmd[1] = cfg.mask;
    i2c_send(IOEX_ADDRESS, cmd, 2, true);

    cmd[0] = RW_INVERSION;
    cmd[1] = 0;
    i2c_send(IOEX_ADDRESS, cmd, 2, true);
}

void ioexpand_out (ioexpand_t pins)
{
    uint8_t cmd[2];

    cmd[0] = RW_OUTPUT;
    cmd[1] = pins.mask;

    i2c_send(IOEX_ADDRESS, cmd, 2, true);
}

ioexpand_t ioexpand_in (void)
{
    ioexpand_t pins = {0};
    uint8_t cmd[4] = {0}; // Use 4 bytes to match 32-bit uint32_t
    cmd[0] = READ_INPUT;
    
    i2c_receive(IOEX_ADDRESS, cmd, 4, true);
    
    // Convert received bytes to 32-bit value
    pins.mask = (cmd[3] << 24) | (cmd[2] << 16) | (cmd[1] << 8) | cmd[0];
    
    return pins;

}

#endif
