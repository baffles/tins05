#ifndef BULLET_H
#define BULLET_H
#include <allegro.h>
#include <math.h>
#include "map.h"

typedef struct bullet {
    int sx,sy,x,y,rad, tr;
    double t,f,c,i,angle,kunt;
} bullet;    

bullet *create_bullet(int x, int y, fixed angle);
int update_bullet(bullet *blt, map *cmap);

#endif
