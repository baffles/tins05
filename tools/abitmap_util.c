// team booges tins 2005 entry
// baf 2005

// abitmap_util.c
// utility to spew out abitmaps :)

#include "main.h"
#include "timers.h"
#include "anim.h"

FILE *logfile;

int main()
{
  char c = ' ', filename[512];
  int i;
  ABITMAP *cur;
  ABITMAP_INSTANCE *cur_i;
  BITMAP *tmp; FILE *hmm;
  logfile = fopen("./abitmap_util.log", "w");
  allegro_init();
  printf("Hey. This is ABITMAP Utility coming at you live from stdout!\n");
  printf("Please choose:\n L) Load and view an abitmap\n C) Create an abitmap\n");
  while(tolower(c) != 'l' && tolower(c) != 'c')
  {
    printf("->");
    scanf("%c", &c);
    printf("\n");
  }
  if(tolower(c) == 'l')
  {
    set_color_depth(32);
    printf("Enter filename to view -> ");
    scanf("%s", filename);
    printf("\n");
    //if(file_exists(filename, FA_RDONLY, NULL) == 0)
    if((hmm = fopen(filename, "r")) == NULL)
    {
      printf("File doesnt exist! Bye bye\n");
      return -1;
    }
    fclose(hmm);
    cur = load_abitmap(filename);
    cur_i = grab_abitmap_instace(cur);
    BASSERT(cur != NULL);
    BASSERT(cur_i != NULL);
    install_keyboard();
    install_timer();
    install_timers();
    set_gfx_mode(GFX_AUTODETECT, 800, 600, 0, 0);
    while(!key[KEY_ESC])
    {
      update_animation(cur_i);
      vsync();
      clear_bitmap(screen);
      ablit(cur_i, screen, 0, 0);
    }
  }
  else
  {
    set_color_depth(32);
    cur = (ABITMAP *)malloc(sizeof(ABITMAP));
    printf("How many frames? ");
    scanf("%d", &cur->num_frames);
    printf("How many FPS? ");
    scanf("%d", &cur->fps);
    printf("Width ");
    scanf("%d", &cur->w);
    printf("Height ");
    scanf("%d", &cur->h);
    printf("Masked ");
    scanf("%d", &cur->masked);
    cur->frames = (BITMAP **)malloc(sizeof(BITMAP *) * cur->num_frames);
    for(i = 0; i < cur->num_frames; ++i)
    {
      printf("Enter filename for frame %d (bmp). -> ", i + 1);
      scanf("%s", filename);
      tmp = load_bitmap(filename, NULL);
      cur->frames[i] = create_bitmap(cur->w, cur->h);
      blit(tmp, cur->frames[i], 0, 0, 0, 0, cur->w, cur->h);
    }
    printf("Enter output filename -> ");
    scanf("%s", filename);
    save_abitmap(filename, cur);
    printf("Yay! We didnt crash!");
  }
}
END_OF_MAIN()
