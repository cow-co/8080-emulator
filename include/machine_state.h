#ifndef MACHINE_STATE_H
#define MACHINE_STATE_H
#include <stdint.h>
#include "emulator_state.h"

typedef struct {
    // Space invaders has an extra register for multi-bit shifts
    uint8_t shift0;
    uint8_t shift1;
    uint8_t shiftOffset;
    uint8_t interruptNum;
    long nextVBlankInt;
    long lastOp;
} SpaceInvadersCabinet;

extern SpaceInvadersCabinet machine;

#endif