// team booges tins 2005 entry
// baf 2005

// main.c
// main / logging functions

#include "main.h"
#include "timers.h"
#include "anim.h"
#error i dont want this compiling atm.
FILE *logfile = NULL;

int init()
{
  char tempstr[512];
  logfile = fopen("./gamelog.log", "w");
  if(!logfile)
  {
    logfile = NULL;
    printf("WARNING: Couldn't open logfile. Logs are disabled\n");
  }
  sprintf(tempstr, "Initializing using Allegro %s", ALLEGRO_VERSION_STR);
  BLOG(tempstr);
  BASSERT(allegro_init() == 0);
  set_config_file("./game.ini");
  BASSERT(install_keyboard() == 0);
  BASSERT(install_timer() == 0);
  if(install_mouse() != 0)
    BLOG("Couldn't initialize mouse... non-fatal, continuing.");
  if(install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0)
    BLOG("Couldn't install a sound driver... non-fatal, continuing.");
  set_color_depth(32);
  if(set_gfx_mode(GFX_AUTODETECT, 800, 600, 0, 0) != 0)
  {
    set_color_depth(24);
    if(set_gfx_mode(GFX_AUTODETECT, 800, 600, 0, 0) != 0)
    {
      set_color_depth(16);
      if(set_gfx_mode(GFX_AUTODETECT, 800, 600, 0, 0) != 0)
      {
        set_color_depth(15);
        if(set_gfx_mode(GFX_AUTODETECT, 800, 600, 0, 0) != 0)
        {
          sprintf(tempstr, "Cannot set a graphics mode, %s", allegro_error);
          BLOG(tempstr);
          exit(EXIT_FAILURE);
        }
      }
    }
  }
  BASSERT(install_timers());
}

void deinit()
{
  if(logfile)
    fclose(logfile);
  logfile = NULL;
}


void introduction()
{
  BITMAP *logo;
  logo = load_bitmap("../media/logo86.bmp", NULL);
  blit(logo, screen, 0, 0, 0, 0, 800, 600);
  sleep(3000);
}

int menu()
{
  BITMAP *logo;
  logo = load_bitmap("../media/logo.bmp", NULL);
  int done = 0;
  while(!done)
  {
    while(game_time > 0)
    {
      // logic
      if(keypressed())
        return -1; // exit
      --game_time;
    }
    while(game_time < 0); // let it catch up
    blit(logo, screen, 0, 0, (SCREEN_W / 2) - (logo->w / 2), 0, logo->w, logo->h);
    textprintf_right_ex(screen, font, SCREEN_W, 0, makecol(255,255,255), makecol(0,0,0), "FPS: %d", fps);
    masked_blit(mouse_sprite, screen, 0, 0, mouse_x, mouse_y, mouse_sprite->w, mouse_sprite->h);
    ++cfps;
  }
}

void game()
{
  // We gotta do something
  int done = 0;
  // load data & level
  while(!done)
  {
    while(game_time > 0)
    {
      // logic
      --game_time;
    }
    while(game_time < 0); // let it catch up, no need in doing extra logic / drawing cycles
    // draw
    ++cfps;
  }
}


int main(int argc, char *argv[])
{
  int menu_choice, done = 0;
  init();
  introduction();
  while(!done)
  {
    menu_choice = menu();
    switch(menu_choice)
    {
      case 0:
        // start a new game
        break;
      case 1:
        // show the help page
        break;
      case 2:
        // show the about page
        break;
      default:
        // exit
        done = 1;
        break;
    }
  }
  deinit();
}
END_OF_MAIN()
