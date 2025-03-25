#ifndef _s_ents_h
#define _s_ents_h

#include <math/m_vec.h>

typedef struct s_player_s s_player_t;

struct s_player_s
{
    vec3_t pos;
    rot_t rot;
};

#endif