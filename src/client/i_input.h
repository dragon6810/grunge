#ifndef _i_input_h
#define _i_input_h

#define MAX_KEYCODE 0xFF

typedef void (*i_keyfunc_t)(void);

typedef struct
{
    const char* name;
    i_keyfunc_t down, up;
} i_keyfield_t;

extern i_keyfield_t keyfields[MAX_KEYCODE];

void i_setupinput(void);

#endif