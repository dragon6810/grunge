#ifndef _m_vec_h
#define _m_vec_h

typedef float vec3_t[3];
// roll, pitch, yaw
typedef vec3_t rot_t;

const static vec3_t vec3_origin = { 0, 0, 0};

void vec3_copy(vec3_t dest, const vec3_t src);
void vec3_rotate(vec3_t out, const vec3_t v, const rot_t r);
void vec3_invrotate(vec3_t out, const vec3_t v, const rot_t r);
void vec3_subtract(vec3_t out, const vec3_t a, const vec3_t b);
void vec3_scale(vec3_t out, const vec3_t v, const float scale);
void vec3_scaleadd(vec3_t out, const vec3_t a, const vec3_t b, const float scale);
void vec3_normalize(vec3_t out, const vec3_t v);
float vec3_dot(const vec3_t a, const vec3_t b);
void vec3_cross(vec3_t out, const vec3_t a, const vec3_t b);

#endif