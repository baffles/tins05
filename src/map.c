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
  memset(ret->actor_file, '\0', 512);
  memset(ret->tile_file, '\0', 512);
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
  return ret;
}

map *load_map(const char *filename)
{
  map *ret;
  PACKFILE *file;
  int w, h, l, x, y, z, len, tw, th, sev;
  float f_ver;
  char a_file[512], t_file[512];
  file = pack_fopen(filename, "r");
  f_ver = pack_igetl(file);
  len = pack_igetl(file);
  pack_fread(a_file, len, file);
  a_file[len] = '\0';
  len = pack_igetl(file);
  pack_fread(t_file, len, file);
  t_file[len] = '\0';
  l = pack_igetl(file);
  h = pack_igetl(file);
  w = pack_igetl(file);
  
  if (strlen(a_file)) _actors = load_actors(a_file);
  if (strlen(t_file)) _tiles = load_tiles(t_file);
  ret = create_map(l, w, h);
  
  strcpy(ret->actor_file, a_file);
  strcpy(ret->tile_file, t_file);
  
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
        /* Baf... STOP ASSUMING THERE IS ALWAYS AN ACTOR... GRAWR... NO NO NO NO NO NO NO NO.. regardless
         * Even if there WERE a loaded actor FILE. wich there is not ATM, it would not neccesarily have
         * an actor ID at that point, so if sev is 0 then it just says fuckit. change what you want
         */
         
        //ret->layers[z].data[y][x].act = get_actor_instance(_actors[pack_igetl(file)]);
        
        sev = pack_igetl(file);
        if (sev && _actors) {
            ret->layers[z].data[y][x].act = get_actor_instance(_actors[sev]);
        }
         
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
  pack_iputl(1.3f, file); // put that its v1.3
  pack_iputl(strlen(ret->actor_file), file);
  pack_fwrite(ret->actor_file, strlen(ret->actor_file), file);
  pack_iputl(strlen(ret->tile_file), file);
  pack_fwrite(ret->tile_file, strlen(ret->tile_file), file);
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
        if (ret->layers[z].data[y][x].act) {
            pack_iputl(ret->layers[z].data[y][x].act->parent->id, file);
        }
        else pack_iputl(-1, file);    
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
        //free(ret->layers[z].data[y][x]);
        // baf must be drunk for that line above... bastard!
      }
      free(ret->layers[z].data[y]);
    }
    //free(ret->layers[z].data);
    // so baf, how about another drink?
    //free(ret->layers[z]);
    // GEEZ, LEARN TO CODE YOU HO
  }
  free(ret->layers);
  free(ret);
  
  destroy_actors(_actors);
  destroy_tiles(_tiles);
}
