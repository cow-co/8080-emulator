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

    processorState.carry = false;
    processorState.parity = false;
    processorState.auxCarry = false;
    processorState.zero = false;
    processorState.sign = false;

    memset(&processorState.readWriteMemory, 0, sizeof(processorState.readWriteMemory) / sizeof(uint8_t));
    memset(&processorState.readOnlyMemory, 0, sizeof(processorState.readOnlyMemory) / sizeof(uint8_t));
}

const size_t load_rom_from_file(FILE* fp) {
    fseek(fp, 0L, SEEK_END);
    size_t fileSize = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    if (fileSize > UINT16_MAX) {
        fileSize = UINT16_MAX;
    }
    fread(&processorState.readOnlyMemory, fileSize, 1, fp);
    return fileSize;
}

uint8_t flags() {
    uint8_t flags = 2;
    flags |= (uint8_t)processorState.carry;
    flags |= (uint8_t)processorState.parity << 2;
    flags |= (uint8_t)processorState.auxCarry << 4;
    flags |= (uint8_t)processorState.zero << 6;
    flags |= (uint8_t)processorState.sign << 7;
    return flags;
}