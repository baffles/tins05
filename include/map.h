// team booges tins 2005 entry
// baf 2005

// map.h
// global map stuff

#ifndef MAP_H
#define MAP_H

#include "anim.h"

typedef struct actor 
{
    ABITMAP *anim;
    int maxhealth, maxammo, toughness, aggressiveness, etc;
} actor;

typedef struct actor_instance
{
    actor *parent;
    ABITMAP_INSTANCE *anim;
    int health, ammo;
} actor_instance;


typedef struct cell
{
  int tile, flags, trans, blocking;
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
  layer *layers;
} map;

map *load_map(char *filename);
int save_map(map *map, char *filename);
void destroy_map(map *map);

#endif
