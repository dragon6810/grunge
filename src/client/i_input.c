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

    keyfields['A'].name = "strafeleft";
    keyfields['A'].down = c_leftdown;
    keyfields['A'].up = c_leftup;

    keyfields['D'].name = "straferight";
    keyfields['D'].down = c_rightdown;
    keyfields['D'].up = c_rightup;

    keyfields['S'].name = "back";
    keyfields['S'].down = c_backdown;
    keyfields['S'].up = c_backup;

    keyfields[38].name = "lup";
    keyfields[38].down = c_lupdown;
    keyfields[38].up = c_lupup;

    keyfields[40].name = "ldown";
    keyfields[40].down = c_ldowndown;
    keyfields[40].up = c_ldownup;

    keyfields[37].name = "lleft";
    keyfields[37].down = c_lleftdown;
    keyfields[37].up = c_lleftup;

    keyfields[39].name = "lright";
    keyfields[39].down = c_lrightdown;
    keyfields[39].up = c_lrightup;
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