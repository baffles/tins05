// team booges tins 2005 entry
// baf 2005

// timers.h
// timer functions

#ifndef TIMERS_H
#define TIMERS_H

#include "main.h"

extern volatile int fps, cfps, game_time, anim_counter;

int install_timers();
void uninstall_timers();

void game_timer();
void anim_timer();

#endif
