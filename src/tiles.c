// team boogers tins 2005 entry
// baf 2005

// tiles.c
// global tile stuff

#include "tiles.h"

tile *_tiles = NULL;

tile *load_tiles(const char *filename)
{
  int i, x, y, x2, y2, w, h, len, ta, td, r,g,b;
  char filename_[512];
  tile *ret;
  PACKFILE *file;
  BITMAP *src;
  file = pack_fopen(filename, "r");
  if(!file)
    return NULL;
  w = pack_igetl(file);
  h = pack_igetl(file);
  //len = pack_igetl(file);
  //pack_fread(filename_, len, file);
  //filename_[len] = '\0';
  //src = load_bitmap(filename_, NULL);
  //ta = src->w / w;
  //td = src->h / h;
  ta = pack_igetl(file);
  td = pack_igetl(file);
  ret = (tile *)malloc(sizeof(tile) * ((ta * td) + 1));
  for(y = 0; y < td; ++y)
  {
    for(x = 0; x < ta; ++x)
    {
      file = pack_fopen_chunk(file, 1);
      i = (y * ta) + x;
      ret[i].flags = pack_igetl(file);
      ret[i].masked = pack_igetw(file);
      ret[i].bmp = create_bitmap(w, h);
      //blit(src, ret[i].bmp, x * w, y * h, 0, 0, w, h);
      for(y2 = 0; y2 < h; ++y2)
      {
        for(x2 = 0; x2 < w; ++x2)
        {
          putpixel(ret[i].bmp, x2, y2, makecol(pack_igetl(file), pack_igetl(file), pack_igetl(file)));
        }
      }
      file = pack_fclose_chunk(file);
    }
  }
  ret[ta * td].bmp = NULL;
  pack_fclose(file);
  //destroy_bitmap(src);
  return ret;
}

void destroy_tiles(tile *t)
{
  if(!t)
    return;
  int tot = 0, i;
  while(1)
  {
    if(t[tot].bmp != NULL)
      ++tot;
    else
      break;
  }
  for(i = 0; i < tot; ++i)
    destroy_bitmap(t[i].bmp);
  free(t);
}
