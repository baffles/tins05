// team boogers tins 2005 entry
// baf 2005

// map.c
// global map stuff

#include "map.h"

map *create_map(int layers, int w, int h)
{
  map *ret;
  int x, y, z;
  ret = (map *)malloc(sizeof(map));
  ret->w = w;
  ret->h = h;
  ret->num_layers = layers;
  ret->layers = (layer *)malloc(sizeof(layer) * layers);
  for(z = 0; z < layers; ++z)
  {
    ret->layers[z].flags = 0;
    ret->layers[z].data = (cell **)malloc(sizeof(cell *) * h);
    for(y = 0; y < h; ++y)
    {
      ret->layers[z].data[y] = (cell *)malloc(sizeof(cell) * w);
      for(x = 0; x < w; ++x)
      {
        ret->layers[z].data[y][x].tile = ret->layers[z].data[y][x].flags = ret->layers[z].data[y][x].trans = ret->layers[z].data[y][x].blocking = 0;
        ret->layers[z].data[y][x].act = NULL;
      }
    }
  }
}

map *load_map(const char *filename)
{
  map *ret;
  PACKFILE *file;
  int w, h, l, x, y, z, len;
  char a_file[512];
  file = pack_fopen(filename, "r");
  len = pack_igetl(file);
  pack_fread(a_file, len, file);
  l = pack_igetl(file);
  h = pack_igetl(file);
  w = pack_igetl(file);
  strcpy(ret->actor_file, a_file);
  _actors = load_actors(a_file);
  ret = create_map(l, w, h);
  ret->w = w;
  ret->h = h;
  ret->num_layers = l;
  for(z = 0; z < l; ++z)
  {
    file = pack_fopen_chunk(file, 1);
    ret->layers[z].flags = pack_igetl(file);
    for(y = 0; y < h; ++y)
    {
      for(x = 0; x < w; ++x)
      {
        ret->layers[z].data[y][x].tile = pack_igetl(file);
        ret->layers[z].data[y][x].flags = pack_igetl(file);
        ret->layers[z].data[y][x].trans = pack_igetw(file);
        ret->layers[z].data[y][x].blocking = pack_igetw(file);
        ret->layers[z].data[y][x].act = get_actor_instance(_actors[pack_igetl(file)]);
      }
    }
    file = pack_fclose_chunk(file);
  }
  pack_fclose(file);
  return ret;
}

int save_map(map *ret, const char *filename)
{
  PACKFILE *file;
  int x, y, z;
  file = pack_fopen(filename, "w");
  if(!file)
    return -1;
  pack_iputl(strlen(ret->actor_file), file);
  pack_fwrite(ret->actor_file, strlen(ret->actor_file), file);
  pack_iputl(ret->num_layers, file);
  pack_iputl(ret->h, file);
  pack_iputl(ret->w, file);
  for(z = 0; z < ret->num_layers; ++z)
  {
    file = pack_fopen_chunk(file, 1);
    pack_iputl(ret->layers[z].flags, file);
    for(y = 0; y < ret->h; ++y)
    {
      for(x = 0; x < ret->w; ++x)
      {
        pack_iputl(ret->layers[z].data[y][x].tile, file);
        pack_iputl(ret->layers[z].data[y][x].flags, file);
        pack_iputw(ret->layers[z].data[y][x].trans, file);
        pack_iputw(ret->layers[z].data[y][x].blocking, file);
        pack_iputl(ret->layers[z].data[y][z].act->id, file);
      }
    }
    file = pack_fclose_chunk(file);
  }
  pack_fclose(file);
  return 0;
}

void destroy_map(map *ret)
{
  int x, y, z;
  for(z = 0; z < ret->num_layers; ++z)
  {
    for(y = 0; y < ret->num_layers; ++y)
    {
      for(x = 0; x < ret->num_layers; ++x)
      {
        destroy_actor_instance(ret->layers[z].data[y][x].act);
        free(ret->layers[z].data[y][x]);
      }
      free(ret->layers[z].data[y]);
    }
    free(ret->layers[z].data);
    free(ret->layers[z]);
  }
  free(ret->layers);
  free(ret);
  
  destroy_actors(_actors);
}


// actor stuff
actor **_actors = NULL;

actor **load_actors(const char *filename)
{
  actor **ret;
  PACKFILE *file;
  int i, tot, len;
  char *abfilename;
  file = pack_fopen(filename, "r");
  tot = pack_igetl(file);
  ret = (actor **)malloc(sizeof(actor *) * (tot + 1));
  for(i = 0; i < tot; ++i)
  {
    file = pack_fopen_chunk(file, 1);
    ret[i] = (actor *)malloc(sizeof(actor));
    len = pack_igetl(file);
    abfilename = (char *)malloc(len + 1);
    pack_fread(abfilename, len, file);
    ret[i]->anim = load_abitmap(abfilename);
    free(abfilename);
    ret[i]->maxhealth = pack_igetl(file);
    ret[i]->maxammo = pack_igetl(file);
    ret[i]->defhealth = pack_igetl(file);
    ret[i]->defammo = pack_igetl(file);
    ret[i]->toughness = pack_igetl(file);
    ret[i]->aggressiveness = pack_igetl(file);
    ret[i]->id = i;
    file = pack_fclose_chunk(file);
  }
  pack_fclose(file);
  ret[tot] = NULL;
  return ret;
}

int save_actors(actor **actors, const char *filename)
{
  PACKFILE *file;
  int i, tot = 0;
  file = pack_fopen(filename, "w");
  if(!file)
    return -1;
  while(1)
  {
    if(actors[tot])
      ++tot;
    else
      break;
  }
  pack_iputl(tot, file);
  for(i = 0; i < tot; ++i)
  {
    file = pack_fopen_chunk(file, 1);
    pack_iputl(strlen(actors[i]->anim_filename), file);
    pack_fwrite(actors[i]->anim_filename, strlen(actors[i]->anim_filename), file);
    pack_iputl(actors[i]->maxhealth, file);
    pack_iputl(actors[i]->maxammo, file);
    pack_iputl(actors[i]->defhealth, file);
    pack_iputl(actors[i]->defammo, file);
    pack_iputl(actors[i]->toughness, file);
    pack_iputl(actors[i]->aggressiveness, file);
    file = pack_fclose_chunk(file);
  }
  pack_fclose(file);
  return 0;
}

void destroy_actors(actor **a)
{
  int i, tot = 0;
  while(1)
  {
    if(a[tot])
      ++tot;
    else
      break;
  }
  for(i = 0; i < tot; ++i)
  {
    destroy_abitmap(a[i]->anim);
    free(a[i]);
  }
  free(a);
}

actor_instance *get_actor_instance(actor *actor)
{
  actor_instance *ret;
  ret = (actor_instance *)malloc(sizeof(actor_instance));
  ret->parent = actor;
  ret->anim = grab_abitmap_instance(actor->anim);
  ret->health = actor->defhealth;
  ret->ammo = actor->defammo;
  return ret;
}

void destroy_actor_instance(actor_instance *a)
{
  a->parent = NULL;
  destroy_abitmap_instance(a->anim);
  free(a);
}
