/*
  FlexiHAL 2350 driver pin map

  Part of grblHAL

  Copyright (c) 2024 Terje Io
  Copyright (c) 2024 PL Barrett

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

#if N_ABC_MOTORS > 3
#error "Axis configuration is not supported!"
#endif

#if RP_MCU != 2350
#error "Board has a RP2350 processor!"
#endif

#define BOARD_NAME "FLEXIHAL2350"

#undef I2C_ENABLE
//#define I2C_ENABLE    1
//#define SERIAL1_PORT  0

// Define step pulse output pins.
#define STEP_PORT               GPIO_PIO_1 // Single pin PIO SM
#define X_STEP_PIN              12
#define Y_STEP_PIN              14
#define Z_STEP_PIN              15

// Define step direction output pins.
#define DIRECTION_PORT          GPIO_OUTPUT
#define DIRECTION_OUTMODE       GPIO_MAP
#define X_DIRECTION_PIN         13
#define Y_DIRECTION_PIN         15
#define Z_DIRECTION_PIN         17

// Define ganged axis or A axis step pulse and step direction output pins.
#if N_ABC_MOTORS > 0
#define M3_AVAILABLE
#define M3_STEP_PIN                 14
#define M3_DIRECTION_PIN            13
#define M3_ENABLE_PIN               15
#define M3_LIMIT_PIN                16
#endif

// Define stepper driver enable/disable output pin.
//#define ENABLE_PORT             GPIO_OUTPUT
//#define X_ENABLE_PIN            22
//#define Y_ENABLE_PIN            23
//#define Z_ENABLE_PIN            24

// Define homing/hard limit switch input pins.
#define X_LIMIT_PIN             38
#define Y_LIMIT_PIN             37
#define Z_LIMIT_PIN             36
#define LIMIT_INMODE            GPIO_MAP

// Define ganged axis or A axis step pulse and step direction output pins.
#if N_ABC_MOTORS > 0
#define M3_AVAILABLE
#define M3_DIRECTION_PIN        15
#define M3_LIMIT_PIN            4 // 1.0 -> 3
#define M3_ENABLE_PIN           25
#endif

#if N_ABC_MOTORS == 2
#define M4_AVAILABLE
#define M4_DIRECTION_PIN        16
#define M4_LIMIT_PIN            2
#define M4_ENABLE_PIN           26
#else
#define AUXINPUT6_PIN           2 // M4_LIMIT_PIN
#endif

#define AUXOUTPUT0_PORT         GPIO_OUTPUT //spindle pwm
#define AUXOUTPUT0_PIN          26

#define SPINDLE_PWM_PIN         AUXOUTPUT0_PIN

/*
#if DRIVER_SPINDLE_ENABLE
#define SPINDLE_PORT            GPIO_OUTPUT
#endif
#if DRIVER_SPINDLE_ENABLE & SPINDLE_ENA
#define SPINDLE_ENABLE_PIN      AUXOUTPUT3_PIN
#endif
#if DRIVER_SPINDLE_ENABLE & SPINDLE_PWM
#define SPINDLE_PWM_PIN         AUXOUTPUT0_PIN
#endif
#if DRIVER_SPINDLE_ENABLE & SPINDLE_DIR
#define SPINDLE_DIRECTION_PIN   AUXOUTPUT5_PIN
#endif
*/
/*
#if COOLANT_ENABLE
#define COOLANT_PORT            GPIO_OUTPUT
#endif
#if COOLANT_ENABLE & COOLANT_FLOOD
#define COOLANT_FLOOD_PIN       AUXOUTPUT6_PIN
#endif
#if COOLANT_ENABLE & COOLANT_MIST
#define COOLANT_MIST_PIN        AUXOUTPUT7_PIN
#endif
*/


#define AUXINPUT0_PIN           31  //motor alarm irq
#define AUXINPUT1_PIN           47  // Auxin 0 placeholder
#define AUXINPUT3_PIN           39  // Probe
#define AUXINPUT4_PIN           32  // Safety door
//#define AUXINPUT5_PIN           8  // I2C strobe pin

#define RESET_PIN               24
#define FEED_HOLD_PIN           27
#define CYCLE_START_PIN         30

#if PROBE_ENABLE
#define PROBE_PIN               AUXINPUT3_PIN
#endif

#if SAFETY_DOOR_ENABLE
#define SAFETY_DOOR_PIN         AUXINPUT4_PIN
#endif

#if I2C_STROBE_ENABLE
#define I2C_STROBE_PIN          AUXINPUT5_PIN
#endif

#if SDCARD_ENABLE || ETHERNET_ENABLE
#define SPI_ENABLE 1

#define SPI_PORT                0
#define SPI_SCK_PIN             2
#define SPI_MOSI_PIN            3
#define SPI_MISO_PIN            0

#if SDCARD_ENABLE
#define SD_CS_PIN               41
#endif

#if ETHERNET_ENABLE
#define SPI_CS_PIN              33
#define SPI_IRQ_PIN             25
#define SPI_RST_PORT            8
#endif

#endif // SDCARD_ENABLE || ETHERNET_ENABLE

#if I2C_ENABLE
#define I2C_PORT                1
#define I2C_SDA                 6    
#define I2C_SCL                 7
#endif

#ifdef SERIAL1_PORT
#define UART_1_RX_PIN           29
#define UART_1_TX_PIN          28
#endif
