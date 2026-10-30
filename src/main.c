#include <stdio.h>
#include <stdint.h>
#include "machine_layer.h"
#include "emulator_layer.h"

int main(int argc, char* argv[]) {
    reset_state();
    load_rom();
    run(false, 0);
}
