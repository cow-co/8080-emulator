#ifndef MACHINE_API_H
#define MACHINE_API_H
#include <stdint.h>

typedef enum {
    SHOOT,
    LEFT,
    RIGHT,
} Input;

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
const uint8_t* const graphics_state();

#endif