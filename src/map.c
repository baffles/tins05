// team boogers tins 2005 entry
// baf 2005

// map.c
// global map stuff

#include "map.h"

/*typedef struct actor 
{
    ABITMAP *anim;
    int maxhealth, maxammo, toughness, aggressiveness;
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
} map;*/

map *create_map(int layers, int w, int h)
{
  map *ret;
  int x, y, z;
  ret = (map *)malloc(sizeof(map));
  map->w = w;
  map->h = h;
  map->num_layers = layers;
  map->layers = (layer *)malloc(sizeof(layer) * layers);
  for(z = 0; z < layers; ++z)
  {
    map->layers[z]->flags = 0;
    map->layers[z]->data = (cell **)malloc(sizeof(cell *) * h);
    for(y = 0; y < h; ++y)
    {
      map->layers[z]->data[y] = (cell *)malloc(sizeof(cell) * w);
      for(x = 0; x < w; ++x)
      {
        map->layers[z]->data[y][x]->tile = map->layers[z]->data[y][x]->flags = map->layers[z]->data[y][x]->trans = map->layers[z]->data[y][x]->blocking = 0;
        map->layers[z]->data[y][x]->act = NULL;
      }
    }
  }
}

map *load_map(const char *filename)
{
  map *ret;
  PACKFILE *file;
  int w, h, l, x, y, z;
  file = pack_fopen(filename, "r");
  l = pack_igetl(file);
  h = pack_igetl(file);
  w = pack_igetl(file);
  ret = create_map(l, w, h);
  ret->w = w;
  ret->h = h;
  ret->num_layers = l;
  for(z = 0; z < l; ++z)
  {
    file = pack_fopen_chunk(file, 1);
    ret->layers[z]->flags = pack_igetl(file);
    for(y = 0; y < h; ++y)
    {
      for(x = 0; x < w; ++x)
      {
        ret->layers[z]->data[y][x]->tile = pack_igetl(file);
        ret->layers[z]->data[y][x]->flags = pack_igetl(file);
        ret->layers[z]->data[y][x]->trans = pack_igetw(file);
        ret->layers[z]->data[y][x]->blocking = pack_igetw(file);
        ret->layers[z]->data[y][x]->act = get_actor_instance(_actors[pack_igetl(file)]);
      }
    }
    file = pack_fclose_chunk(file);
  }
  pack_fclose(file);
  return ret;
}

int save_map(map *map, const char *filename)
{
  PACKFILE *file;
  int x, y, z;
  file = pack_fopen(filename, "w");
  if(!file)
    return -1;
  pack_iputl(map->num_layers, file);
  pack_iputl(map->h, file);
  pack_iputl(map->w, file);
  for(z = 0; z < map->num_layers; ++z)
  {
    file = pack_fopen_chunk(file, 1);
    pack_iputl(map->layers[z]->flags, file);
    for(y = 0; y < map->h; ++y)
    {
      for(x = 0; x < map->w; ++x)
      {
        pack_iputl(map->layers[z]->data[y][x]->tile, file);
        pack_iputl(map->layers[z]->data[y][x]->flags, file);
        pack_iputw(map->layers[z]->data[y][x]->trans, file);
        pack_iputw(map->layers[z]->data[y][x]->blocking, file);
        pack_iputl(map->layers[z]->data[y][z]->act->id, file);
      }
    }
    file = pack_fclose_chunk(file);
  }
  pack_fclose(file);
  return 0;
}

void destroy_map(map *map)
{
  int x, y, z;
  for(z = 0; z < map->num_layers; ++z)
  {
    for(y = 0; y < map->num_layers; ++y)
    {
      for(x = 0; x < map->num_layers; ++x)
      {
        destroy_actor_instance(map->layers[z]->data[y][x]->act);
        free(map->layers[z]->data[y][x]);
      }
      free(map->layers[z]->data[y]);
    }
    free(map->layers[z]->data);
    free(map->layers[z]);
  }
  free(map->layers);
  free(map);
}


// actor stuff

actor **load_actors(const char *filename);
int save_actors(actor **actors, const char *filename);
void destroy_actors(actor **a);

actor_instance *get_actor_instance(actor *actor);
void destroy_actor_instance(actor_instance *a);
