/*
 minimal SDL app for prototyping out some lo-fidelity graphics.
 final project will be a 128x64 1-bit color OLED screen.
 Jacob Schwartz, August, 2015
 */

#include "display.h"
#include "image.h"
#include <SDL2/SDL.h>

#ifndef MAX
#define MAX( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif

#ifndef MIN
#define MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

void tick_boring() {
    display_rect(1, 10, 10, 50, 20);
}

void tick_bounce() {
    static int8_t bx=display_width/2+15;
    static int8_t by=display_height/2;
    static int8_t dx=1;
    static int8_t dy=1;

    display_rect(1, bx-2, by-2, 5, 5);

    if (bx == 0 || bx == display_width-1) {
        dx = -dx;
    }
    bx += dx;
    
    if (by == 0 || by == display_height-1) {
        dy = -dy;
    }
    by += dy;
}

void tick_noise() {
    uint8_t image[display_width*display_height/8]; // looks good uninitialized
//    int8_t* image = malloc(1024);
    display_buffer(image);
//    free(image);
}

void tick_image() {
    static const uint8_t image_cat[] = {0x55,0x8b,0x55,0x23,0x55,0x88,0x55,0x23,0x55,0xe8,0x55,0xa2,0x55,0x88,0x55,0x2,0x55,0xaf,0x77,0xff,0xdd,0xff,0x75,0xff,0xd5,0xef,0x77,0xff,0xdd,0xff,0x57,0xff,0xdf,0xff,0x77,0xff,0x5d,0xff,0x55,0xb8,0x55,0xa8,0x55,0x20,0x55,0x88,0x55,0xf2,0x55,0xe8,0x55,0xb,0x55,0xbe,0x55,0x2b,0x55,0xf,0x55,0xb,0x15,0xb,0x15,0x3,0x11,0x0,0x1,0x0,0x11,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x10,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x10,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x11,0x0,0x4,0x0,0x11,0x0,0x55,0x3b,0x55,0xff,0x55,0xff,0xd5,0xff,0x55,0xff,0xfd,0xff,0x77,0xff,0xdd,0xfe,0x75,0xfa,0xd5,0xff,0x55,0xfb,0xd5,0xea,0x55,0xba,0x55,0xaa,0x55,0x23,0x55,0x8a,0x55,0x22,0x55,0x88,0x55,0x2a,0x55,0xff,0x75,0xff,0x5d,0xfe,0x55,0x2e,0x55,0x8e,0x55,0x2b,0x55,0xff,0x57,0xff,0xdd,0xff,0x77,0xff,0xdd,0xff,0x77,0xff,0xdf,0xff,0x55,0xbf,0x5d,0xaf,0x55,0x3b,0x55,0xae,0x55,0xfa,0xd5,0xbe,0x55,0x1b,0x55,0x2,0x55,0x0,0x15,0x0,0x5,0x0,0x11,0x0,0x0,0x0,0x11,0x0,0x0,0x0,0x1,0x0,0x40,0x0,0x11,0x0,0x44,0x0,0x11,0x0,0x44,0x0,0x11,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x10,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x11,0x0,0x0,0x0,0x1,0x0,0x54,0x0,0x55,0xbf,0x57,0x3f,0x5d,0xfb,0x55,0xf8,0x5d,0xff,0x55,0xff,0x55,0xff,0x75,0xff,0x5d,0xff,0x55,0xff,0x5d,0xff,0x75,0xfb,0x55,0xfa,0x55,0xb2,0x55,0x8a,0x55,0x22,0x55,0x88,0x55,0x82,0x55,0x8a,0x55,0xbf,0x5d,0xff,0x57,0xff,0x5d,0xbc,0x55,0x3e,0x55,0x8b,0x55,0x8f,0x55,0xff,0x55,0xbf,0x55,0xff,0x57,0xbf,0x5f,0xff,0x57,0xff,0x5d,0xff,0x57,0xfe,0xdd,0xfe,0x55,0xff,0x55,0xaf,0x55,0x3,0x15,0x0,0x44,0x0,0x11,0x80,0x44,0x80,0xd1,0xe0,0x50,0xe0,0x51,0xe0,0x54,0xa0,0x51,0xe0,0x50,0xe0,0x51,0x80,0x54,0x80,0x51,0x80,0x40,0x0,0x11,0x0,0x44,0x0,0x11,0x0,0x40,0x0,0x11,0x0,0x0,0x0,0x11,0x0,0x40,0x0,0x10,0x0,0x40,0x0,0x11,0x0,0x40,0x0,0x11,0x2,0x5,0x0,0x1,0x0,0x1,0x0,0x11,0x3,0x5,0x3,0x11,0x0,0x45,0x0,0x15,0x0,0x55,0x3,0x15,0xa,0x55,0x2b,0x55,0xaf,0x55,0xbb,0x55,0x88,0x55,0x22,0x55,0x88,0x55,0x3,0x55,0x8a,0x55,0xa2,0x55,0xbe,0x55,0xfb,0xd5,0xfe,0x75,0xfe,0x7d,0xfe,0x55,0xfb,0xd5,0xf0,0x55,0xf0,0xd5,0xfa,0x55,0xab,0x55,0xaa,0x55,0xbb,0x55,0xee,0x55,0xff,0xd5,0xff,0x75,0xff,0x55,0xfe,0x55,0x3a,0x5d,0xe,0x55,0x2,0x15,0xf,0x5,0x7,0x15,0xf,0x45,0x3,0x15,0x7,0x7,0x3,0x15,0x3,0x5,0x3,0x11,0x0,0x5,0x1,0x11,0x2,0x5,0x2,0x11,0x0,0x4,0x0,0x11,0x0,0x45,0x0,0x51,0x88,0x55,0x0,0x51,0x80,0x55,0xa0,0xd1,0x80,0x54,0x0,0x51,0x80,0x54,0x0,0x51,0xe8,0x54,0x30,0x11,0x0,0x40,0x0,0x11,0x0,0x0,0x0,0x1,0x0,0x40,0x0,0x11,0x0,0x4,0x0,0x11,0x0,0x55,0x0,0x55,0x0,0x55,0x2,0x55,0x88,0x55,0x2,0x55,0x8,0x55,0x0,0x55,0x88,0x55,0x2b,0x5d,0xff,0x55,0xa3,0x55,0xfb,0x55,0xff,0xdd,0xff,0x55,0xfb,0x55,0xaf,0x57,0xbf,0x55,0xab,0x55,0x2b,0x55,0xfe,0x55,0xba,0x55,0xaf,0x55,0xbb,0x55,0xff,0x55,0x2b,0x55,0x0,0x55,0x0,0x11,0x0,0x40,0x0,0x11,0x0,0x0,0x0,0x11,0x0,0x40,0x0,0x10,0x0,0x0,0x0,0x11,0x0,0x40,0x0,0x10,0x0,0x0,0x0,0x11,0x0,0x40,0x0,0x11,0x0,0x44,0x0,0x11,0x0,0x45,0x2,0x15,0xe,0x55,0xf,0x15,0xf,0x55,0xf,0x55,0xf,0x55,0x3a,0x55,0xea,0x55,0xba,0x55,0xa8,0x55,0x0,0x11,0x80,0x40,0x0,0x11,0x0,0x44,0x0,0x11,0x0,0x44,0x0,0x11,0x0,0x44,0x0,0x11,0x0,0x45,0x0,0x11,0x0,0x55,0x0,0x55,0x88,0x55,0x20,0x55,0x88,0x55,0x0,0x55,0x88,0x55,0x20,0x55,0x8f,0x55,0xfb,0xd5,0xef,0x55,0xb,0x1d,0xe,0x55,0x6,0x15,0x6,0x55,0x2,0x55,0xb,0x55,0x3,0x55,0xab,0x55,0xaa,0x55,0xea,0x55,0xff,0xdd,0xff,0x55,0xfb,0x55,0xa8,0x55,0x0,0x55,0x80,0x55,0x0,0x51,0x0,0x54,0x0,0x51,0x80,0x55,0x0,0x51,0x80,0x54,0x0,0x55,0x80,0x54,0x0,0x51,0x0,0x54,0x0,0x11,0x0,0x45,0x0,0x51,0x0,0x55,0x0,0x11,0x0,0x55,0x0,0x55,0x80,0x55,0x0,0x55,0x80,0x55,0x0,0x55,0x88,0x55,0x0,0x55,0x88,0x55,0xfb,0xd5,0xfa,0x75,0xfa,0xd5,0xe8,0x55,0xa0,0x55,0xa8,0x55,0x80,0x51,0x80,0x55,0x0,0x51,0x80,0x54,0x0,0x11,0x0,0x55,0x0,0x55,0x80,0x55,0x0,0x55,0x88,0x55,0x0,0x55,0xa8,0x55,0x38,0x55,0x88,0x55,0x20,0x55,0x8e,0x55,0x3f,0x55,0xff,0x55,0xb0,0x51,0xa0,0x55,0xb8,0x55,0xec,0x55,0xba,0x55,0xb8,0x55,0xba,0x55,0xae,0x55,0xbb,0x55,0xaf,0x55,0xbf,0xd5,0xff,0x55,0xfb,0x55,0xaa,0x55,0x0,0x55,0x80,0x55,0x0,0x55,0x88,0x55,0x0,0x55,0x80,0x55,0x20,0x55,0x88,0x55,0x20,0x55,0x80,0x55,0x0,0x51,0x0,0x55,0x0,0x55,0x80,0x55,0x0,0x51,0x88,0x54,0x0,0x55,0x80,0x55,0x20,0x55,0xa8,0x55,0xa0,0x55,0xea,0x55,0xfa,0xd5,0xfa,0x55,0xfa,0xdd,0xff,0x77,0xff,0xff,0xff,0x77,0xff,0xdf,0xff,0x77,0xff,0x5d,0xff,0x55,0xff,0xd5,0xfe,0x55,0xba,0x55,0xa8,0x55,0x0,0x55,0x80,0x55,0x0,0x55,0x0,0x55,0x0,0x55,0x88,0x55,0x22,0x55,0x88,0x55,0x22,0x55,0x88,0x55,0x22,0x55,0xa8,0x55,0x22,0x55,0xff,0x55,0xff,0x55,0xff,0x55,0xbb,0x55,0xaa,0x55,0xbb,0x55,0xaa,0x55,0xbb,0x55,0xaa,0x55,0x7b,0x55,0x2e,0x55,0x2b,0x55,0x8f,0x55,0x3b,0x55,0x8a,0x55,0x22,0x55,0x88,0x55,0x20,0x55,0xa8,0x55,0x2a,0x55,0x8a,0x55,0xa2,0x55,0xaa,0x55,0x28,0x55,0x8a,0x55,0x20,0x55,0x88,0x55,0x20,0x55,0x88,0x55,0xa0,0x55,0x88,0x55,0xa2,0x55,0xaa,0x55,0xa2,0x55,0xaa,0x55,0xfb,0xd5,0xff,0x55,0xff,0x5d,0xff,0x55,0xbf,0x55,0xef,0x55,0xbb,0x55,0xab,0x55,0xab,0x55,0x8a,0x55,0x23,0x55,0x8a,0x55,0x3,0x55,0x8b,0x55,0x3,0x55,0x8,0x55,0x0,0x55,0x0,0x55,0x0,0x51,0x0,0x55,0x0};
    display_buffer(image_cat);
}

void tick_checkerboard() {
    uint8_t row,block,square;
    uint8_t pattern = 0;
    for (row=8; row!=0; --row) {
        for (block=16; block!=0; --block) {
            for (square=8; square!=0; --square) {
                image_put(pattern);
            }
            pattern = ~pattern;
        }
        pattern = ~pattern;
    }
    image_flush();
}

void (*tick_ptrs[])(void) = {tick_boring, tick_bounce, tick_noise, tick_image, tick_checkerboard};

int main(int argc, char* args[])
{
    int cur_tick = 0;
    const int num_tick_ptrs = sizeof(tick_ptrs)/sizeof(tick_ptrs[0]);
    
    display_init();
    
    int doLoop = 1;
    while (doLoop) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                doLoop = 0;
            } else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        doLoop = 0;
                        break;
                    case SDLK_EQUALS:
                        display_grow();
                        break;
                    case SDLK_MINUS:
                        display_shrink();
                        break;
                    case SDLK_2:
                        if (cur_tick < num_tick_ptrs-1) {
                            ++cur_tick;
                        }
                        break;
                    case SDLK_1:
                        if (cur_tick > 0) {
                            --cur_tick;
                        }
                        break;
                }
            }
        }
        
        display_clear(0);
        tick_ptrs[cur_tick]();
        display_update();
    }
    
    display_destroy();
    
    SDL_Quit();
    
    return 0;
}
