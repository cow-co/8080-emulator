#ifndef MACHINE_STATE_H
#define MACHINE_STATE_H
#include <stdint.h>
#include "emulator_state.h"

typedef struct {
    uint16_t shift; // Space invaders has an extra register for multi-bit shifts
    long lastVBlank;
} SpaceInvadersCabinet;

extern SpaceInvadersCabinet machine;

#endif