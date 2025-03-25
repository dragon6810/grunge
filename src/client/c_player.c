#include "c_player.h"

#include <stdio.h>

bool forwardheld = false;

void c_forwarddown(void)
{
    printf("forward down\n");
    forwardheld = true;
}

void c_forwardup(void)
{
    printf("forward up\n");
    forwardheld = false;
}