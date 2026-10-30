#ifndef STATE_H
#define STATE_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

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
    uint8_t A;
    
    bool carry;
    bool parity;
    bool auxCarry;
    bool zero;
    bool sign;

    bool intEnabled;
    bool halted;

    // In the 8080, the processor can address 65,535 8-bit bytes of read-write memory
    uint8_t readWriteMemory[UINT16_MAX];
    // In the 8080, the processor can address 65,535 8-bit bytes of read-only memory (program counter is 16 bits)
    uint8_t readOnlyMemory[UINT16_MAX];

    uint8_t deviceData[UINT8_MAX + 1];
} State;

extern State processorState;
void reset_state();
/**
 * Call_er_ closes the file pointer!
 */
const size_t load_rom_from_file(FILE* fp);

// Flags byte has bits set like so:
// 0: Carry
// 1: 1
// 2: Parity
// 3: 0
// 4: Aux Carry
// 5: 0
// 6: Zero
// 7: Sign
uint8_t flags();

#endif