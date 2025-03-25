#include <stdint.h>
#include <string.h>
#include <emscripten.h>

#include "client/i_input.h"

#define WIDTH 320
#define HEIGHT 200

uint32_t framebuffer[WIDTH * HEIGHT];

extern void js_presentframe(uint8_t *data, int width, int height);

void draw_frame()
{
    static int frame = 0;
    frame++;

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            int i = y * WIDTH + x;
            framebuffer[i] = 0xFF000000 | (x << 16) | (y << 8);  // RGB
        }
    }

    js_presentframe((uint8_t*)framebuffer, WIDTH, HEIGHT);
}

int main()
{
    i_setupinput();
    emscripten_set_main_loop(draw_frame, 0, 1);
    return 0;
}