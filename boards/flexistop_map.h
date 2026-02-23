/*
  picoHAL_map.h - Board mapping for PicoHAL (modified for custom use)

  Part of grblHAL

  Copyright (c) 2021-2023 Andrew Marles
  Copyright (c) 2024 Mitchell Grams

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

#if TRINAMIC_ENABLE
#error Trinamic plugin not supported!
#endif

#if N_ABC_MOTORS > 0
#error "Axis configuration is not supported!"
#endif

#define BOARD_NAME "FlexiSTOP"
#define BOARD_URL "https://github.com/Expatria-Technologies/FlexiSTOP"

// Define step pulse output pins.
#define STEP_PORT             GPIO_PIO_1
#define X_STEP_PIN            4 //stepper
#define Y_STEP_PIN            14 //AUX0
#define Z_STEP_PIN            22 //AUX4

// Define step direction output pins.
#define DIRECTION_PORT        GPIO_OUTPUT
#define DIRECTION_OUTMODE     GPIO_MAP
#define X_DIRECTION_PIN       5 //stepper
#define Y_DIRECTION_PIN       15 //AUX1
#define Z_DIRECTION_PIN       23 //AUX3

// Define stepper driver enable/disable output pin.
//#define ENABLE_PORT           GPIO_OUTPUT
//#define STEPPERS_ENABLE_PIN   6


// Define homing/hard limit switch input pins.  Currently configured so that X and Z limit pins are shared.
#define LIMIT_PORT            GPIO_INPUT
#define X_LIMIT_PIN           18 //IN0
#define Y_LIMIT_PIN           17 //IN1
#define Z_LIMIT_PIN           18 //IN0

// Aux Outputs
#define AUXOUTPUT0_PORT         GPIO_OUTPUT // MODBUS DIRECTION
#define AUXOUTPUT0_PIN          27
#define AUXOUTPUT1_PORT         GPIO_OUTPUT  // Fans PWM
#define AUXOUTPUT1_PIN          7
#define AUXOUTPUT2_PORT         GPIO_OUTPUT //AUX2
#define AUXOUTPUT2_PIN          24
#define AUXOUTPUT3_PORT         GPIO_OUTPUT //Neo0
#define AUXOUTPUT3_PIN          21
//#define AUXOUTPUT4_PORT         GPIO_OUTPUT //Neo1
//#define AUXOUTPUT4_PIN          20

#if RGB_LED_ENABLE
#define NEOPIXELS_PIN           20
#define NEOPIXELS_NUM           5
#endif

// Aux Inputs
#define AUXINPUT0_PIN           19 //
#define AUXINPUT1_PIN           16 // 
//#define AUXINPUT2_PIN           28 // 
//#define AUXINPUT3_PIN           29 // 

#undef CONTROL_ENABLE
#define CONTROL_ENABLE 0

#if PROBE_ENABLE
#define PROBE_PIN               AUXINPUT0_PIN
#endif

#if PROBE2_ENABLE
#define PROBE2_PIN              AUXINPUT1_PIN
#endif

// Modbus 
#define MODBUS_DIR_AUX  0
#define SERIAL1_PORT 1

#if MODBUS_ENABLE
#define MODBUS_SERIAL_PORT      1
#endif

// UART 0
//#define UART_TX_PIN 12
//#define UART_RX_PIN 13

// UART 1 (Modbus)
#define UART_1_TX_PIN 8
#define UART_1_RX_PIN 9

#define NANOMODBUS_STREAM 1