#ifndef STATE_H
#define STATE_H

#include <stdint.h>
#include <stdlib.h>

typedef struct {
    // We use uint16_t instead of two unsigned chars because we need exactly 16 bits, rather than *at least* 16 bits
    uint16_t programCounter;
    uint16_t stackPointer;

    // Registers
    // We use uint8_t instead of unsigned char because we need exactly 8 bits, rather than *at least* 8 bits
    uint8_t B; 
    uint8_t C; 
    uint8_t D; 
    uint8_t E; 
    uint8_t H; 
    uint8_t L;
    uint8_t M;

    uint8_t flags;

    // In the 8080, the processor can address 65,535 8-bit bytes of read-write memory
    uint8_t readWriteMemory[65535];
} State;

extern State processorState;
void setFlag(const size_t flagIndex);

#endif