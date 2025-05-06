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

const float nearplane = 1;
const float farplane = 4096;

vec3_t frustumplanesn[6];
float frustumplanesd[6];

void r_findfrustumplanes(void)
{
    int i;

    float farsize[2];
    vec3_t planepoints[3];
    vec3_t farquad[4];
    vec3_t basis[2];
    vec3_t a, b;

    // Front and back planes
    vec3_copy(frustumplanesn[0], vec3_origin);
    frustumplanesn[0][0] = -1;
    frustumplanesd[0] = -nearplane;
    vec3_copy(frustumplanesn[1], vec3_origin);
    frustumplanesn[1][0] = 1;
    frustumplanesd[1] = farplane;

    farsize[0] = tanf(DEG2RAD(FOV) * 0.5) * farplane;
    farsize[1] = farsize[0] * ((float) SCREENHEIGHT / (float) SCREENWIDTH);
    for(i=0; i<4; i++)
    {
        vec3_copy(basis[0], vec3_origin);
        switch(i)
        {
            case 0:
            case 1:
                basis[0][1] = -1;
                break;
            default:
                basis[0][1] = 1;
        }
        vec3_copy(basis[1], vec3_origin);
        switch(i)
        {
            case 1:
            case 2:
                basis[1][2] = 1;
                break;
            default:
                basis[1][2] = -1;
        }

        vec3_copy(farquad[i], vec3_origin);
        vec3_scaleadd(farquad[i], farquad[i], basis[0], farsize[0]);
        vec3_scaleadd(farquad[i], farquad[i], basis[1], farsize[1]);
        farquad[i][0] = farplane;
    }

    vec3_copy(planepoints[0], vec3_origin);
    for(i=0; i<4; i++)
    {
        vec3_copy(planepoints[1], farquad[i]);
        vec3_copy(planepoints[2], farquad[(i+1)%4]);
        vec3_subtract(a, planepoints[1], planepoints[0]);
        vec3_subtract(b, planepoints[2], planepoints[0]);
        vec3_cross(frustumplanesn[i+2], a, b);
        vec3_normalize(frustumplanesn[i+2], frustumplanesn[i+2]);
        printf("( %f %f %f ) x ( %f %f %f ) = ( %f %f %f )\n",
            a[0], a[1], a[2],
            b[0], b[1], b[2],
            frustumplanesn[i+2][0], frustumplanesn[i+2][1], frustumplanesn[i+2][2]);
        frustumplanesd[i+2] = 0;

        //printf("distances: %f %f %f\n", 
        //    vec3_dot(planepoints[0], frustumplanesn[i+2]),
        //    vec3_dot(planepoints[1], frustumplanesn[i+2]),
        //    vec3_dot(planepoints[2], frustumplanesn[i+2]));
    }
}

int r_cliplinetofrustum(const vec3_t v1, const vec3_t v2, vec3_t out1, vec3_t out2)
{
    int i;

    vec3_t o1, o2;
    float d1, d2, t;
    vec3_t r, p;
    bool didclip;

    vec3_copy(o1, v1);
    vec3_copy(o2, v2);

    for(i=0, didclip=false; i<6; i++)
    {
        d1 = vec3_dot(o1, frustumplanesn[i]) - frustumplanesd[i];
        d2 = vec3_dot(o2, frustumplanesn[i]) - frustumplanesd[i];

        if(d1 <= 0 && d2 <= 0)
            continue;
        if(d1 > 0 && d2 > 0)
            return 0;

        // line crosses
        vec3_subtract(r, o2, o1);
        vec3_normalize(r, r);
        
        t = -d1 / (vec3_dot(r, frustumplanesn[i]));
        vec3_scaleadd(p, o1, r, t);
        if(d1 > 0)
            vec3_copy(o1, p);
        else
            vec3_copy(o2, p);

        didclip = true;
    }

    if(out1)
        vec3_copy(out1, o1);
    if(out2)
        vec3_copy(out2, o2);

    return didclip ? 2 : 1;
}

void r_renderworldline(const vec3_t v1, const vec3_t v2)
{
    rot_t revrot;
    float v1x, v1y, v2x, v2y;
    float hplane, vplane;
    float t;
    float slope;
    vec3_t r;
    vec3_t v1local, v2local;
    float d1, d2;

    vec3_scale(revrot, player.rot, -1);
    vec3_subtract(v1local, v1, player.pos);
    vec3_subtract(v2local, v2, player.pos);
    vec3_invrotate(v1local, v1local, player.rot);
    vec3_invrotate(v2local, v2local, player.rot);

    if(!r_cliplinetofrustum(v1local, v2local, v1local, v2local))
        return;

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

    if(v1x < 0)
        v1x = 0;
    if(v1x > SCREENWIDTH-1)
        v1x = SCREENWIDTH-1;
    if(v2x < 0)
        v2x = 0;
    if(v2x > SCREENWIDTH-1)
        v2x = SCREENWIDTH-1;
    if(v1y < 0)
        v1y = 0;
    if(v1y > SCREENHEIGHT-1)
        v1y = SCREENHEIGHT-1;
    if(v2y < 0)
        v2y = 0;
    if(v2y > SCREENHEIGHT-1)
        v2y = SCREENHEIGHT-1;

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

    r_findfrustumplanes();

    r_rendertestplane();
}