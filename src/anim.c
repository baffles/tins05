// team booges tins 2005 entry
// baf 2005

// anim.c
// animation stuff

#include "anim.h"

int lac = 0;

ABITMAP *load_abitmap(const char *filename)
{
  PACKFILE *abmp;
  ABITMAP *ret;
  int i, x, y;
  abmp = pack_fopen(filename, "r");
  if(!abmp)
    return NULL;
  ret = (ABITMAP *)malloc(sizeof(ABITMAP));
  ret->num_frames = pack_igetl(abmp);
  ret->fps = pack_igetl(abmp);
  ret->w = pack_igetl(abmp);
  ret->h = pack_igetl(abmp);
  ret->masked = pack_igetl(abmp);
  ret->frames = (BITMAP **)malloc(sizeof(BITMAP *) * ret->num_frames);
  for(i = 0; i < ret->num_frames; ++i)
  {
    abmp = pack_fopen_chunk(abmp, 1);
    ret->frames[i] = create_bitmap(ret->w, ret->h);
    for(y = 0; y < ret->h; ++y)
      for(x = 0; x < ret->w; ++x)
        putpixel(ret->frames[i], x, y, makecol(pack_igetl(abmp), pack_igetl(abmp), pack_igetl(abmp)));
    abmp = pack_fclose_chunk(abmp);
  }
  pack_fclose(abmp);
  return ret;
}

int save_abitmap(const char *filename, ABITMAP *bmp)
{
  PACKFILE *abmp;
  int i, x, y, col;
  abmp = pack_fopen(filename, "w");
  if(!abmp)
    return -1;
  pack_iputl(bmp->num_frames, abmp);
  pack_iputl(bmp->fps, abmp);
  pack_iputl(bmp->w, abmp);
  pack_iputl(bmp->h, abmp);
  pack_iputl(bmp->masked, abmp);
  for(i = 0; i < bmp->num_frames; ++i)
  {
    abmp = pack_fopen_chunk(abmp, 1);
    for(y = 0; y < bmp->h; ++y)
    {
      for(x = 0; x < bmp->w; ++x)
      {
        col = getpixel(bmp->frames[i], x, y);
        pack_iputl(getr(col), abmp);
        pack_iputl(getg(col), abmp);
        pack_iputl(getb(col), abmp);
      }
    }
    abmp = pack_fclose_chunk(abmp);
  }
  pack_fclose(abmp);
}

ABITMAP_INSTANCE *grab_abitmap_instance(ABITMAP *bmp)
{
  ABITMAP_INSTANCE *ret;
  ret = (ABITMAP_INSTANCE *)malloc(sizeof(ABITMAP_INSTANCE));
  ret->parent = bmp;
  ret->curframe = 0;
  return ret;
}


void destroy_abitmap(ABITMAP *bmp)
{
  int i;
  for(i = 0; i < bmp->num_frames; ++i)
    destroy_bitmap(bmp->frames[i]);
  free(bmp->frames);
  free(bmp);
}

void destroy_abitmap_instance(ABITMAP_INSTANCE *bmp)
{
  free(bmp);
}


void update_animation(ABITMAP_INSTANCE *bmp)
{
  BASSERT(bmp);
  
 /* if(anim_counter == lac)
    return;
  lac = anim_counter;*/
  
  // anim_counter goes up by 60 each second... we gotta calculate this with frames per second.
  // update. the curframe.
  if(anim_counter % (60 / bmp->parent->fps) == 0)
    ++bmp->curframe;
  
   // we dont want segfaults ;)
  if(bmp->curframe >= bmp->parent->num_frames)
    bmp->curframe %= bmp->parent->num_frames;
  
  // keep it from overflowing
  if(anim_counter >= 60)
    anim_counter -= 60;
}

void ablit(ABITMAP_INSTANCE *source, BITMAP *dest, int dest_x, int dest_y)
{
  BASSERT(source);
  BASSERT(source->parent);
  BASSERT(source->parent->frames);
  //printf("%d ", source->curframe);
  if(source->parent->masked)
    masked_blit(source->parent->frames[source->curframe], dest, 0, 0, dest_x, dest_y, source->parent->w, source->parent->h);
  else
    blit(source->parent->frames[source->curframe], dest, 0, 0, dest_x, dest_y, source->parent->w, source->parent->h);
}

void ablit_r(ABITMAP_INSTANCE *source, BITMAP *dest, int dest_x, int dest_y, fixed angle)
{
  rotate_sprite(dest, source->parent->frames[source->curframe], dest_x, dest_y, angle);
}
