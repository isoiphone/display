/*
 minimal SDL app for prototyping out some lo-fidelity graphics.
 final project will be a 128x64 1-bit color OLED screen.
 Jacob Schwartz, August, 2015
 */

#include "display.h"

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

void (*tick_ptrs[])(void) = {tick_boring, tick_bounce};

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
