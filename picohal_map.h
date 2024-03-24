/*
  picoHAL_map.h - Board mapping for PicoHAL with classic CNC Shield (4 independent axes)

  Part of grblHAL

  Copyright (c) 2021-2023 Andrew Marles

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

#if TRINAMIC_ENABLE
#error Trinamic plugin not supported!
#endif

#if N_ABC_MOTORS > 1
#error "Axis configuration is not supported!"
#endif

#define BOARD_NAME "PicoHAL"
#define BOARD_URL "https://github.com/Expatria-Technologies/PicoHAL"

// Define step pulse output pins.
#define STEP_PORT             GPIO_PIO  // N_AXIS pin PIO SM
#define STEP_PINS_BASE        16        // N_AXIS number of consecutive pins are used by PIO

// Define step direction output pins.
#define DIRECTION_PORT        GPIO_OUTPUT
#define DIRECTION_OUTMODE     GPIO_MAP
#define X_DIRECTION_PIN       20
#define Y_DIRECTION_PIN       21
#define Z_DIRECTION_PIN       22

// Define ganged axis or A axis step pulse and step direction output pins.
#if N_ABC_MOTORS > 0
#define M3_AVAILABLE
#define M3_DIRECTION_PIN      23
#define M3_LIMIT_PIN          5  //shared with Z
#endif

//Define stepper driver enable/disable output pin.  This is not used on PicoBOB.

// Define homing/hard limit switch input pins.  Currently configured so that X and Z limit pins are shared.
#define LIMIT_PORT            GPIO_INPUT
#define X_LIMIT_PIN           15
#define Y_LIMIT_PIN           10
#define Z_LIMIT_PIN           5

// Define driver spindle pins

//auxout0 first so that it is available for Modbus dir
#define AUXOUTPUT0_PORT         GPIO_OUTPUT
#define AUXOUTPUT0_PIN          27
#define MODBUS_DIR_AUX  0

#define SERIAL1_PORT 1

#if MODBUS_ENABLE
#define MODBUS_SERIAL_PORT          1
#endif

#if DRIVER_SPINDLE_PWM_ENABLE
//Define 2 pin PWM port as PWM spindle output
#define SPINDLE_PWM_PORT        GPIO_OUTPUT
#define SPINDLE_PWM_PIN         25

//Define 3 pin 'Neopixel" driver port as aux output
#define AUXOUTPUT1_PORT         GPIO_OUTPUT
#define AUXOUTPUT1_PIN          26

//Define cnc shield coolant pin as auxoutput
#define AUXOUTPUT2_PORT         GPIO_OUTPUT
#define AUXOUTPUT2_PIN          27

//Define cnc shield coolant pin as auxoutput
#define AUXOUTPUT3_PORT         GPIO_OUTPUT
#define AUXOUTPUT3_PIN          7

#else
//Define 2 pin PWM port as Aux output
#define AUXOUTPUT1_PORT        GPIO_OUTPUT
#define AUXOUTPUT1_PIN         25

//Define 3 pin 'Neopixel" driver port as aux output
#define AUXOUTPUT2_PORT         GPIO_OUTPUT
#define AUXOUTPUT2_PIN          26

//Define cnc shield coolant pin as auxoutput
#define AUXOUTPUT3_PORT         GPIO_OUTPUT
#define AUXOUTPUT3_PIN          27

//Define cnc shield coolant pin as auxoutput
#define AUXOUTPUT4_PORT         GPIO_OUTPUT
#define AUXOUTPUT4_PIN          7

#endif

//define CNC shield HOLD pin as auxinput
#define AUXINPUT0_PIN           6
//define CNC shield RUN pin as auxinput
#define AUXINPUT1_PIN           11

//define CNC shield A4/A5 pins as Auxinput, these are ADC capable (3.3V max).
#define AUXINPUT2_PIN           28

#if (PROBE_ENABLE)
#define PROBE_PIN               29
#else
#define AUXINPUT3_PIN           29
#endif

// Define Reset/HALT pin
#define RESET_PIN               14

// Define stepper driver enable/disable output pin.
#define ENABLE_PORT               GPIO_OUTPUT
#define STEPPERS_ENABLE_PIN       24

#if ETHERNET_ENABLE
#define SPI_PORT            0
#define SPI_SCK_PIN         2
#define SPI_MOSI_PIN        3
#define SPI_MISO_PIN        0
#define SPI_CS_PIN          1
#define SPI_IRQ_PIN         4
#define SPI_RST_PORT        GPIO_OUTPUT
//#define SPI_RST_PIN         21
#endif