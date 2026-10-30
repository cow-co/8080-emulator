#ifndef MACHINE_H

#include "state.h"
#include <stdint.h>

#define MACHINE_H

typedef struct {
    State* processorState;
    uint16_t shift; // Space invaders has an extra register for multi-bit shifts
} SpaceInvadersCabinet;

extern SpaceInvadersCabinet machine;

void reset_machine();
void load_rom();
void input();
void output();
void run_machine();

#endif