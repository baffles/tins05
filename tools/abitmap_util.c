// team booges tins 2005 entry
// baf 2005

// abitmap_util.c
// utility to spew out abitmaps :)

#include "main.h"
#include "timers.h"
#include "anim.h"

FILE *logfile;
BITMAP *buffer;

int main()
{
  char c = ' ', filename[512];
  int i;
  ABITMAP *cur;
  ABITMAP_INSTANCE *cur_i;
  BITMAP *tmp; FILE *hmm;
  logfile = fopen("./abitmap_util.log", "w");
  printf("Hey. This is ABITMAP Utility coming at you live from stdout!\n");
  printf("Please choose:\n L) Load and view an abitmap\n C) Create an abitmap\n E) Edit an abitmap\n");
  while(tolower(c) != 'l' && tolower(c) != 'c' && tolower(c) != 'e')
  {
    printf("->");
    scanf("%c", &c);
    printf("\n");
  }
  if(tolower(c) == 'l')
  {
    printf("Enter filename to view -> ");
    scanf("%s", filename);
    printf("\n");
    //if(file_exists(filename, FA_RDONLY, NULL) == 0)
    /*if((hmm = fopen(filename, "r")) == NULL)
    {
      printf("File doesnt exist! Bye bye\n");
      return -1;
    }
    fclose(hmm);*/
    allegro_init();
    set_color_depth(32);
    cur = load_abitmap(filename);
    if(!cur)
    {
      printf("File doesn't exist! Bye bye\n");
      return -1;
    }
    cur_i = grab_abitmap_instance(cur);
    BASSERT(cur != NULL);
    BASSERT(cur_i != NULL);
    install_keyboard();
    install_timer();
    install_timers();
    set_gfx_mode(GFX_AUTODETECT, 800, 600, 0, 0);
    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    i = 0;
    while(!key[KEY_ESC])
    {
      if(i != anim_counter)
        update_animation(cur_i);
      i = anim_counter;
      vsync();
      clear_bitmap(buffer);
      ablit(cur_i, buffer, 0, 0);
      textprintf_right_ex(buffer, font, SCREEN_W, 0, makecol(255,255,255), makecol(0,0,0), "Frame: %d | ABM FPS: %d", cur_i->curframe, cur->fps);
      textprintf_right_ex(buffer, font, SCREEN_W, 10, makecol(255,255,255), makecol(0,0,0), "%d", anim_counter % (60 / cur->fps));
      textprintf_right_ex(buffer, font, SCREEN_W, 20, makecol(255,255,255), makecol(0,0,0), "DEBUG - cur frame count: %d", anim_counter);
      blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
      //sleep(60 / cur->fps + 10);
    }
  }
  else if(tolower(c) == 'e')
  {
    int done = 0;
    printf("Enter filename to edit -> ");
    scanf("%s", filename);
    printf("\n");
    install_allegro(SYSTEM_NONE, &errno, atexit);
    set_color_depth(32);
    cur = load_abitmap(filename);
    if(!cur) return -1;
    printf("Loaded %s\n", filename);
    printf("Settings:\n\tFPS: %d\n\tMasked: %d\n", cur->fps, cur->masked);
    printf("New FPS -> ");
    scanf("%d", &cur->fps);
    printf("New Masked -> ");
    scanf("%d", &cur->masked);
    save_abitmap(filename, cur);
    printf("Modified");
  }
  else
  {
    install_allegro(SYSTEM_NONE, &errno, atexit);
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
