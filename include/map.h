// team booges tins 2005 entry
// baf 2005

// map.h
// global map stuff

#ifndef MAP_H
#define MAP_H

typedef struct cell
{
  int tile, flags, trans, blocking;
} cell;

typedef struct layer
{
  int w, h, sx, sy;
  cell **data;
} layer;

typedef struct map
{
  int w, h, layers;
  layer *layers;
} map;

map *load_map(char *filename);
int save_map(map *map, char *filename);

#endif