#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include <stdio.h>
#include <stdint.h>

typedef struct {
    const char code;
    const char assembly[64];
    const uint8_t opbytes;
} Opcode;

extern const Opcode opcodes[256];
void disassemble(const FILE* fp);

#endif