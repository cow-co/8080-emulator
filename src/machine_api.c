#include "machine_api.h"
#include "machine_state.h"
#include "emulator_api.h"
#include "emulator_state.h"
#include <time.h>

const DisplayParams displayParams = {
    .pixelsWidth = 224,
    .pixelsHeight = 256,
    .pixelsPerByte = 8,
    .refreshInterval = 1./60.,
};

const char* const sfxFiles[9] = {
    "./data/0.wav",
    "./data/1.wav",
    "./data/2.wav",
    "./data/3.wav",
    "./data/4.wav",
    "./data/5.wav",
    "./data/6.wav",
    "./data/7.wav",
    "./data/3.wav",
};
bool sfxStates[9] = {0};
bool ampEnable = true;
bool extendPlay = false;

void load_rom() {
#ifndef CPUDIAG
    FILE* file = fopen("./data/invaders", "rb");
    if (file == nullptr) {
        printf("ERROR: Could not open space invaders ROM file!\n");
        return;
    }
    
    load_binary(file, 0x0000);
#endif
#ifdef CPUDIAG
    FILE* file = fopen("./data/cpudiag.bin", "rb");
    if (file == nullptr) {
        printf("ERROR: Could not open CPU Diag ROM file!\n");
        return;
    }
    
    load_binary(file, 0x100);
    state.memory[0] = 0xc3;
    state.memory[1] = 0x00;
    state.memory[2] = 0x01;
    state.memory[368] = 0x07;
#endif
}

void reset_machine() {
    reset_state();
    // Certain input bits are always set
    set_input_port(0, 0b00001110);
    set_input_port(1, 0b00001000);
    machine.nextVBlankInt = 1;
}

void key_press(Input inputType) {
    switch (inputType)
    {
        case COIN_INSERT:
            set_bit_on_input_port(1, 0);
            break;
        case P2_START:
            set_bit_on_input_port(1, 1);
            break;
        case P1_START:
            set_bit_on_input_port(1, 2);
            break;
        case P1_SHOOT:
            set_bit_on_input_port(1, 4);
            break;
        case P1_LEFT:
            set_bit_on_input_port(1, 5);
            break;
        case P1_RIGHT:
            set_bit_on_input_port(1, 6);
            break;
        case TILT:
            set_bit_on_input_port(2, 2);
            break;
        case P2_SHOOT:
            set_bit_on_input_port(2, 4);
            break;
        case P2_LEFT:
            set_bit_on_input_port(2, 5);
            break;
        case P2_RIGHT:
            set_bit_on_input_port(2, 6);
            break;
        
        default:
            break;
    }
}

void key_release(Input inputType) {
    switch (inputType)
    {
        case COIN_INSERT:
            unset_bit_on_input_port(1, 0);
            break;
        case P2_START:
            unset_bit_on_input_port(1, 1);
            break;
        case P1_START:
            unset_bit_on_input_port(1, 2);
            break;
        case P1_SHOOT:
            unset_bit_on_input_port(1, 4);
            break;
        case P1_LEFT:
            unset_bit_on_input_port(1, 5);
            break;
        case P1_RIGHT:
            unset_bit_on_input_port(1, 6);
            break;
        case TILT:
            unset_bit_on_input_port(2, 2);
            break;
        case P2_SHOOT:
            unset_bit_on_input_port(2, 4);
            break;
        case P2_LEFT:
            unset_bit_on_input_port(2, 5);
            break;
        case P2_RIGHT:
            unset_bit_on_input_port(2, 6);
            break;
        
        default:
            break;
    }
}

const double cyclePeriodMicros = 0.5;
const long clocksPerMicro = CLOCKS_PER_SEC / 1'000'000;
const long clocksPerVBlank = CLOCKS_PER_SEC / 60;

void run_machine() {
    // Handle the interrupts generated at the middle and end of V-Blank
    const long now = clock();
    if (machine.lastOp == 0) {
        machine.lastOp = now;
        machine.nextVBlankInt = machine.lastOp + clocksPerVBlank;
        machine.interruptNum = 1;
    }

    if (now > machine.nextVBlankInt) {
        if (now > machine.nextVBlankInt && machine.interruptNum == 1) {
            // Mid-vblank
            interrupt(0b11001111);  // RST 1
            machine.interruptNum = 2;
        } else {
            // End of vblank
            interrupt(0b11010111);  // RST 2
            machine.interruptNum = 1;
        }
        machine.nextVBlankInt = now + clocksPerVBlank / 2;
    }

    // Because our processor operates at a different speed than the real 8080, we have to synchronise our loops based on the 
    // cycle times of the intrustions, otherwise the game will run weirdly
    const long clocksPassed = now - machine.lastOp;
    const long cyclesToCatchUp = (clocksPassed / clocksPerMicro) / cyclePeriodMicros;   // The 8080 is a 2MHz processor, ie. one cycle is 0.5 microseconds
    long cycles = 0;

    while (cyclesToCatchUp > cycles) {
        if (state.memory[state.programCounter] == 0xDB) {
            // Machine-specific IN
            uint8_t devNumber = state.memory[state.programCounter + 1];
            switch(devNumber) {
                case 0:
                    state.A = 1;
                    break;
                case 1:
                    state.A = state.inputData[1];
                    break;
                case 3:
                    uint16_t value = (machine.shift1 << 8) | machine.shift0;
                    state.A = ((value >> (8 - machine.shiftOffset)) & 0xFF);
                    break;
                default:
                    state.A = 0;
                    break;
            }
            state.programCounter += 2;
            cycles += 3;
        } else if (state.memory[state.programCounter] == 0xD3) {
            // Machine-specific OUT
            uint8_t devNumber = state.memory[state.programCounter + 1];
            switch(devNumber) {
                case 2:
                    machine.shiftOffset = state.A & 0x7;
                    break;
                case 4:
                    machine.shift0 = machine.shift1;
                    machine.shift1 = state.A;
                    break;
            }

            state.programCounter += 2;
            cycles += 3;
        } else {
            cycles += run();
        }
    }
    machine.lastOp = now;
}

const void* const graphics_state() {
    return read_memory(0x2400);
}

const void queued_sfx() {
    const uint8_t out3 = read_output_port(3);
    const uint8_t out5 = read_output_port(5);
    sfxStates[0] = (out3 & 0b00000001);
    sfxStates[1] = (out3 & 0b00000010);
    sfxStates[2] = (out3 & 0b00000100);
    sfxStates[3] = (out3 & 0b00001000);
    extendPlay   = (out3 & 0b00010000);
    ampEnable    = (out3 & 0b00100000);
    sfxStates[4] = (out5 & 0b00000001);
    sfxStates[5] = (out5 & 0b00000010);
    sfxStates[6] = (out5 & 0b00000100);
    sfxStates[7] = (out5 & 0b00001000);
    sfxStates[8] = (out5 & 0b00010000);
}