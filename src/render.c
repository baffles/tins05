// team booges tins 2005 entry
// baf 2005

// render.c
// rendering functions

#include "render.h"

int soffset;

/*
<ahuillet>   for(int i = 0; i < wave->size; i ++)
<ahuillet>                 putpixel(wave->temp, i, 5 + 5*sin(3.14159 * (10* i + wave->offset) / 180), 4);
<r4z01> you can use cos(x) = sin(x + 90) I think
<ahuillet>         pivot_sprite(vscreen, wave->temp, wave->refpt.x, wave->refpt.y, 0, 5 + 5*sin(3.14159 * wave->offset) / 180, ftofix(- 256 * wave->angle / 360));
*/

void draw_sine(int length, BITMAP *b, int startx, int starty, int stopx, int stopy, int col)
{
  /*fixed x, y;
  fixed angle = 0;
  fixed angle_stepsize = itofix(1);
  
  while(fixtoi(angle) < 256)
  {
    x = angle + startx;
    y = (length * fsin(angle)) + starty;
    putpixel(b, fixtoi (x), fixtoi(y) + SCREEN_H / 2, col);
    angle += angle_stepsize;
  }*/
  int i;
  
}
