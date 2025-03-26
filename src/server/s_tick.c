#include "s_tick.h"

#include <stdio.h>

#include "s_ents.h"

void s_printplayerpositions(void)
{
    int i;

    for(i=0; i<nplayers; i++)
        printf("Player %d: (%f, %f, %f) (%f, %f, %f)\n", i,
            players[i]->pos[0], players[i]->pos[1], players[i]->pos[2],
            players[i]->rot[0], players[i]->rot[1], players[i]->rot[2]);
}

void s_updateplayers(void)
{
    int i;

    for(i=0; i<nplayers; i++)
        s_processplayerinputs(players[i]);
}

void s_tick(void)
{
    //s_printplayerpositions();
    s_updateplayers();
}