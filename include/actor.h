// team booges tins 2005 entry
// baf 2005

// actor.h
// global actor stuff

#ifndef ACTOR_H
#define ACTOR_H

#include "main.h"
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

extern actor **_actors;

actor **load_actors(const char *filename);
int save_actors(actor **actors, const char *filename);
void destroy_actors(actor **a);

actor_instance *get_actor_instance(actor *actor);
void destroy_actor_instance(actor_instance *a);

#endif
