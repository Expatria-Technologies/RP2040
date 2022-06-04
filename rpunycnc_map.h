/*
  RPunyCNC.h - driver code for RP2040 ARM processors

  Part of grblHAL

  Copyright (c) 2021 Terje Io

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

#include <stdint.h>

#if TRINAMIC_ENABLE
#error Trinamic plugin not supported!
#endif

#if N_ABC_MOTORS > 1
#error "Axis configuration is not supported!"
#endif

//#define IOEXPAND_ENABLE 1

#define BOARD_NAME "RPunyCNC"
//#define HAS_BOARD_INIT

#define UART_TX_PIN 12
#define UART_RX_PIN 13

// Define stepper driver enable/disable output pin.
#define ENABLE_PORT                 GPIO_OUTPUT
#define X_ENABLE_PIN                19
#define Y_ENABLE_PIN                19
#define Z_ENABLE_PIN                19
#define A_ENABLE_PIN                19

#define STEP_PORT           GPIO_SR8
#define DIRECTION_PORT      GPIO_SR8

typedef union {
    uint8_t value;
    /*struct {
        uint8_t m3_dir  :1,
                z_dir   :1,
                y_dir   :1,
                x_dir   :1,
                m3_step :1,
                z_step  :1,
                y_step  :1,
                x_step  :1;
    };*/
        struct {
        uint8_t m3_dir  :1,
                z_dir   :1,
                y_dir   :1,
                x_dir   :1,
                m3_step :1,
                z_step  :1,
                y_step  :1,
                x_step  :1;
    };
} step_dir_t;

typedef union {
    uint32_t value;
    struct {
        step_dir_t set;
        step_dir_t reset;
        uint16_t unused;
    };
} step_dir_sr_t;

// Define step pulse output pins.
#define SD_SHIFT_REGISTER   8
#define SD_SR_DATA_PIN      16
#define SD_SR_SCK_PIN       17 // includes next pin (18)

// Define ganged axis or A axis step pulse and step direction output pins.
#if N_ABC_MOTORS > 0
#define M3_AVAILABLE
#define M3_STEP_PIN         0 // Not referenced by driver code
#define M3_DIRECTION_PIN    0 // Not referenced by driver code
#define M3_LIMIT_PIN        7 // shared with Z axis
#define M3_ENABLE_PIN      19 // shared
#endif

// Define homing/hard limit switch input pins.
#define LIMIT_PORT          GPIO_IN
#define X_LIMIT_PIN         15
#define Y_LIMIT_PIN         27
#define Z_LIMIT_PIN         7
#define LIMIT_INMODE        GPIO_MAP

// Define spindle enable and spindle direction output pins.
#define SPINDLE_PORT                GPIO_OUTPUT
//#define SPINDLE_ENABLE_PIN          28
#define SPINDLE_DIRECTION_PIN       29

// Define spindle PWM output pin.
#define SPINDLE_PWM_PORT            GPIO_OUTPUT
#define SPINDLE_PWM_PIN             28

// Define flood and mist coolant enable output pins.
#define COOLANT_PORT                GPIO_OUTPUT
#define COOLANT_FLOOD_PIN           9
#define COOLANT_MIST_PIN            8

// Define user-control controls (cycle start, reset, feed hold) input pins.
#define RESET_PIN                   6
#define FEED_HOLD_PIN               14 //needs to be connected!
#define CYCLE_START_PIN             11

// Define probe switch input pin.
#define PROBE_PORT                  GPIO_INPUT
#define PROBE_PIN                   5

#define AUX_IO0_PIN      0
#define AUX_IO1_PIN      1
#define AUX_IO2_PIN      2