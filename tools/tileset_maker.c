// tilemap index file maker

#define ALLEGRO_NO_MAGIC_MAIN
#include "main.h"
#include "tiles.h"

FILE *logfile = NULL;

int main(int argc, char *argv[])
{
  char filename[512], output[512];
  int w, h, ta, td, tot, fnlen, x, y, x2, y2, flags, masked[2], col;
  BITMAP *src;
  PACKFILE *file;
  install_allegro(SYSTEM_NONE, &errno, atexit);
  printf("Tileset index file maker\n");
  printf("Please enter src bitmap filename -> ");
  scanf("%s", filename);
  set_color_depth(32);
  src = load_bitmap(filename, NULL);
  fnlen = strlen(filename);
  printf("Tile width ");
  scanf("%d", &w);
  printf("Tile height ");
  scanf("%d", &h);
  printf("Output filename ->");
  scanf("%s", output);
  ta = src->w / w;
  td = src->h / h;
  tot = ta * td;
  file = pack_fopen(output, "w");
  if(!file) return -1;
  pack_iputl(w, file);
  pack_iputl(h, file);
  //pack_iputl(fnlen, file);
  //pack_fwrite(filename, fnlen, file);
  pack_iputl(ta, file);
  pack_iputl(td, file);
  for(y = 0; y < td; ++y)
  {
    for(x = 0; x < ta; ++x)
    {
      file = pack_fopen_chunk(file, 1);
      printf("Info for tile %d,%d in the bmp:\n\tFlags: ", x, y);
      scanf("%d", &flags);
      pack_iputl(flags, file);
      printf("\tMasked: ");
      scanf("%s", masked);
      pack_iputw(masked[0], file);
      for(y2 = 0; y2 < h; ++y2)
      {
        for(x2 = 0; x2 < w; ++x2)
        {
          col = getpixel(src, x * 40 + x2, y * 40 + y2);
          //printf("(%d,%d,%d)", getr(col), getg(col), getb(col));
          pack_iputl(getr(col), file);
          pack_iputl(getg(col), file);
          pack_iputl(getb(col), file);
        }
      }
      file = pack_fclose_chunk(file);
    }
  }
  pack_fclose(file);
  destroy_bitmap(src);
  return 0;
}
