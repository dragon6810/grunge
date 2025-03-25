#include "i_input.h"

#include <stdio.h>
#include <emscripten.h>
#include <string.h>

#include "c_player.h"

extern void js_setupinput(void);

i_keyfield_t keyfields[MAX_KEYCODE];

void i_loaddefaultkeys(void)
{
    memset(keyfields, 0, sizeof(keyfields));

    keyfields['W'].name = "forward";
    keyfields['W'].down = c_forwarddown;
    keyfields['W'].up = c_forwardup;
}

void i_setupinput(void)
{
    js_setupinput();
    i_loaddefaultkeys();
}

EMSCRIPTEN_KEEPALIVE
void i_keydown(int keycode)
{
    // printf("Key down: %d\n", keycode);
    if(keyfields[keycode].down)
        keyfields[keycode].down();
}

EMSCRIPTEN_KEEPALIVE
void i_keyup(int keycode)
{
    // printf("Key up: %d\n", keycode);
    if(keyfields[keycode].up)
        keyfields[keycode].up();
}