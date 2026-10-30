#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <stdio.h>
#include <stdint.h>

typedef struct {
    const char assembly[64];
    const uint8_t opbytes;
    // Pointer to the function implementing the opcode. 
    // NOTE: it is required that this function sets the program counter register appropriately when done.
    const void (*opFn)();
} Opcode;

extern const Opcode opcodes[256];
extern const size_t countOpcodes;

#endif