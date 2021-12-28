/*
  pico_cnc_map.h - driver code for RP2040 ARM processors

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

#define IOEXPAND_ENABLE 1

#define BOARD_NAME "Ras_CNC"
#define HAS_BOARD_INIT

// Define stepper driver enable/disable output pin.
#define STEPPERS_DISABLEX_PIN        4
#define STEPPERS_DISABLEY_PIN        5
#define STEPPERS_DISABLEZ_PIN        6
#define STEPPERS_DISABLEA_PIN        7
#define STEPPERS_ENABLE_OUTMODE     GPIO_IOEXPAND

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
#define SD_SR_DATA_PIN      1
#define SD_SR_SCK_PIN       2 // includes next pin (3)

// Define ganged axis or A axis step pulse and step direction output pins.
#if N_ABC_MOTORS > 0
#define M3_AVAILABLE
#define M3_STEP_PIN         0
#define M3_STEP_PORT        GPIO_SR8
#define M3_DIRECTION_PIN    0
#define M3_DIRECTION_PORT   GPIO_SR8
#define M3_LIMIT_PIN        3
#define M3_ENABLE_PIN       7
#define M3_ENABLE_PORT      GPIO_IOEXPAND
#endif

// Define homing/hard limit switch input pins.
#define X_LIMIT_PIN         15
#define Y_LIMIT_PIN         27
#define Z_LIMIT_PIN         28
#define X_LIMIT_BIT         (1<<X_LIMIT_PIN)
#define Y_LIMIT_BIT         (1<<Y_LIMIT_PIN)
#define Z_LIMIT_BIT         (1<<Z_LIMIT_PIN)
/*#if N_AXIS > 3
#define A_LIMIT_PIN         14
#define A_LIMIT_BIT         (1<<A_LIMIT_PIN)
#define LIMIT_MASK          (X_LIMIT_BIT|Y_LIMIT_BIT|Z_LIMIT_BIT|A_LIMIT_BIT) // All limit bits
#else
#define LIMIT_MASK          (X_LIMIT_BIT|Y_LIMIT_BIT|Z_LIMIT_BIT) // All limit bits
#endif*/
#define LIMIT_INMODE        GPIO_MAP

// Define spindle enable and spindle direction output pins.
#define SPINDLE_ENABLE_PORT         GPIO_IOEXPAND
#define SPINDLE_ENABLE_PIN          2
#define SPINDLE_DIRECTION_PORT      GPIO_IOEXPAND
#define SPINDLE_DIRECTION_PIN       3
#define SPINDLE_OUTMODE             GPIO_IOEXPAND

// Define flood and mist coolant enable output pins.
#define COOLANT_FLOOD_PORT          GPIO_IOEXPAND
#define COOLANT_FLOOD_PIN           1
#define COOLANT_MIST_PORT           GPIO_IOEXPAND
#define COOLANT_MIST_PIN            0
#define COOLANT_OUTMODE             GPIO_IOEXPAND

// Define spindle PWM output pin.
#define SPINDLE_PWM_PORT    GPIO_OUTPUT
#define SPINDLE_PWM_PIN     7
#define SPINDLE_PWM_BIT     (1<<SPINDLE_PWM_PIN)

// Define user-control controls (cycle start, reset, feed hold) input pins.
#define RESET_PIN           0
#define RESET_BIT           (1<<RESET_PIN)
#define FEED_HOLD_PIN       17
#define FEED_HOLD_BIT       (1<<FEED_HOLD_PIN)
#define CYCLE_START_PIN     6
#define CYCLE_START_BIT     (1<<CYCLE_START_PIN)
#ifdef ENABLE_SAFETY_DOOR_INPUT_PIN
#define SAFETY_DOOR_PIN     16
#define SAFETY_DOOR_BIT     (1<<SAFETY_DOOR_PIN)
#define CONTROL_MASK        (RESET_BIT|FEED_HOLD_BIT|CYCLE_START_BIT|SAFETY_DOOR_BIT)
#else
#define CONTROL_MASK        (RESET_BIT|FEED_HOLD_BIT|CYCLE_START_BIT)
#endif
#define CONTROL_INMODE      GPIO_MAP

// Define probe switch input pin.
#define PROBE_PIN           28
#define PROBE_BIT           (1<<PROBE_PIN)

#define AUX_IO0_PIN      21
#define AUX_IO1_PIN      20
#define AUX_IO2_PIN      19
#define AUX_IO3_PIN      18


#if !SDCARD_ENABLE || !defined(SAFETY_DOOR_PIN)
//#define HAS_IOPORTS
#if !SDCARD_ENABLE 
#define AUX_INPUT0_PIN      AUX_IO0_PIN
#define AUX_INPUT1_PIN      AUX_IO1_PIN
#define AUX_INPUT2_PIN      AUX_IO2_PIN
#if !MPG_MODE_ENABLE
#define AUX_INPUT3_PIN      AUX_IO3_PIN
#endif
#ifndef SAFETY_DOOR_PIN
#define AUX_INPUT4_PIN      16   
#endif
#else
#define AUX_INPUT0_PIN      9   
#endif
#endif

/*#define AUXOUTPUT0_PORT GPIO_IOEXPAND
#define AUXOUTPUT0_PIN 10
#define AUXOUTPUT1_PORT GPIO_IOEXPAND
#define AUXOUTPUT1_PIN 11
#define AUXOUTPUT2_PORT GPIO_IOEXPAND
#define AUXOUTPUT2_PIN 12
#define AUXOUTPUT3_PORT GPIO_IOEXPAND
#define AUXOUTPUT3_PIN 13
*/
#if I2C_ENABLE
#define I2C_PORT            0
#define I2C_SDA             4
#define I2C_SCL             5
#endif

#if SDCARD_ENABLE
#define SPI_PORT            spi1
#define SD_SCK_PIN          AUX_IO0_PIN
#define SD_MOSI_PIN         AUX_IO1_PIN
#define SD_MISO_PIN         AUX_IO2_PIN
#define SD_CS_PIN           AUX_IO3_PIN
#endif

#if MPG_MODE_ENABLE
#define MODE_SWITCH_PIN     AUX_IO3_PIN
#define MODE_SWITCH_BIT     (1<<MODE_SWITCH_PIN)
#endif

#if KEYPAD_ENABLE
#define KEYPAD_STROBE_PIN   10
#define KEYPAD_STROBE_BIT   (1<<KEYPAD_STROBE_PIN)
#endif
