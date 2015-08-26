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

void display_color(uint8_t white);
void display_clear(uint8_t white);
void display_rect(uint8_t white, uint8_t x, uint8_t y, uint8_t w, uint8_t h);

#endif
