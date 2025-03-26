#ifndef _s_ents_h
#define _s_ents_h

#include <stdbool.h>

#include <math/m_vec.h>

#define MAXPLAYERS 16

typedef struct s_player_s s_player_t;

struct s_player_s
{
    vec3_t pos;
    rot_t rot;

    // inputs
    bool forward, left, right, back, lleft, lright, lup, ldown;
    float addyaw, addpitch;
};

extern s_player_t* players[MAXPLAYERS];
extern int nplayers;

void s_processplayerinputs(s_player_t* player);

#endif