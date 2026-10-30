#include "state.h"
#include <string.h>

State processorState = {0};

uint8_t flags() {
    uint8_t flags = 2;
    flags |= (uint8_t)processorState.carry;
    flags |= (uint8_t)processorState.parity << 2;
    flags |= (uint8_t)processorState.auxCarry << 4;
    flags |= (uint8_t)processorState.zero << 6;
    flags |= (uint8_t)processorState.sign << 7;
    return flags;
}

void write_memory(const uint16_t addr, const uint8_t data) {
    // The lowest 2K of memory is genuine ROM
    if (addr <= 2047) {
        printf("Could not write to memory location 0x%hx since it is in ROM!\n", addr);
    } else {
        processorState.readWriteMemory[addr] = data;
    }
}