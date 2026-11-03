#include "machine_api.h"
#include "machine_state.h"
#include "emulator_api.h"

DisplayParams displayParams = {
    .pixelsWidth = 224,
    .pixelsHeight = 220,
    .bytesPerPixel = 1,
    .refreshInterval = 1./60.,
};

const char* const sfx_files[] = {
    "./data/0.wav",
    "./data/1.wav",
    "./data/2.wav",
    "./data/3.wav",
    "./data/4.wav",
    "./data/5.wav",
    "./data/6.wav",
};

void load_rom() {
    FILE* h_file = fopen("./data/invaders.h", "rb");
    if (h_file == nullptr) {
        printf("ERROR: Could not open H file!\n");
        return;
    }
    FILE* g_file = fopen("./data/invaders.g", "rb");
    if (g_file == nullptr) {
        printf("ERROR: Could not open G file!\n");
        return;
    }
    FILE* f_file = fopen("./data/invaders.f", "rb");
    if (f_file == nullptr) {
        printf("ERROR: Could not open F file!\n");
        return;
    }
    FILE* e_file = fopen("./data/invaders.e", "rb");
    if (e_file == nullptr) {
        printf("ERROR: Could not open E file!\n");
        return;
    }
    
    load_binary(machine.processorState, h_file, 0x0000);
    load_binary(machine.processorState, g_file, 0x0800);
    load_binary(machine.processorState, f_file, 0x1000);
    load_binary(machine.processorState, e_file, 0x1800);
}

void reset_machine() {
    reset_state(machine.processorState);
    // Certain input bits are always set
    machine.processorState->inputData[0] = 0b00001110;
    machine.processorState->inputData[1] = 0b00001000;
}

void key_press(Input inputType) {
    switch (inputType)
    {
        case COIN_INSERT:
            machine.processorState->inputData[1] |= 0b00000001;
            break;
        case P1_LEFT:
            machine.processorState->inputData[1] |= 0b00100000;
            break;
        case P1_RIGHT:
            machine.processorState->inputData[1] |= 0b01000000;
            break;
        case P1_SHOOT:
            machine.processorState->inputData[1] |= 0b00010000;
            break;
        case P1_START:
            machine.processorState->inputData[1] |= 0b00000100;
            break;
        case P2_LEFT:
            machine.processorState->inputData[2] |= 0b00100000;
            break;
        case P2_RIGHT:
            machine.processorState->inputData[2] |= 0b01000000;
            break;
        case P2_SHOOT:
            machine.processorState->inputData[2] |= 0b00010000;
            break;
        case P2_START:
            machine.processorState->inputData[1] |= 0b00000010;
            break;
        case TILT:
            machine.processorState->inputData[2] |= 0b00000100;
            break;
        
        default:
            break;
    }
}

void key_release(Input inputType) {
    switch (inputType)
    {
        case COIN_INSERT:
            machine.processorState->inputData[1] &= 0b11111110;
            break;
        case P1_LEFT:
            machine.processorState->inputData[1] &= 0b11011111;
            break;
        case P1_RIGHT:
            machine.processorState->inputData[1] &= 0b10111111;
            break;
        case P1_SHOOT:
            machine.processorState->inputData[1] &= 0b11101111;
            break;
        case P1_START:
            machine.processorState->inputData[1] &= 0b11111011;
            break;
        case P2_LEFT:
            machine.processorState->inputData[2] &= 0b11011111;
            break;
        case P2_RIGHT:
            machine.processorState->inputData[2] &= 0b10111111;
            break;
        case P2_SHOOT:
            machine.processorState->inputData[2] &= 0b11101111;
            break;
        case P2_START:
            machine.processorState->inputData[1] &= 0b11111101;
            break;
        case TILT:
            machine.processorState->inputData[2] &= 0b11111011;
            break;
        
        default:
            break;
    }
}

void run_machine() {
    while (machine.processorState->programCounter < UINT16_MAX) {
        run(machine.processorState, true);
        // TODO Check for middle/end of VBlank and, if so, send the relevant interrupt
    }
}

const uint8_t* const graphics_state() {
    return &machine.processorState->memory[0x2400];
}

const SFX_TYPE queued_sfx() {
    if (machine.processorState->outputData[3] & 0b00000001) {
        return SOUND_UFO;
    } else if (machine.processorState->outputData[3] & 0b00000010) {
        return SOUND_SHOOT;
    } else if (machine.processorState->outputData[3] & 0b00000100) {
        return SOUND_DEATH;
    } else if (machine.processorState->outputData[3] & 0b00001000) {
        return SOUND_KILL;
    } else if (machine.processorState->outputData[3] & 0b00010000) {
        return SOUND_EXTENDED_PLAY;
    } else if (machine.processorState->outputData[3] & 0b00100000) {
        return SOUND_AMP_ENABLE;
    } else if (machine.processorState->outputData[5] & 0b00000001) {
        return SOUND_FLEET_1;
    } else if (machine.processorState->outputData[5] & 0b00000010) {
        return SOUND_FLEET_2;
    } else if (machine.processorState->outputData[5] & 0b00000100) {
        return SOUND_FLEET_3;
    } else if (machine.processorState->outputData[5] & 0b00001000) {
        return SOUND_FLEET_4;
    } else if (machine.processorState->outputData[5] & 0b00010000) {
        return SOUND_UFO_HIT;
    }
    return SOUND_NONE;
}