#include "display.h"

#include <SDL2/SDL.h>
#include <stdio.h>

static SDL_Window *window;
static SDL_Renderer *renderer;

static int display_initialized = 0;
static int display_scale = 1;

void display_init() {
    if (!display_initialized) {
        display_initialized = 1;
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            printf("SDL_Error: %s\n", SDL_GetError());
            exit(1);
        }
    }
    
    if (!window) {
        window = SDL_CreateWindow("Display", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  display_width*display_scale, display_height*display_scale,
                                  SDL_WINDOW_SHOWN);
        if (!window) {
            printf("SDL_Error: %s\n", SDL_GetError());
            exit(1);
        }
    } else {
        SDL_SetWindowSize(window, display_width*display_scale, display_height*display_scale);
    }
    
    if (!renderer) {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
        if (!renderer) {
            printf("SDL_Error: %s\n", SDL_GetError());
            exit(1);
        }
    }
}

void display_destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void display_grow() {
    if (display_scale < 16) {
        ++display_scale;
        display_init();
    }
}

void display_shrink() {
    if (display_scale > 1) {
        --display_scale;
        display_init();
    }
}

void display_update() {
    SDL_RenderPresent(renderer);
}

void display_color(int8_t white) {
    if (white) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    } else {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }
}

void display_clear(int8_t white) {
    display_color(white);
    SDL_RenderClear(renderer);
}

void display_rect(int8_t white, int8_t x, int8_t y, int8_t w, int8_t h) {
    display_color(white);
    SDL_Rect r = {x*display_scale, y*display_scale, w*display_scale, h*display_scale};
    SDL_RenderFillRect(renderer, &r);
}
