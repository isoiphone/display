#include <stdint.h>
#include "mandelbrot.h"

// adapted from "Programming 16-Bit PIC Microcontrollers in C: Learning to Fly the PIC 24" by Lucio Di Jasio

#define SIZE 128
#define MAXIT 90

float xx0=-2.0f, yy0=-2.0f, w=4.0f;
//float xx0=-0.637579262, yy0=-0.637579262, w=0.317781657;

uint8_t zoomcounter = 0;
float zoomdir = 1.0;

uint8_t mandelbrot(int ij, int ii) {
    uint8_t result = 0;
    float x, y, d, x0, y0, x2, y2;
    int i, k;
    
    d = w/SIZE;
    
    y0 = yy0+(d*ii)+d*32;
    x0 = xx0+(d*ij);
    
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
        
        y0 += d;
    }
    
    if (zoomcounter++ == 255) {
        if (w < 0.002f || w > 4.0f) {
            zoomdir = -zoomdir;
        }

        float ow = w;
        w *= zoomdir > 0 ? 0.99 : 1.01;
        float ofs = (w-ow)*0.37f;
        xx0 -= ofs;
        yy0 -= ofs;
    }
    
    return result;
}
