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
  char anim_filename[512];
  int maxhealth, maxammo, defhealth, defammo, toughness, aggressiveness, id;
} actor;

typedef struct actor_instance
{
  actor *parent;
  ABITMAP_INSTANCE *anim;
  int health, ammo;
} actor_instance;


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
  layer *layers;
} map;

map *create_map(int layers, int w, int h);
map *load_map(const char *filename);
int save_map(map *map, const char *filename);
void destroy_map(map *map);

// actors
extern actor **_actors;

actor **load_actors(const char *filename);
int save_actors(actor **actors, const char *filename);
void destroy_actors(actor **a);

actor_instance *get_actor_instance(actor *actor);
void destroy_actor_instance(actor_instance *a);

#endif
