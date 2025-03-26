#ifndef _c_player_h
#define _c_player_h

#include <stdbool.h>

#include <server/s_ents.h>

extern s_player_t player;

void c_forwarddown(void);
void c_forwardup(void);
void c_leftdown(void);
void c_leftup(void);
void c_rightdown(void);
void c_rightup(void);
void c_backdown(void);
void c_backup(void);
void c_lupdown(void);
void c_lupup(void);
void c_ldowndown(void);
void c_ldownup(void);
void c_lleftdown(void);
void c_lleftup(void);
void c_lrightdown(void);
void c_lrightup(void);

#endif