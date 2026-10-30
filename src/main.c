#include <stdio.h>
#include "control.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("ERROR: You must provide a binary file to disassemble!\n");
        return 2;
    }

    FILE* f = fopen(argv[1], "rb");
    if (f == nullptr) {
        printf("ERROR: Could not open file!\n");
        return 1;
    }

    run(f, false);
    fclose(f);
}
