#ifndef _i_video_h
#define _i_video_h

#include <stdint.h>

#define SCREENWIDTH 320
#define SCREENHEIGHT 200

extern uint32_t framebuffer[SCREENWIDTH * SCREENHEIGHT];

void i_present(void);

#endif