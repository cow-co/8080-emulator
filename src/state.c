#include "state.h"
#include <string.h>

State processorState = {0};

void reset_state() {
    processorState.programCounter = 0;
    processorState.stackPointer = 0;
    processorState.B = 0;
    processorState.C = 0;
    processorState.D = 0;
    processorState.E = 0;
    processorState.H = 0;
    processorState.L = 0;
    processorState.A = 0;
    processorState.flags = 0;
    memset(&processorState.readWriteMemory, 0, sizeof(processorState.readWriteMemory) / sizeof(uint8_t));
}

void set_flag(size_t flagIndex) {
    if (flagIndex >= 5) {
        flagIndex = 4;
    }
    processorState.flags |= 1 << flagIndex;
}

void reset_flag(size_t flagIndex) {
    if (flagIndex >= 5) {
        flagIndex = 4;
    }
    processorState.flags &= ~(1 << flagIndex);
}

const uint16_t B_register_pair() {
    uint16_t regPair = processorState.B;
    regPair = regPair<< 8;
    regPair |= (uint16_t)processorState.C;
    return regPair;
}

const uint16_t D_register_pair() {
    uint16_t regPair = processorState.D;
    regPair = regPair<< 8;
    regPair |= (uint16_t)processorState.E;
    return regPair;
}

const uint16_t H_register_pair() {
    uint16_t regPair = processorState.H;
    regPair = regPair<< 8;
    regPair |= (uint16_t)processorState.L;
    return regPair;
}

const uint16_t psw() {
    uint16_t regPair = processorState.A;
    regPair = regPair<< 8;
    regPair |= (uint16_t)processorState.flags;
    return regPair;
}