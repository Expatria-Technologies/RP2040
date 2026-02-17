/*
  my_plugin.c - driver code nanomodbus server

  Part of grblHAL

  Copyright (c) 2020-2024 Terje Io

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
#include "nanomodbus/nanomodbus.h"

#include <string.h>

//#include "serial.h"
#include "grbl/modbus.h"
#include "grbl/settings.h"
#include "grbl/protocol.h"

static io_stream_t *stream;
static on_report_options_ptr on_report_options;

typedef struct {
    uint32_t baud_rate;
    uint32_t rx_timeout;
} rtu_settings_t;

static const uint32_t baud[] = { 2400, 4800, 9600, 19200, 38400, 115200 };
static const modbus_silence_timeout_t dflt_timeout =
{
    .b2400   = 16,
    .b4800   = 8,
    .b9600   = 4,
    .b19200  = 2,
    .b38400  = 2,
    .b115200 = 2
};

static io_stream_t nanomodbus_stream;
static uint8_t dir_port = IOPORT_UNASSIGNED;

// The data model of this sever will support coils addresses 0 to 100 and registers addresses from 0 to 32
#define COILS_ADDR_MAX 100
#define REGS_ADDR_MAX 32

// Our RTU address
#define RTU_SERVER_ADDRESS 1

// A single nmbs_bitfield variable can keep 2000 coils
nmbs_bitfield server_coils = {0};
uint16_t server_registers[REGS_ADDR_MAX + 1] = {0};

static io_stream_t nano_uart;

void onError() {
    // Set the led ON on error
    while (true) {
        //digitalWrite(LED_BUILTIN, HIGH);
    }
}

nmbs_error handle_read_coils(uint16_t address, uint16_t quantity, nmbs_bitfield coils_out, uint8_t unit_id, void* arg) {
    if (address + quantity > COILS_ADDR_MAX + 1)
        return NMBS_EXCEPTION_ILLEGAL_DATA_ADDRESS;

    // Read our coils values into coils_out
    for (int i = 0; i < quantity; i++) {
        bool value = nmbs_bitfield_read(server_coils, address + i);
        nmbs_bitfield_write(coils_out, i, value);
    }

    return NMBS_ERROR_NONE;
}


nmbs_error handle_write_multiple_coils(uint16_t address, uint16_t quantity, const nmbs_bitfield coils, uint8_t unit_id,
                                       void* arg) {
    if (address + quantity > COILS_ADDR_MAX + 1)
        return NMBS_EXCEPTION_ILLEGAL_DATA_ADDRESS;

    // Write coils values to our server_coils
    for (int i = 0; i < quantity; i++) {
        nmbs_bitfield_write(server_coils, address + i, nmbs_bitfield_read(coils, i));
    }

    return NMBS_ERROR_NONE;
}


nmbs_error handler_read_holding_registers(uint16_t address, uint16_t quantity, uint16_t* registers_out, uint8_t unit_id,
                                          void* arg) {
    if (address + quantity > REGS_ADDR_MAX + 1)
        return NMBS_EXCEPTION_ILLEGAL_DATA_ADDRESS;

    // Read our registers values into registers_out
    for (int i = 0; i < quantity; i++)
        registers_out[i] = server_registers[address + i];

    return NMBS_ERROR_NONE;
}


nmbs_error handle_write_multiple_registers(uint16_t address, uint16_t quantity, const uint16_t* registers,
                                           uint8_t unit_id, void* arg) {
    if (address + quantity > REGS_ADDR_MAX + 1)
        return NMBS_EXCEPTION_ILLEGAL_DATA_ADDRESS;

    // Write registers values to our server_registers
    for (int i = 0; i < quantity; i++)
        server_registers[address + i] = registers[i];

    return NMBS_ERROR_NONE;
}

size_t stream_read_bytes(uint8_t *buf, size_t count, uint32_t timeout_ms)
{
    if (!stream || !stream->read || !buf || count == 0)
        return 0;

    size_t read_count = 0;
    uint32_t start = hal.get_elapsed_ticks();

    while (read_count < count) {

        int16_t c = stream->read();

        if (c >= 0) {
            buf[read_count++] = (uint8_t)c;
            continue;
        }

        // No data available — check timeout
        if ((hal.get_elapsed_ticks() - start) >= timeout_ms)
            break;
    }

    return read_count;
}

int32_t read_serial(uint8_t* buf, uint16_t count, int32_t byte_timeout_ms, void* arg) {

    return stream_read_bytes(buf, count, byte_timeout_ms);
}


int32_t write_serial(const uint8_t* buf, uint16_t count, int32_t byte_timeout_ms, void* arg) {
    ioport_digital_out(dir_port, 1);
    stream->write_n(buf, count);
    ioport_digital_out(dir_port, 0);

    return count;
}

static void onReportOptions (bool newopt)
{
    on_report_options(newopt);

    if(!newopt)
    	report_plugin("NanoModbus", "0.01");

}

void my_plugin_init (void)
{
    nmbs_platform_conf platform_conf;
    nmbs_platform_conf_create(&platform_conf);
    platform_conf.transport = NMBS_TRANSPORT_RTU;
    platform_conf.read = read_serial;
    platform_conf.write = write_serial;
    platform_conf.arg = NULL;

    nmbs_callbacks callbacks;
    nmbs_callbacks_create(&callbacks);
    callbacks.read_coils = handle_read_coils;
    callbacks.write_multiple_coils = handle_write_multiple_coils;
    callbacks.read_holding_registers = handler_read_holding_registers;
    callbacks.write_multiple_registers = handle_write_multiple_registers;
  
    bool ok;
    io_stream_t const *stream = stream_open_instance(NANOMODBUS_STREAM, 115200, NULL, "NanoMODBUS UART");
    if((ok = stream != NULL)) {
        memcpy(&nanomodbus_stream, stream, sizeof(io_stream_t));
        nanomodbus_stream.set_enqueue_rt_handler(stream_buffer_all);
    }

    xbar_t *dir_pin; // TODO: move to top and use for direct access
    io_port_cfg_t d_out;

    ioports_cfg(&d_out, Port_Digital, Port_Output);

    int8_t dir_aux = MODBUS_DIR_AUX;

    dir_port = dir_aux != -1 ? dir_aux : (d_out.n_ports ? d_out.n_ports - 1 : IOPORT_UNASSIGNED);

    if((dir_pin = d_out.claim(&d_out, &dir_port, NULL, (pin_cap_t){}))) {
        ioport_set_function(dir_pin, Output_RS485_Direction, NULL);
    }

    on_report_options = grbl.on_report_options;
    grbl.on_report_options = onReportOptions;    
}


