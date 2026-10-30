#ifndef EMULATOR_H
#define EMULATOR_H
#include <stdint.h>
#include <stdio.h>

void run(const bool executeInstructions, const uint16_t fromAddr);

/**
 * NOTE: Call_er_ closes the file pointer
 */
size_t load_binary(FILE* fp, const uint16_t addr);
void reset_state();

#endif