/*

  ioexpand.h - driver code for RP2040 ARM processor

  I2C I/O expander

  Part of grblHAL

  Copyright (c) 2018-2022 Terje Io

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

#ifndef _IOEXPAND_H_
#define _IOEXPAND_H_

#include "driver.h"

#define ioex_out(pin) ioex_outN(pin)
#define ioex_outN(pin) io_expander.out ## pin
#define ioex_in(pin) ioex_inN(pin)
#define ioex_inN(pin) io_expander.in ## pin

#if IOEXPAND_ENABLE == 2

typedef union {
    uint32_t mask;
    struct {
        uint32_t out0 :1,
                out1 :1,
                out2 :1,
                out3 :1,
                out4 :1,
                out5 :1,
                out6 :1,
                out7 :1,
                out8 :1,
                out9 :1,
                out10 :1,
                out11 :1,
                out12 :1,
                out13 :1,
                out14 :1,
                out15 :1,
                out16 :1,
                out17 :1,
                out18 :1,
                out19 :1,
                out20 :1,
                out21 :1,
                out22 :1,
                out23 :1,
                out24 :1,
                out25 :1,
                out26 :1,
                out27 :1,
                out28 :1,
                out29 :1,
                out30 :1, 
                out31 :1;                                               
    };
    struct {
        uint32_t in0 :1,
                in1 :1,
                in2 :1,
                in3 :1,
                in4 :1,
                in5 :1,
                in6 :1,
                in7 :1,
                in8 :1,
                in9 :1,
                in10 :1,
                in11 :1,
                in12 :1,
                in13 :1,
                in14 :1,
                in15 :1,
                in16 :1,
                in17 :1,
                in18 :1,
                in19 :1,
                in20 :1,
                in21 :1,
                in22 :1,
                in23 :1,
                in24 :1,
                in25 :1,
                in26 :1,
                in27 :1,
                in28 :1,
                in29 :1,
                in30 :1, 
                in31 :1;   
    };
} ioexpand_t;

#else

typedef union {
    uint8_t mask;
    struct {
        uint8_t out0 :1,
                out1 :1,
                out2 :1,
                out3 :1,
                out4 :1,
                out5 :1,
                out6 :1,
                out7 :1;
    };
    struct {
        uint8_t in0 :1,
                in1 :1,
                in2 :1,
                in3 :1,
                in4 :1,
                in5 :1,
                in6 :1,
                in7 :1;
    };
} ioexpand_t;
#endif

extern ioexpand_t io_expander;
void ioexpand_init (void);
void ioexpand_out (ioexpand_t pins);
ioexpand_t ioexpand_in (void);

#endif
