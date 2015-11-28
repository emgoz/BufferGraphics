A quick but powerful library for monochrome graphics displays using optimized drawing routines.
For a discription of all functions check out Buffer.h.

It doesn't use malloc() to allocate memory dynamically, so you either have to create the memory area by yourself!
Example:   


#include <Buffer.h>

#define WIDTH   64

#define HEIGHT  16

uint8_t displaybuf[WIDTH * HEIGHT / 8];

Buffer buff(displaybuf,64,16);