#include "emulator_layer.h"
#include "processor.h"
#include "state.h"
#include <string.h>

const size_t countOpcodes = sizeof(opcodes) / sizeof(Opcode);

void run(const bool executeInstructions, const uint16_t fromAddr) {
    processorState.programCounter = fromAddr;
    while (processorState.programCounter < UINT16_MAX) {
        if (executeInstructions) {
            printf("NOT IMPLEMENTED YET!\n");
            return;
        } else {
            const unsigned char* const code = &processorState.readWriteMemory[processorState.programCounter];
            if (*code >= countOpcodes) {
                printf("ERROR: Could not find opcode %c!\n", *code);
                return;
            }
            const Opcode* const opcode = &opcodes[*code];
            if (opcode != nullptr) {
                printf("%04hu ", processorState.programCounter);
                if (opcode->opbytes == 2) {
                    printf(opcode->assembly, code[1]);
                } else if (opcode->opbytes == 3) {
                    printf(opcode->assembly, code[2], code[1]);
                } else {
                    printf("%s", opcode->assembly);
                }
                printf("\n");
                processorState.programCounter += opcode->opbytes;
            } else {
                printf("ERROR: Could not find opcode %c!\n", *code);
                return;
            }
        }
    }
}

size_t load_binary(FILE* fp, const uint16_t addr) {
    fseek(fp, 0L, SEEK_END);
    size_t fileSize = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    if (fileSize > UINT16_MAX) {
        fileSize = UINT16_MAX;
    }
    fread(&processorState.readWriteMemory[addr], fileSize, 1, fp);
    return fileSize;
}

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

    processorState.intEnabled = false;
    processorState.halted = false;

    memset(&processorState.readWriteMemory, 0, sizeof(processorState.readWriteMemory) / sizeof(uint8_t));
    memset(&processorState.deviceData, 0, sizeof(processorState.deviceData) / sizeof(uint8_t));
}