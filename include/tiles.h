// team booges tins 2005 entry
// baf 2005

// tiles.h
// global tile stuff

#ifndef TILES_H
#define TILES_H

#include "main.h"

typedef struct tile
{
  int flags;
  char masked;
  BITMAP *bmp;
} tile;

extern tile *_tiles;

tile *load_tiles(const char *filename);
void destroy_tiles(tile *t);

#endif
