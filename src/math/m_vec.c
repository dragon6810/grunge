#include "m_vec.h"

#include <math.h>

void vec3_copy(vec3_t dest, const vec3_t src)
{
    int i;

    for(i=0; i<3; i++)
        dest[i] = src[i];
}

void vec3_rotate(vec3_t out, const vec3_t v, const rot_t r)
{
    vec3_t old;
    float theta, cosine, sine;

    vec3_copy(out, v);

    theta = r[0];
    vec3_copy(old, out);
    sine = sinf(-theta);
    cosine = cosf(-theta);
    out[1] = old[1] * cosine - old[2] * sine;
    out[2] = old[2] * cosine + old[1] * sine;

    theta = r[1];
    vec3_copy(old, out);
    sine = sinf(theta);
    cosine = cosf(theta);
    out[0] = old[0] * cosine - old[2] * sine;
    out[2] = old[2] * cosine + old[0] * sine;

    theta = r[2];
    vec3_copy(old, out);
    sine = sinf(theta);
    cosine = cosf(theta);
    out[0] = old[0] * cosine - old[1] * sine;
    out[1] = old[1] * cosine + old[0] * sine;
}

void vec3_invrotate(vec3_t out, const vec3_t v, const rot_t r)
{
    vec3_t old;
    float theta, cosine, sine;

    vec3_copy(out, v);

    theta = -r[2];
    vec3_copy(old, out);
    sine = sinf(theta);
    cosine = cosf(theta);
    out[0] = old[0] * cosine - old[1] * sine;
    out[1] = old[1] * cosine + old[0] * sine;

    theta = -r[1];
    vec3_copy(old, out);
    sine = sinf(theta);
    cosine = cosf(theta);
    out[0] = old[0] * cosine - old[2] * sine;
    out[2] = old[2] * cosine + old[0] * sine;

    theta = -r[0];
    vec3_copy(old, out);
    sine = sinf(-theta);
    cosine = cosf(-theta);
    out[1] = old[1] * cosine - old[2] * sine;
    out[2] = old[2] * cosine + old[1] * sine;
}

void vec3_subtract(vec3_t out, const vec3_t a, const vec3_t b)
{
    int i;

    for(i=0; i<3; i++)
        out[i] = a[i] - b[i];
}

void vec3_scale(vec3_t out, const vec3_t v, const float scale)
{
    int i;

    for(i=0; i<3; i++)
        out[i] = v[i] * scale;
}

void vec3_scaleadd(vec3_t out, const vec3_t a, const vec3_t b, const float scale)
{
    int i;

    for(i=0; i<3; i++)
        out[i] = a[i] + b[i] * scale;
}

void vec3_normalize(vec3_t out, const vec3_t v)
{
    int i;

    float len;

    for(i=0, len=0; i<3; i++)
        len += v[i] * v[i];
    len = sqrtf(len);

    for(i=0; i<3; i++)
        out[i] = v[i] / len;
}

float vec3_dot(const vec3_t a, const vec3_t b)
{
    int i;

    float dot;

    for(i=0, dot=0; i<3; i++)
        dot += a[i] * b[i];

    return dot;
}

void vec3_cross(vec3_t out, const vec3_t a, const vec3_t b)
{
    vec3_t v;

    v[0] = a[1] * b[2] - a[2] * b[1];
    v[1] = a[2] * b[0] - a[0] * b[2];
    v[2] = a[0] * b[1] - a[1] * b[0];

    vec3_copy(out, v);
}