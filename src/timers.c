// team booges tins 2005 entry
// baf 2005

// timers.c
// timer functions

#include "main.h"

volatile int fps = 0, cfps = 0, game_time = 0, fpsct = 0;

int install_timers()
{
  LOCK_VARIABLE(fps);
  LOCK_VARIABLE(cfps);
  LOCK_VARIABLE(game_time);
  LOCK_VARIABLE(fpsct);
  LOCK_FUNCTION(game_timer);
  return install_int_ex(game_timer, BPS_TO_TIMER(60));
}

void uninstall_timers()
{
  remove_int(game_time);
}

void game_time()
{
  ++game_timer;
  if(++fpsct == 60)
  {
    fps = cfps;
    cfps = fpsct = 0;
  }
}
END_OF_FUNCTION(game_timer)
