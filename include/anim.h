// team booges tins 2005 entry
// baf 2005

// anim.h
// animation stuff

#ifndef ANIM_H
#define ANIM_H

#include "main.h"
#include "timers.h"

typedef struct ABITMAP
{
  int num_frames, fps, w, h;
  BITMAP **frames;
} ABITMAP:

typedef struct ABITMAP_INSTANCE
{
  ABITMAP *parent;
  int curframe;
} ABITMAP_INSTANCE;

ABITMAP *load_abitmap(const char *filename);
int save_abitmap(const char *filename, ABITMAP *bmp);
ABTIMAP_INSTANCE *grab_instance(ABITMAP *bmp);

void destroy_abitmap(ABITMAP *bmp);
void destroy_abitmap_instance(ABITMAP_INSTANCE *bmp);

void update_animation(ABITMAP_INSTANCE *bmp);
void ablit(ABITMAP_INSTANCE *source, BITMAP *dest, int dest_x, int dest_y);

#endif
