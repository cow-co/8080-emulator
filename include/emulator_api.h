#ifndef EMULATOR_API_H
#define EMULATOR_API_H
#include <stdint.h>
#include <stdio.h>
#include "emulator_state.h"

void run(State* state, const bool executeInstructions, const uint16_t fromAddr);

/**
 * NOTE: Call_er_ closes the file pointer
 */
size_t load_binary(FILE* fp, const uint16_t addr);
void reset_state(State* state);

#endif