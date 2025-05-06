#ifndef _m_math_h
#define _m_math_h

#define PI 3.14159
#define DEG2RAD(x) (x / 360.0 * PI * 2.0)
#define RAD2DEG(x) (x / (PI * 2.0) * 360.0)

#define INRANGE(x, min, max) ((x >= min) && (x <= max))
#define SWAP(a, b) do             \
                   {              \
                    a ^= b;       \
                    b ^= a;       \
                    a ^= b;       \
                   } while(0)
#define CLAMP(x, min, max) do                    \
                           {                     \
                            if(x < min) x = min; \
                            if(x > max) x = max; \
                           } while(0);              

#endif