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

typedef enum {
    SOUND_NONE,
    SOUND_UFO,
    SOUND_SHOOT,
    SOUND_DEATH,
    SOUND_KILL,
    SOUND_EXTENDED_PLAY,
    SOUND_AMP_ENABLE,
    SOUND_FLEET_1,
    SOUND_FLEET_2,
    SOUND_FLEET_3,
    SOUND_FLEET_4,
    SOUND_UFO_HIT,
} SFX_TYPE;

extern const char* const sfx_files[];

typedef struct {
    unsigned pixelsWidth;
    unsigned pixelsHeight;
    unsigned bytesPerPixel;
    double refreshInterval;
} DisplayParams;

extern const DisplayParams displayParams;

void reset_machine();
void load_rom();
void key_press(Input inputType);
void key_release(Input inputType);
void run_machine();
const SFX_TYPE queued_sfx();
const uint8_t* const graphics_state();

#endif