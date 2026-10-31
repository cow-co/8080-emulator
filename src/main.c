#include <stdio.h>
#include <stdint.h>
#include "machine_api.h"

int main(int argc, char* argv[]) {
    reset_machine();
    load_rom();
    run_machine();
}
