// team booges tins 2005 entry
// baf 2005

// main.c
// main / logging functions

#include "main.h"
#include "timers.h"
#include "anim.h"
#include "render.h"
//#error i dont want this compiling atm.
FILE *logfile = NULL;
DUH *beyondfo;
DUH *ck094;
AL_DUH_PLAYER *dumbp;
ALFONT_FONT *tfont;

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
  if(install_mouse() < 0)
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
  /*dumb_register_packfiles();
  beyondfo = dumb_load_mod("../media/music.dat#BEYONDFO");
  ck094 = dumb_load_it("../media/music.dat#CK094");*/
  dumb_register_stdfiles();
  beyondfo = dumb_load_mod("../beyondfo.mod");
  ck094 = dumb_load_it("../media/ck094.it");
  alfont_init();
  tfont = alfont_load_font("../media/BIRDMAN.TTF");
  alfont_set_font_size(tfont, 14);
}

void deinit()
{
  if(logfile)
    fclose(logfile);
  logfile = NULL;
  unload_duh(beyondfo);
  unload_duh(ck094);
  dumb_exit();
  alfont_destroy_font(tfont);
  alfont_exit();
}
void this_is_temporary() { al_poll_duh(dumbp); }

void introduction()
{
  BITMAP *logo;
  dumbp = al_start_duh(beyondfo, 2, 0, 1.0f, 4096, 4410);
  logo = load_bitmap("../media/logo86.bmp", NULL);
  blit(logo, screen, 0, 0, 0, 0, 800, 600);
  install_int_ex(this_is_temporary, BPS_TO_TIMER(2));
  sleep(3000);
  al_stop_duh(dumbp);
}

int menu()
{
  BITMAP *logo, *buffer;
  logo = load_bitmap("../media/teampink.bmp", NULL);
  buffer = create_bitmap(SCREEN_W, SCREEN_H);
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
    clear_bitmap(buffer);
    masked_blit(logo, buffer, 0, 0, (SCREEN_W / 2) - (logo->w / 2), 0, logo->w, logo->h);
    textprintf_right_ex(buffer, font, SCREEN_W, 0, makecol(255,255,255), makecol(0,0,0), "FPS: %d", fps);
    alfont_textout_centre_aa_ex(buffer, tfont, "Welcome to... gamename!", SCREEN_W / 2, logo->h, makecol(128, 255, 128), -1);
    draw_sine(100, buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(255,128,0));
    draw_sine(100, buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(255,128,0));
    draw_sine(100, buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(255,128,0));
    draw_sine(100, buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(255,128,0));
    draw_sine(100, buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(255,128,0));
    draw_sine(100, buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(255,128,0));
    draw_sine(100, buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(255,128,0));
    draw_sine(100, buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(255,128,0));
    masked_blit(mouse_sprite, buffer, 0, 0, mouse_x, mouse_y, mouse_sprite->w, mouse_sprite->h);
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    ++cfps;
  }
  destroy_bitmap(buffer);
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
