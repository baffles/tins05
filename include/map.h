// team booges tins 2005 entry
// baf 2005

// map.h
// global map stuff

#ifndef MAP_H
#define MAP_H

#include "main.h"
#include "anim.h"
#include "tile.h"
#include "tiles.h"
#include "actor.h"

// flags
#define EXIT    2
#define HEALTH  4
#define AMMO    8
#define ARMOR   16
#define PIT     (EXIT | HEALTH)
#define WALKWAY (EXIT | AMMO)
#define REG_SP  32
#define TROLL1  64
#define TROLL2  128

typedef struct cell
{
  int tile, flags;
  char trans, blocking;
  actor_instance *act;
} cell;

typedef struct layer
{
  int flags;
  cell **data;
} layer;

typedef struct map
{
  int w, h, num_layers;
  char actor_file[512];
  char tile_file[512];
  layer *layers;
} map;

map *create_map(int layers, int w, int h);
map *load_map(const char *filename);
int save_map(map *map, const char *filename);
void destroy_map(map *map);

#endif
