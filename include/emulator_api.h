#ifndef EMULATOR_API_H
#define EMULATOR_API_H
#include <stdint.h>
#include <stdio.h>
#include "emulator_state.h"

/**
 * Runs one iteration (one instruction) of the emulator
 */
void run(State* state, const bool executeInstructions);

/**
 * NOTE: Call_er_ closes the file pointer
 */
size_t load_binary(State* state, FILE* fp, const uint16_t addr);
void reset_state(State* state);
void interrupt(State* state, const uint8_t intByte);

extern const double cyclePeriodMicros;

#endif