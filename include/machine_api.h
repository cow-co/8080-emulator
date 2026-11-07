#ifndef MACHINE_API_H
#define MACHINE_API_H
#include <stdint.h>

typedef enum {
    P1_SHOOT,
    P1_LEFT,
    P1_RIGHT,
    P1_START,
    P2_SHOOT,
    P2_LEFT,
    P2_RIGHT,
    P2_START,
    TILT,
    COIN_INSERT,
} Input;

extern const char* const sfxFiles[9];
extern bool sfxStates[9];
extern bool ampEnable;
extern bool extendPlay;

typedef struct {
    unsigned pixelsWidth;
    unsigned pixelsHeight;
    unsigned pixelsPerByte;
    double refreshInterval;
} DisplayParams;

extern const DisplayParams displayParams;

void reset_machine();
void load_rom();
void key_press(Input inputType);
void key_release(Input inputType);
void run_machine();
const void queued_sfx();
const uint8_t* const graphics_state();

#endif