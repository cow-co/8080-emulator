#include "emulator_api.h"
#include "processor.h"
#include "emulator_state.h"
#include <string.h>
#include <time.h>

const size_t countOpcodes = sizeof(opcodes) / sizeof(Opcode);
const double cyclePeriodMicros = 0.5;
const long clocksPerMicro = CLOCKS_PER_SEC / 1'000'000;

void run() {
    if (state.lastOpEndsAt > clock()) {
        return;
    }
    const uint8_t* const code = &state.memory[state.programCounter];
    if (*code >= countOpcodes) {
        printf("ERROR: Could not find opcode %04hhu!\n", *code);
        return;
    } else if (code == nullptr) {
        printf("ERROR: Could not find opcode!\n");
        return;
    }
    const Opcode* const opcode = &opcodes[*code];
#define __EMU8080_DEBUG__
#ifdef __EMU8080_DEBUG__
    printf("%04hu ", state.programCounter);
    if (opcode->opbytes == 2) {
        printf(opcode->assembly, code[1]);
    } else if (opcode->opbytes == 3) {
        printf(opcode->assembly, code[2], code[1]);
    } else {
        printf("%s", opcode->assembly);
    }
    printf("\n");
#endif

    const uint8_t cycles = opcode->opFn(&state);
    if (state.lastOpEndsAt == 0) {
        state.lastOpEndsAt = clock() + (cyclePeriodMicros * cycles * clocksPerMicro);
    } else {
        state.lastOpEndsAt += cyclePeriodMicros * cycles * clocksPerMicro;
    }
}

size_t load_binary(FILE* fp, const uint16_t addr) {
    fseek(fp, 0L, SEEK_END);
    size_t fileSize = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    if (fileSize > UINT16_MAX) {
        fileSize = UINT16_MAX;
    }
    fread(&state.memory[addr], fileSize, 1, fp);
    return fileSize;
}

void reset_state() {
    state.programCounter = 0;
    state.stackPointer = 0;
    
    state.B = 0;
    state.C = 0;
    state.D = 0;
    state.E = 0;
    state.H = 0;
    state.L = 0;
    state.A = 0;

    state.carry = false;
    state.parity = false;
    state.auxCarry = false;
    state.zero = false;
    state.sign = false;

    state.intEnabled = false;
    state.halted = false;
    state.lastOpEndsAt = 0;   // The 8080 runs at 2MHz

    memset(&state.memory, 0, sizeof(state.memory) / sizeof(uint8_t));
    memset(&state.inputData, 0, sizeof(state.inputData) / sizeof(uint8_t));
    memset(&state.outputData, 0, sizeof(state.outputData) / sizeof(uint8_t));
}


void interrupt(const uint8_t intByte) {
    if (state.intEnabled) {
        if (intByte >= countOpcodes) {
            printf("ERROR: Could not find opcode %04hhu!\n", intByte);
            return;
        }
        const Opcode* const opcode = &opcodes[intByte];
        opcode->opFn(&state);
    }
}


void set_bit_on_input_port(const uint8_t port, const uint8_t bit) {
    if (bit > 7) {
        state.inputData[port] |= (uint8_t)(0x80);
    } else {
        state.inputData[port] |= (uint8_t)(1 << bit);
    }
}


void set_input_port(const uint8_t port, const uint8_t value) {
    state.inputData[port] = value;
}


void unset_bit_on_input_port(const uint8_t port, const uint8_t bit) {
    if (bit > 7) {
        state.inputData[port] &= (uint8_t)(0b01111111);
    } else {
        state.inputData[port] &= (uint8_t)((1 << bit) ^ 0xFF);
    }
}


void unset_input_port(const uint8_t port) {
    state.inputData[port] = 0;
}


const uint8_t read_output_port(const uint8_t port) {
    const uint8_t value = state.outputData[port];
    state.outputData[port] = 0;
    return value;
}


const uint8_t* const read_memory(const uint16_t fromAddr) {
    return &state.memory[fromAddr];
}