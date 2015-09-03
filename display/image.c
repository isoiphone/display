#include "image.h"
#include "display.h"

static uint8_t image[display_width*display_height/8];
const int max_bytes = display_width*display_height/8;
static int cur_index;

void image_put(uint8_t byte) {
    image[cur_index] = byte;
    cur_index = (cur_index+1)%max_bytes;
}

void image_flush() {
    display_buffer(image);
}
