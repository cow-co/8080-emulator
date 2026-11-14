#ifndef EMULATOR_API_H
#define EMULATOR_API_H
#include <stdint.h>
#include <stdio.h>
#include "emulator_state.h"

/**
 * Runs one iteration (one instruction) of the emulator
 */
const uint8_t run();

/**
 * NOTE: Call_er_ closes the file pointer
 */
size_t load_binary(FILE* fp, const uint16_t addr);
void reset_state();
void interrupt(const uint8_t intByte);
/**
 * Internally clamps `bit` to 0-7
 */
void set_bit_on_input_port(const uint8_t port, const uint8_t bit);
/**
 * Internally clamps `bit` to 0-7
 */
void unset_bit_on_input_port(const uint8_t port, const uint8_t bit);
void set_input_port(const uint8_t port, const uint8_t value);
void unset_input_port(const uint8_t port);
const uint8_t read_output_port(const uint8_t port);
const void* const read_memory(const uint16_t fromAddr);

extern const double cyclePeriodMicros;

#endif