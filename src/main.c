#include <stdint.h>
#include <string.h>
#include <emscripten.h>

#define WIDTH 320
#define HEIGHT 200

uint32_t framebuffer[WIDTH * HEIGHT];

extern void js_present_frame(uint8_t *data, int width, int height);

void draw_frame()
{
    static int frame = 0;
    frame++;

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            int i = y * WIDTH + x;
            framebuffer[i] = 0xFFFF0000 | ((x + frame) << 16) | ((y + frame) << 8);  // RGB
        }
    }

    js_present_frame((uint8_t*)framebuffer, WIDTH, HEIGHT);
}

int main()
{
    emscripten_set_main_loop(draw_frame, 0, 1);
    return 0;
}