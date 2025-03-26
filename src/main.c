#include <stdint.h>
#include <string.h>
#include <emscripten.h>
#include <stdio.h>
#include <time.h>

#include "client/i_input.h"
#include "client/c_player.h"
#include "server/s_tick.h"
#include "server/s_ents.h"

#define WIDTH 320
#define HEIGHT 200

uint32_t framebuffer[WIDTH * HEIGHT];

extern void js_presentframe(uint8_t *data, int width, int height);

bool runtick(void)
{
    static double lasttime = 0;
    double now, elapsed;
    static int frame = 0;
    int nticks;
    frame++;

    now = emscripten_get_now();

    if(!lasttime)
    {
        lasttime = now;
        return false;
    }

    elapsed = now - lasttime;
    if(elapsed < (1.0 / TICKRATE) * 1000.0)
        return false;

    nticks = elapsed / ((1.0 / TICKRATE) * 1000.0);
    lasttime += nticks * ((1.0 / TICKRATE) * 1000.0);
    while(nticks--)
    {
        //printf("Player pos: (%f, %f, %f)\n", player.pos[0], player.pos[1], player.pos[2]);

        s_tick();

        for (int y = 0; y < HEIGHT; y++)
        {
            for (int x = 0; x < WIDTH; x++)
            {
                int i = y * WIDTH + x;
                framebuffer[i] = 0xFF000000 | (x << 16) | (y << 8);  // RGB
            }
        }
    }

    js_presentframe((uint8_t*)framebuffer, WIDTH, HEIGHT);
    lasttime = now;

    return true;
}

void mainloop(void)
{
    while(!runtick());
}

int main()
{
    i_setupinput();
    players[nplayers++] = &player;
    emscripten_set_main_loop(mainloop, TICKRATE, 1);
    return 0;
}