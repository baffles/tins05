// team boogers tins 2005 entry
// baf 2005

// actor.c
// global actor stuff

#include "actor.h"

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
  if (!a) return;
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

actor_instance *get_actor_instance(actor *a)
{
  actor_instance *ret;
  ret = (actor_instance *)malloc(sizeof(actor_instance));
  ret->parent = a;
  ret->anim = grab_abitmap_instance(a->anim);
  ret->health = a->defhealth;
  ret->ammo = a->defammo;
  return ret;
}

void destroy_actor_instance(actor_instance *a)
{
  if (!a)
    return;
  a->parent = NULL;
  destroy_abitmap_instance(a->anim);
  free(a);
}
