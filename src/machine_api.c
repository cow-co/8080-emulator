#include "machine_api.h"
#include "machine_state.h"
#include "emulator_api.h"
#include "emulator_state.h"
#include <time.h>

#define __CPUDIAG__

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
#ifndef __CPUDIAG__
    FILE* file = fopen("./data/invaders", "rb");
    if (file == nullptr) {
        printf("ERROR: Could not open space invaders ROM file!\n");
        return;
    }
    
    load_binary(file, 0x0000);
#endif
#ifdef __CPUDIAG__
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

void run_machine() {
    if (machine.lastVBlank == 0) {
        machine.lastVBlank = clock();
    }
    run();
    const bool vblankInterrupt = (clock() - machine.lastVBlank) > (displayParams.refreshInterval * CLOCKS_PER_SEC);
    if (vblankInterrupt) {
        interrupt(0xD7);  // RST 2
        machine.lastVBlank = clock();
    }
}

const uint8_t* const graphics_state() {
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