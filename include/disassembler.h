#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include <stdio.h>
#include <stdint.h>

typedef struct {
    const char assembly[64];
    const uint8_t opbytes;
} Opcode;

extern const Opcode opcodes[256];
extern const size_t countOpcodes;

/**
 * NOTE: Call_er_ closes the file pointer
 */
void disassemble(FILE* fp);

#endif