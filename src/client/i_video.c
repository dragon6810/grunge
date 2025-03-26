#include "i_video.h"

uint32_t framebuffer[SCREENWIDTH * SCREENHEIGHT];

extern void js_presentframe(uint8_t *data, int width, int height);

void i_present(void)
{
    js_presentframe((uint8_t*)framebuffer, SCREENWIDTH, SCREENHEIGHT);
}