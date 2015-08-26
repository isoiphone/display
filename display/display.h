#ifndef display_display_h
#define display_display_h

#include <stdint.h>

#define display_width   128
#define display_height  64

void display_init();
void display_destroy();

void display_grow();
void display_shrink();

void display_update();

void display_color(int8_t white);
void display_clear(int8_t white);
void display_rect(int8_t white, int8_t x, int8_t y, int8_t w, int8_t h);

// must be display_width*display_height/8 bytes long!
void display_buffer(const uint8_t *buffer);

#endif
