#include "emulator_api.h"
#include "processor.h"
#include "emulator_state.h"
#include <string.h>

const size_t countOpcodes = sizeof(opcodes) / sizeof(Opcode);

void run(State* state, const bool executeInstructions, const uint16_t fromAddr) {
    state->programCounter = fromAddr;
    while (state->programCounter < UINT16_MAX) {
        if (executeInstructions) {
            printf("NOT IMPLEMENTED YET!\n");
            return;
        } else {
            const unsigned char* const code = &state->memory[state->programCounter];
            if (*code >= countOpcodes) {
                printf("ERROR: Could not find opcode %c!\n", *code);
                return;
            }
            const Opcode* const opcode = &opcodes[*code];
            if (opcode != nullptr) {
                printf("%04hu ", state->programCounter);
                if (opcode->opbytes == 2) {
                    printf(opcode->assembly, code[1]);
                } else if (opcode->opbytes == 3) {
                    printf(opcode->assembly, code[2], code[1]);
                } else {
                    printf("%s", opcode->assembly);
                }
                printf("\n");
                state->programCounter += opcode->opbytes;
            } else {
                printf("ERROR: Could not find opcode %c!\n", *code);
                return;
            }
        }
    }
}

size_t load_binary(State* state, FILE* fp, const uint16_t addr) {
    fseek(fp, 0L, SEEK_END);
    size_t fileSize = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    if (fileSize > UINT16_MAX) {
        fileSize = UINT16_MAX;
    }
    fread(&state->memory[addr], fileSize, 1, fp);
    return fileSize;
}

void reset_state(State* state) {
    state->programCounter = 0;
    state->stackPointer = 0;
    
    state->B = 0;
    state->C = 0;
    state->D = 0;
    state->E = 0;
    state->H = 0;
    state->L = 0;
    state->A = 0;

    state->carry = false;
    state->parity = false;
    state->auxCarry = false;
    state->zero = false;
    state->sign = false;

    state->intEnabled = false;
    state->halted = false;

    memset(&state->memory, 0, sizeof(state->memory) / sizeof(uint8_t));
    memset(&state->deviceData, 0, sizeof(state->deviceData) / sizeof(uint8_t));
}