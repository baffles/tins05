// tilemap index file maker

#define ALLEGRO_NO_MAGIC_MAIN
#include "main.h"
#include "tiles.h"

FILE *logfile = NULL;

int main(int argc, char *argv[])
{
  char filename[512], output[512];
  int w, h, ta, td, tot, fnlen, x, y, flags, masked[2];
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
  pack_iputl(fnlen, file);
  pack_fwrite(filename, fnlen, file);
  for(y = 0; y < td; ++y)
  {
    for(x = 0; x < ta; ++x)
    {
      printf("Info for tile %d,%d in the bmp:\n\tFlags: ", x, y);
      scanf("%d", &flags);
      pack_iputl(flags, file);
      printf("\tMasked: ");
      scanf("%s", masked);
      pack_iputw(masked[0], file);
    }
  }
  pack_fclose(file);
  destroy_bitmap(src);
  return 0;
}
