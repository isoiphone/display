#include <stdint.h>
#include "mandelbrot.h"

// adapted from "Programming 16-Bit PIC Microcontrollers in C: Learning to Fly the PIC 24" by Lucio Di Jasio

#define SIZE_X 128
#define SIZE_Y 64

#define MAXIT 64

float xx0=-2.0f, yy0=-2.0f, w=4.0f;
uint8_t zoomcounter = 0;

uint8_t mandelbrot(int ij, int ii) {
    uint8_t result = 0;
    float x, y, dx, dy, x0, y0, x2, y2;
    int i, k;
    
    dx = w/SIZE_X;
    dy = w/SIZE_Y;
    
    y0 = yy0+(dy*ii);
    x0 = xx0+(dx*ij);
    
    for (i=0; i<8; i++) {
        x = x0;
        y = y0;
        k = 0;
        
        do {
            x2 = x*x;
            y2 = y*y;
            y = 2*x*y + y0;
            x = x2 - y2 + x0;
            k++;
        } while ( (x2 + y2 < 4) && (k < MAXIT));
        
        if (k == MAXIT) {
            result |= (1<<i);
        }
        
        y0 += dy;
    }
    
    if (zoomcounter++ == 255) {
        float ow = w;
        w *= 0.99;
        float ofs = (w-ow)*0.37;
        xx0 -= ofs;
        yy0 -= ofs;
    }
    
    return result;
}
