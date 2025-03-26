#include "r_main.h"

#include <stdio.h>
#include <string.h>
#include <math.h>

#include <math/m_math.h>
#include <math/m_vec.h>
#include "i_video.h"
#include "c_player.h"

#define FOV 90

#define RANGECHECK

void r_renderline(int x1, int y1, int x2, int y2, uint32_t color)
{
    int i;
    float slope, x, y, xstep, ystep;

#ifdef RANGECHECK
    if(!INRANGE(x1, 0, SCREENWIDTH-1)
    || !INRANGE(x2, 0, SCREENWIDTH-1)
    || !INRANGE(y1, 0, SCREENHEIGHT-1)
    || !INRANGE(y2, 0, SCREENHEIGHT-1))
    {
        fprintf(stderr, "r_renderline: rangecheck failed for (%d, %d) to (%d, %d)\n", x1, y1, x2, y2);
        return;
    }
#endif

    if(x1 > x2)
    {
        SWAP(x1, x2);
        SWAP(y1, y2);
    }

    if(y1 == y2)
    {
        for(i=y1*SCREENWIDTH+x1; i<y1*SCREENWIDTH+x2; i++)
            framebuffer[i] = color;

        return;
    }

    if(x1 == x2)
    {
        if(y1 < y2)
            SWAP(y1, y2);
        
        for(i=y2*SCREENWIDTH+x1; i<y1*SCREENWIDTH+x1; i+=SCREENWIDTH)
            framebuffer[i] = color;

        return;
    }

    slope = (float) (y2-y1) / (float) (x2-x1);
    if(INRANGE(slope, -1, 1))
    {
        x = x1;
        y = y1;
        ystep = slope;
        for(x=x1, y=y1; x<x2; x++, y+=ystep)
        {
            i = ((int) y) * SCREENWIDTH + (int) x;
            framebuffer[i] = color;
        }

        return;
    }

    if(y1 > y2)
    {
        SWAP(x1, x2);
        SWAP(y1, y2);
        slope = (float) (y2-y1) / (float) (x2-x1);
    }

    x = x1;
    y = y1;
    xstep = 1.0 / slope;
    for(x=x1, y=y1; y<y2; y++, x+=xstep)
    {
        i = ((int) y) * SCREENWIDTH + (int) x;
        framebuffer[i] = color;
    }
}

void r_renderworldline(const vec3_t v1, const vec3_t v2)
{
    const float nearplane = 1;

    rot_t revrot;
    float v1x, v1y, v2x, v2y;
    float hplane, vplane;
    float t;
    float slope;
    vec3_t r;
    vec3_t v1local, v2local;

    vec3_scale(revrot, player.rot, -1);
    vec3_subtract(v1local, v1, player.pos);
    vec3_subtract(v2local, v2, player.pos);
    vec3_rotate(v1local, v1local, revrot);
    vec3_rotate(v2local, v2local, revrot);

    // Both lines are behind us
    if(v1local[0] < nearplane && v2local[0] < nearplane)
        return;

    // Clip line to not be behind us
    if(v1local[0] < nearplane)
    {
        vec3_subtract(r, v1local, v2local);
        vec3_normalize(r, r);

        t = (nearplane - v2local[0]) / r[0];
        vec3_scaleadd(v1local, v2local, r, t);
    }

    // Clip line to not be behind us
    if(v2local[0] < nearplane)
    {
        vec3_subtract(r, v2local, v1local);
        vec3_normalize(r, r);

        t = (nearplane - v1local[0]) / r[0];
        vec3_scaleadd(v2local, v1local, r, t);
    }

    hplane = 2.0 * tanf(DEG2RAD(FOV)*0.5);
    vplane = hplane * ((float) SCREENHEIGHT / (float) SCREENWIDTH);

    v1x = -(v1local[1]) / hplane / v1local[0];
    v1y = -(v1local[2]) / vplane / v1local[0];
    v2x = -(v2local[1]) / hplane / v2local[0];
    v2y = -(v2local[2]) / vplane / v2local[0];

    v1x = (v1x + 0.5) * SCREENWIDTH;
    v1y = (v1y + 0.5) * SCREENHEIGHT;
    v2x = (v2x + 0.5) * SCREENWIDTH;
    v2y = (v2y + 0.5) * SCREENHEIGHT;

    r_renderline(v1x, v1y, v2x, v2y, 0xFFFFFFFF);
}

void r_rendertestplane(void)
{
    int i;

    vec3_t verts[4];

    for(i=0; i<4; i++)
        vec3_copy(verts[i], vec3_origin);
    for(i=0; i<4; i++)
        verts[i][2] = -128;
    
    verts[0][0] = 1024;
    verts[0][1] = -1024;

    verts[1][0] = 1024;
    verts[2][1] = 1024;

    verts[2][0] = -1024;
    verts[2][1] = 1024;

    verts[3][0] = -1024;
    verts[3][1] = -1024;

    r_renderworldline(verts[0], verts[1]);
    r_renderworldline(verts[1], verts[2]);
    r_renderworldline(verts[2], verts[3]);
    r_renderworldline(verts[3], verts[0]);
}

void r_renderplayerview(void)
{
    memset(framebuffer, 0, sizeof(framebuffer));

    r_rendertestplane();
}