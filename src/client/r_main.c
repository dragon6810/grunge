#include "r_main.h"

#include <stdio.h>
#include <string.h>
#include <math/m_math.h>

#include "i_video.h"

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

void r_rendertestplane(void)
{
    r_renderline(0, 0, SCREENWIDTH-1, SCREENHEIGHT-1, 0xFFFFFFFF);
    r_renderline(0, SCREENHEIGHT-1, SCREENWIDTH-1, 0, 0xFFFFFFFF);

    r_renderline(0, 0, SCREENWIDTH>>1, SCREENHEIGHT-1, 0xFFFFFFFF);
    r_renderline(SCREENWIDTH>>1, 0, SCREENWIDTH-1, SCREENHEIGHT-1, 0xFFFFFFFF);
    r_renderline(0, SCREENHEIGHT-1, SCREENWIDTH>>1, 0, 0xFFFFFFFF);
    r_renderline(SCREENWIDTH>>1, SCREENHEIGHT-1, SCREENWIDTH-1, 0, 0xFFFFFFFF);
    
    r_renderline(SCREENWIDTH>>1, 0, SCREENWIDTH>>1, SCREENHEIGHT-1, 0xFFFFFFFF);
    r_renderline(0, SCREENHEIGHT>>1, SCREENWIDTH-1, SCREENHEIGHT>>1, 0xFFFFFFFF);
}

void r_renderplayerview(void)
{
    memset(framebuffer, 0, sizeof(framebuffer));

    r_rendertestplane();
}