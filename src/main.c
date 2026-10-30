#include <stdio.h>
#include <stdint.h>
#include "machine_layer.h"

int main(int argc, char* argv[]) {
    reset_machine();
    load_rom();
    run_machine();
}
