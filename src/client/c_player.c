#include "c_player.h"

#include <stdio.h>

s_player_t player = {};

void c_forwarddown(void)
{
    player.forward = true;
}

void c_forwardup(void)
{
    player.forward = false;
}

void c_leftdown(void)
{
    player.left = true;
}

void c_leftup(void)
{
    player.left = false;
}

void c_rightdown(void)
{
    player.right = true;
}

void c_rightup(void)
{
    player.right = false;
}

void c_backdown(void)
{
    player.back = true;
}

void c_backup(void)
{
    player.back = false;
}

void c_lupdown(void)
{
    player.lup = true;
}

void c_lupup(void)
{
    player.lup = false;
}

void c_ldowndown(void)
{
    player.ldown = true;
}

void c_ldownup(void)
{
    player.ldown = false;
}

void c_lleftdown(void)
{
    player.lleft = true;
}

void c_lleftup(void)
{
    player.lleft = false;
}

void c_lrightdown(void)
{
    player.lright = true;
}

void c_lrightup(void)
{
    player.lright = false;
}