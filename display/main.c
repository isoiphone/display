/*
 minimal SDL app for prototyping out some lo-fidelity graphics.
 final project will be a 128x64 1-bit color OLED screen.
 Jacob Schwartz, August, 2015
*/

#include "display.h"

#include <SDL2/SDL.h>

void tick() {
    display_rect(1, 10, 10, 50, 20);
}

int main(int argc, char* args[])
{
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
                }
            }
        }
        
        display_clear(0);
        tick();
        display_update();
    }
    
    display_destroy();
    
    SDL_Quit();
    
    return 0;
}
