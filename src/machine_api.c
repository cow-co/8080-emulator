#include "machine_api.h"
#include "machine_state.h"
#include "emulator_api.h"
#include <time.h>


const DisplayParams displayParams = {
    .pixelsWidth = 224,
    .pixelsHeight = 256,
    .bitsPerPixel = 1,
    .refreshInterval = 1./60.,
};

const char* const sfx_files[] = {
    "",
    "./data/0.wav",
    "./data/1.wav",
    "./data/2.wav",
    "./data/3.wav",
    "./data/4.wav",
    "./data/5.wav",
    "./data/6.wav",
    "./data/7.wav",
    "./data/8.wav",
    "./data/9.wav",
    "./data/10.wav",
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
    
    load_binary(h_file, 0x0000);
    load_binary(g_file, 0x0800);
    load_binary(f_file, 0x1000);
    load_binary(e_file, 0x1800);
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
    machine.lastVBlank = clock();
    run(true);
    const bool vblankInterrupt = (clock() - machine.lastVBlank) > (displayParams.refreshInterval * CLOCKS_PER_SEC);
    if (vblankInterrupt) {
        interrupt(0xD7);  // RST 2
        machine.lastVBlank = clock();
    }
}

const uint8_t* const graphics_state() {
    return read_memory(0x2400);
}

const SFX_TYPE queued_sfx() {
    if (read_output_port(3) & 0b00000001) {
        return SOUND_UFO;
    } else if (read_output_port(3) & 0b00000010) {
        return SOUND_SHOOT;
    } else if (read_output_port(3) & 0b00000100) {
        return SOUND_DEATH;
    } else if (read_output_port(3) & 0b00001000) {
        return SOUND_KILL;
    } else if (read_output_port(3) & 0b00010000) {
        return SOUND_EXTENDED_PLAY;
    } else if (read_output_port(3) & 0b00100000) {
        return SOUND_AMP_ENABLE;
    } else if (read_output_port(5) & 0b00000001) {
        return SOUND_FLEET_1;
    } else if (read_output_port(5) & 0b00000010) {
        return SOUND_FLEET_2;
    } else if (read_output_port(5) & 0b00000100) {
        return SOUND_FLEET_3;
    } else if (read_output_port(5) & 0b00001000) {
        return SOUND_FLEET_4;
    } else if (read_output_port(5) & 0b00010000) {
        return SOUND_UFO_HIT;
    }
    return SOUND_NONE;
}