// team booges tins 2005 entry
// baf 2005

// render.c
// rendering functions

#include "render.h"

void draw_sine(int length, BITMAP *b, int startx, int starty, int stopx, int stopy, int col)
{
  fixed x, y;
  fixed angle = 0;
  fixed angle_stepsize = itofix(1);
  
  while(fixtoi(angle) < 256)
  {
    x = angle + startx;
    y = (length * fsin(angle)) + starty;
    putpixel(b, fixtoi (x), fixtoi(y) + SCREEN_H / 2, col);
    angle += angle_stepsize;
  }
}
