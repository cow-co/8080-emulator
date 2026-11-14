#include "emulator_state.h"

State state = {};

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
#ifndef CPUDIAG
    // The lowest 2K of memory is genuine ROM
    if (addr < 0x2000) {
        return;
    }
    // Above 4K is the RAM mirror
    if (addr >= 0x4000) {
        return;
    }
#endif
    if (addr >= 0x2400) {
        printf("Writing %hhu to video mem at %hu\n", data, addr);
    }
    write_memory_unsafe(state, addr, data);
}

void write_memory_unsafe(State* state, const uint16_t addr, const uint8_t data) {
    state->memory[addr] = data;
}