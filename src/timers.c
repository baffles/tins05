// team booges tins 2005 entry
// baf 2005

// timers.c
// timer functions

#include "timers.h"

volatile int fps = 0, cfps = 0, game_time = 0, fpsct = 0, anim_counter = 0;

int install_timers()
{
  LOCK_VARIABLE(fps);
  LOCK_VARIABLE(cfps);
  LOCK_VARIABLE(game_time);
  LOCK_VARIABLE(fpsct);
  LOCK_VARIABLE(anim_counter);
  LOCK_FUNCTION(game_timer);
  return install_int_ex(game_timer, BPS_TO_TIMER(60)) == 0 ? install_int_ex(anim_timer, BPS_TO_TIMER(60)) : 1;
}

void uninstall_timers()
{
  remove_int(game_timer);
  remove_int(anim_timer);
}

void game_timer()
{
  ++game_time;
  if(++fpsct == 60)
  {
    fps = cfps;
    cfps = fpsct = 0;
  }
}
END_OF_FUNCTION(game_timer)

void anim_timer()
{
  ++anim_counter;
}
END_OF_FUNCTION(anim_timer);
