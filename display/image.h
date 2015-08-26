#ifndef __display__image__
#define __display__image__

#include <stdint.h>

void image_put(uint8_t byte);

// real hardware would always display, we need to manually trigger it here
void image_flush();

#endif
