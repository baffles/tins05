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

BITMAP *buffer;

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
  beyondfo = dumb_load_mod("../media/beyondfo.mod");
  ck094 = dumb_load_it("../media/ck094.it");
  alfont_init();
  tfont = alfont_load_font("../media/BIRDMAN.TTF");
  alfont_set_font_size(tfont, 14);
  buffer = create_bitmap(SCREEN_W, SCREEN_H);
}

void deinit()
{
  destroy_bitmap(buffer);
  if(logfile)
    fclose(logfile);
  logfile = NULL;
  unload_duh(beyondfo);
  unload_duh(ck094);
  dumb_exit();
  alfont_destroy_font(tfont);
  alfont_exit();
}

void introduction()
{
  BITMAP *logo;
  dumbp = al_start_duh(beyondfo, 2, 0, 1.0f, 8192, 4800);
  logo = load_bitmap("../media/logo86.bmp", NULL);
  blit(logo, screen, 0, 0, 0, 0, 800, 600);
  al_poll_duh(dumbp);
  sleep(750);
  al_poll_duh(dumbp);
  sleep(750);
  al_poll_duh(dumbp);
  sleep(750);
  al_poll_duh(dumbp);
  sleep(750);
  al_poll_duh(dumbp);
}

int menu()
{
  BITMAP *logo, *buttons[6];
  int i, done;
  logo = load_bitmap("../media/teampink.bmp", NULL);
  buttons[0] = load_bitmap("../media/buttons/about.bmp", NULL);
  buttons[1] = load_bitmap("../media/buttons/back.bmp", NULL);
  buttons[2] = load_bitmap("../media/buttons/help.bmp", NULL);
  buttons[3] = load_bitmap("../media/buttons/ok.bmp", NULL);
  buttons[4] = load_bitmap("../media/buttons/play.bmp", NULL);
  buttons[5] = load_bitmap("../media/buttons/exit.bmp", NULL);
  //tins = load_bitmap("../media/tins.bmp", NULL);
  done = 0;
  al_poll_duh(dumbp);
  while(!done)
  {
    while(game_time > 0)
    {
      // logic
      if(key[KEY_ESC])
        return -1; // exit
      if(mouse_b & 1) // click
      {
        if((mouse_x > ((SCREEN_W / 2) - 60)) && (mouse_x < ((SCREEN_W / 2) + 60))) // its in the x range
        {
          // find which button its on.
          if(mouse_y > 220 && mouse_y < 260)
            return 0; // play
          if(mouse_y > 280 && mouse_y < 320)
            return 2; // about
          if(mouse_y > 340 && mouse_y < 380)
            return 1; // help
          if(mouse_y > 400 && mouse_y < 440)
            return -1; // exit
        }
        al_poll_duh(dumbp);
      }
      --game_time;
    }
    while(game_time < 0); // let it catch up
    clear_bitmap(buffer);
    masked_blit(logo, buffer, 0, 0, (SCREEN_W / 2) - (logo->w / 2), 0, logo->w, logo->h);
    textprintf_right_ex(buffer, font, SCREEN_W, 0, makecol(255,255,255), makecol(0,0,0), "FPS: %d", fps);
    alfont_textout_centre_aa_ex(buffer, tfont, "Welcome to. . . gamename!", SCREEN_W / 2, logo->h, makecol(128, 255, 128), -1);
    //masked_blit(tins, buffer, 0, 0, ((SCREEN_W / 2) - (tins->w / 2)), logo->h + alfont_text_height(tfont), tins->w, tins->h);
    alfont_textout_centre_aa_ex(buffer, tfont, "A Joint Production by BAF, Gnat, and Sevalecan", SCREEN_W / 2, logo->h + alfont_text_height(tfont), makecol(128, 255, 128), -1);
    /*draw_sine(100, buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(255,128,0)); // <-- ignore these tests
    draw_sine(100, buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(255,128,0));
    draw_sine(100, buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(255,128,0));
    draw_sine(100, buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(255,128,0));
    draw_sine(100, buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(255,128,0));
    draw_sine(100, buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(255,128,0));
    draw_sine(100, buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(255,128,0));
    draw_sine(100, buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(255,128,0));*/
    // draw the menu.
    blit(buttons[4], buffer, 0, 0, ((SCREEN_W / 2) - (buttons[4]->w / 2)), 220, buttons[4]->w, buttons[4]->h);
    blit(buttons[0], buffer, 0, 0, ((SCREEN_W / 2) - (buttons[0]->w / 2)), 280, buttons[0]->w, buttons[0]->h);
    blit(buttons[2], buffer, 0, 0, ((SCREEN_W / 2) - (buttons[2]->w / 2)), 340, buttons[2]->w, buttons[2]->h);
    blit(buttons[5], buffer, 0, 0, ((SCREEN_W / 2) - (buttons[5]->w / 2)), 400, buttons[5]->w, buttons[5]->h);
    masked_blit(mouse_sprite, buffer, 0, 0, mouse_x, mouse_y, mouse_sprite->w, mouse_sprite->h);
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    ++cfps;
  }
  destroy_bitmap(logo);
  for(i = 0; i < 6; ++i)
    destroy_bitmap(buttons[i]);
}


void about()
{
  // about page
}

void help()
{
  // help page
}

void game()
{
  // We gotta do something
  int done = 0;
  // load data & level
  int x = 0, y = 0; fixed direction = 0, moving = 0;
  ABITMAP *character;
  ABITMAP_INSTANCE *char_ins;
  character = load_abitmap("../media/mainchar.abm");
  char_ins = grab_abitmap_instance(character);
  while(!done)
  {
    while(game_time > 0)
    {
      // logic
      if(key[KEY_ESC])
        done = 1;
      if(key[KEY_LEFT] && x > 0)
      {
        --x;
        direction = itofix(192);
        moving = 1;
      }
      if(key[KEY_RIGHT] && x < SCREEN_W)
      {
        ++x;
        direction = itofix(64);
        moving = 1;
      }
      if(key[KEY_UP] && y > 0)
      {
        --y;
        direction = itofix(0);
        moving = 1;
      }
      if(key[KEY_DOWN] && y < SCREEN_H)
      {
        ++y;
        direction = itofix(128);
        moving = 1;
      }
      if(moving)
        update_animation(char_ins);
      moving = 0;
      al_poll_duh(dumbp);
      --game_time;
    }
    while(game_time < 0); // let it catch up, no need in doing extra logic / drawing cycles
    // draw
    clear_bitmap(buffer);
    ablit_r(char_ins, buffer, x, y, direction);
    textprintf_right_ex(buffer, font, SCREEN_W, 0, makecol(255,255,255), makecol(0,0,0), "FPS: %d", fps);
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    ++cfps;
  }
  destroy_abitmap_instance(char_ins);
  destroy_abitmap(character);
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
        game();
        sleep(100);
        poll_keyboard();
        break;
      case 1:
        // show the help page
        help();
        sleep(100);
        poll_keyboard();
        break;
      case 2:
        // show the about page
        about();
        sleep(100);
        poll_keyboard();
        break;
      default:
        // exit
        done = 1;
        break;
    }
  }
  al_stop_duh(dumbp);
  deinit();
}
END_OF_MAIN()
