#include "machine_layer.h"
#include "emulator_layer.h"

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