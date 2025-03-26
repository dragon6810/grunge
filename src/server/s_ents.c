#include "s_ents.h"

#include <stdio.h>
#include <math.h>

#include "s_tick.h"

s_player_t* players[MAXPLAYERS];
int nplayers = 0;

void s_processplayerinputs(s_player_t* player)
{
    vec3_t forward, right, up;
    const float turnsense = M_PI / TICKRATE;
    const float movespeed = 512 / TICKRATE;

    if(player->lup)
        player->addpitch += turnsense;
    if(player->ldown)
        player->addpitch -= turnsense;
    if(player->lleft)
        player->addyaw += turnsense;
    if(player->lright)
        player->addyaw -= turnsense;

    player->rot[1] += player->addpitch;
    player->rot[2] += player->addyaw;

    player->addpitch = player->addyaw = 0;

    vec3_copy(forward, vec3_origin);
    vec3_copy(right, vec3_origin);
    vec3_copy(up, vec3_origin);

    forward[0] = 1;
    right[1] = -1;
    up[2] = 1;

    vec3_rotate(forward, forward, player->rot);
    vec3_rotate(right, right, player->rot);
    vec3_rotate(up, up, player->rot);

    if(player->forward)
        vec3_scaleadd(player->pos, player->pos, forward, movespeed);
    if(player->back)
        vec3_scaleadd(player->pos, player->pos, forward, -movespeed);
    if(player->left)
        vec3_scaleadd(player->pos, player->pos, right, -movespeed);
    if(player->right)
        vec3_scaleadd(player->pos, player->pos, right, movespeed);

    // printf("Player: (%f, %f, %f)\n", player->pos[0], player->pos[1], player->pos[2]);
}