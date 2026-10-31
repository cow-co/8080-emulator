#include "emulator_state.h"
#include <string.h>

uint8_t flags(State* state) {
    uint8_t flags = 2;
    flags |= (uint8_t)state->carry;
    flags |= (uint8_t)state->parity << 2;
    flags |= (uint8_t)state->auxCarry << 4;
    flags |= (uint8_t)state->zero << 6;
    flags |= (uint8_t)state->sign << 7;
    return flags;
}

void write_memory(State* state, const uint16_t addr, const uint8_t data) {
    // The lowest 2K of memory is genuine ROM
    if (addr <= 2047) {
        printf("Could not write to memory location 0x%hx since it is in ROM!\n", addr);
    } else {
        state->memory[addr] = data;
    }
}