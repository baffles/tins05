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

const char *message = "Welcome to gamename, Team Booger's TINS Is Not Speedhack 2005 Entry! Programmed by BAF and Sevalecan, with artwork by Gnatinator and Brian. "
                      "Thanks to everybody who helped along the way. Thanks goes out to ahuillet, IcedRazor, and CGames for helping explain sine wave rendering to me. "
                      "See the About page for more information on Team Boogers and the game, and see the Help page for information on how to play, "
                      "and the object of the game. Thanks for downloading!     ";
int cur_index = 0, message_len = 0, char_width = 0;

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
  char_width = text_length(font, " ");
  message_len = strlen(message);
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
  dumbp = al_start_duh(beyondfo, 2, 0, 1.0f, 8192, 48000);
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
  int i, done, timeout = 0, counter, j;
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
        done = -1; // exit
      if(mouse_b & 1) // click
      {
        if((mouse_x > ((SCREEN_W / 2) - 60)) && (mouse_x < ((SCREEN_W / 2) + 60))) // its in the x range
        {
          // find which button its on.
          if(mouse_y > 220 && mouse_y < 260)
            done = 1; // play
          if(mouse_y > 280 && mouse_y < 320)
            done = 3; // about
          if(mouse_y > 340 && mouse_y < 380)
            done = 2; // help
          if(mouse_y > 400 && mouse_y < 440)
            done = -1; // exit
        }
      }
      if(timeout == 0)
      {
        if(++cur_index > message_len)
          cur_index = 0;
        timeout = 7;
      }
      if(timeout > 0)
        --timeout;
      al_poll_duh(dumbp);
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
    for(j = 0, counter = cur_index; j < SCREEN_W/char_width; ++j)
    {
      textprintf_ex(buffer, font, j * char_width, SCREEN_H - text_height(font), makecol(255,255,255), -1, "%c", message[counter]);
      if(++counter > message_len)
        counter = 0;
    }
    masked_blit(mouse_sprite, buffer, 0, 0, mouse_x, mouse_y, mouse_sprite->w, mouse_sprite->h);
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    ++cfps;
  }
  destroy_bitmap(logo);
  for(i = 0; i < 6; ++i)
    destroy_bitmap(buttons[i]);
  return done;
}


void about()
{
  // about page
  BITMAP *logo, *button, *tins;
  int i, done, timeout = 0, counter, j;
  logo = load_bitmap("../media/teampink.bmp", NULL);
  button = load_bitmap("../media/buttons/ok.bmp", NULL);
  tins = load_bitmap("../media/tins.bmp", NULL);
  done = 0;
  al_poll_duh(dumbp);
  while(!done)
  {
    while(game_time > 0)
    {
      // logic
      if(key[KEY_ESC])
        done = 1; // exit
      if(mouse_b & 1) // click
      {
        if((mouse_x > ((SCREEN_W / 2) - 60)) && (mouse_x < ((SCREEN_W / 2) + 60)) && (mouse_y > (SCREEN_H - button->h - 20)) && (mouse_y < (SCREEN_H - 20)))
        {
          done = 1; // exit
        }
      }
      if(timeout == 0)
      {
        if(++cur_index > message_len)
          cur_index = 0;
        timeout = 7;
      }
      if(timeout > 0)
        --timeout;
      al_poll_duh(dumbp);
      --game_time;
    }
    while(game_time < 0); // let it catch up
    clear_bitmap(buffer);
    masked_blit(logo, buffer, 0, 0, (SCREEN_W / 2) - (logo->w / 2), 0, logo->w, logo->h);
    textprintf_right_ex(buffer, font, SCREEN_W, 0, makecol(255,255,255), makecol(0,0,0), "FPS: %d", fps);
    alfont_textout_centre_aa_ex(buffer, tfont, "About", SCREEN_W / 2, logo->h, makecol(128, 255, 128), -1);
    //                                  "A message can be approx this long ---------------------------------------------------------->| <-- up to that line"  max of 30 lines, all preplotted below
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (0 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (1 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (2 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (3 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (4 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (5 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (6 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (7 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (8 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (9 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (10 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (11 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (12 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (13 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (14 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (15 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (16 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (17 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (18 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (19 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (20 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (21 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (22 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (23 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (24 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (25 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (26 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (27 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (28 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (29 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    //masked_blit(tins, buffer, 0, 0, ((SCREEN_W / 2) - (tins->w / 2)), logo->h + alfont_text_height(tfont), tins->w, tins->h);
    //alfont_textout_centre_aa_ex(buffer, tfont, "A Joint Production by BAF, Gnat, and Sevalecan", SCREEN_W / 2, logo->h + alfont_text_height(tfont), makecol(128, 255, 128), -1);
    /*draw_sine(100, buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(255,128,0)); // <-- ignore these tests
    draw_sine(100, buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(255,128,0));
    draw_sine(100, buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(255,128,0));
    draw_sine(100, buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(255,128,0));
    draw_sine(100, buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(255,128,0));
    draw_sine(100, buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(255,128,0));
    draw_sine(100, buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(255,128,0));
    draw_sine(100, buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(255,128,0));*/
    // draw the menu.
    blit(button, buffer, 0, 0, ((SCREEN_W / 2) - (button->w / 2)), SCREEN_H - button->h - 20, button->w, button->h);
    for(j = 0, counter = cur_index; j < SCREEN_W/char_width; ++j)
    {
      textprintf_ex(buffer, font, j * char_width, SCREEN_H - text_height(font), makecol(255,255,255), -1, "%c", message[counter]);
      if(++counter > message_len)
        counter = 0;
    }
    masked_blit(mouse_sprite, buffer, 0, 0, mouse_x, mouse_y, mouse_sprite->w, mouse_sprite->h);
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    ++cfps;
  }
  destroy_bitmap(logo);
  destroy_bitmap(button);
}

void help()
{
  // help page
  BITMAP *logo, *button, *tins;
  int i, done, timeout = 0, counter, j;
  logo = load_bitmap("../media/teampink.bmp", NULL);
  button = load_bitmap("../media/buttons/ok.bmp", NULL);
  tins = load_bitmap("../media/tins.bmp", NULL);
  done = 0;
  al_poll_duh(dumbp);
  while(!done)
  {
    while(game_time > 0)
    {
      // logic
      if(key[KEY_ESC])
        done = 1; // exit
      if(mouse_b & 1) // click
      {
        if((mouse_x > ((SCREEN_W / 2) - 60)) && (mouse_x < ((SCREEN_W / 2) + 60)) && (mouse_y > (SCREEN_H - button->h - 20)) && (mouse_y < (SCREEN_H - 20)))
        {
          done = 1; // exit
        }
      }
      if(timeout == 0)
      {
        if(++cur_index > message_len)
          cur_index = 0;
        timeout = 7;
      }
      if(timeout > 0)
        --timeout;
      al_poll_duh(dumbp);
      --game_time;
    }
    while(game_time < 0); // let it catch up
    clear_bitmap(buffer);
    masked_blit(logo, buffer, 0, 0, (SCREEN_W / 2) - (logo->w / 2), 0, logo->w, logo->h);
    textprintf_right_ex(buffer, font, SCREEN_W, 0, makecol(255,255,255), makecol(0,0,0), "FPS: %d", fps);
    alfont_textout_centre_aa_ex(buffer, tfont, "Help", SCREEN_W / 2, logo->h, makecol(128, 255, 128), -1);
    //                                  "A message can be approx this long ---------------------------------------------------------->| <-- up to that line"  max of 30 lines, all preplotted below
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (0 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (1 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (2 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (3 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (4 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (5 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (6 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (7 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (8 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (9 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (10 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (11 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (12 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (13 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (14 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (15 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (16 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (17 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (18 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (19 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (20 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (21 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (22 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (23 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (24 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (25 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (26 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (27 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (28 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    alfont_textout_aa_ex(buffer, tfont, "Spam spam spam spam spam spam spam spam SPAMMITY SPAM!", 2, logo->h + 20 + (29 * alfont_text_height(tfont)), makecol(255,255,255), -1);
    //masked_blit(tins, buffer, 0, 0, ((SCREEN_W / 2) - (tins->w / 2)), logo->h + alfont_text_height(tfont), tins->w, tins->h);
    //alfont_textout_centre_aa_ex(buffer, tfont, "A Joint Production by BAF, Gnat, and Sevalecan", SCREEN_W / 2, logo->h + alfont_text_height(tfont), makecol(128, 255, 128), -1);
    /*draw_sine(100, buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(255,128,0)); // <-- ignore these tests
    draw_sine(100, buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(255,128,0));
    draw_sine(100, buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(255,128,0));
    draw_sine(100, buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(255,128,0));
    draw_sine(100, buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(255,128,0));
    draw_sine(100, buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(255,128,0));
    draw_sine(100, buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(255,128,0));
    draw_sine(100, buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(255,128,0));*/
    // draw the menu.
    blit(button, buffer, 0, 0, ((SCREEN_W / 2) - (button->w / 2)), SCREEN_H - button->h - 20, button->w, button->h);
    for(j = 0, counter = cur_index; j < SCREEN_W/char_width; ++j)
    {
      textprintf_ex(buffer, font, j * char_width, SCREEN_H - text_height(font), makecol(255,255,255), -1, "%c", message[counter]);
      if(++counter > message_len)
        counter = 0;
    }
    masked_blit(mouse_sprite, buffer, 0, 0, mouse_x, mouse_y, mouse_sprite->w, mouse_sprite->h);
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    ++cfps;
  }
  destroy_bitmap(logo);
  destroy_bitmap(button);
}

void game()
{
  // We gotta do something
  int done = 0;
  // load data & level
  int cx = 0, cy = 0; fixed cdirection = 0, cmoving = 0;
  int t1x = 0, t1y = 0; fixed t1direction = 0, t1moving = 0;
  int t2x = 0, t2y = 0; fixed t2direction = 0, t2moving = 0;
  ABITMAP *character, *troll1, *troll2;
  ABITMAP_INSTANCE *char_ins, *troll1_ins, *troll2_ins;
  character = load_abitmap("../media/mainchar.abm");
  char_ins = grab_abitmap_instance(character);
  troll1 = load_abitmap("../media/troll01.abm");
  troll1_ins = grab_abitmap_instance(troll1);
  troll2 = load_abitmap("../media/troll02.abm");
  troll2_ins = grab_abitmap_instance(troll2);
  al_stop_duh(dumbp);
  dumbp = al_start_duh(ck094, 2, 0, 1.0f, 8192, 48000);
  while(!done)
  {
    while(game_time > 0)
    {
      // logic
      poll_keyboard();
      if(key[KEY_ESC])
        done = 1;
      
      // character
      if(key[KEY_LEFT] && cx > 0)
      {
        --cx;
        cdirection = itofix(192);
        cmoving = 1;
      }
      if(key[KEY_RIGHT] && cx < SCREEN_W)
      {
        ++cx;
        cdirection = itofix(64);
        cmoving = 1;
      }
      if(key[KEY_UP] && cy > 0)
      {
        --cy;
        cdirection = itofix(0);
        cmoving = 1;
      }
      if(key[KEY_DOWN] && cy < SCREEN_H)
      {
        ++cy;
        cdirection = itofix(128);
        cmoving = 1;
      }
      if(cmoving)
      {
        // kinda redundant, but check for diaganols and display it correctly
        if(key[KEY_UP] && key[KEY_LEFT])
        {
          cdirection = itofix(224);
        }
        if(key[KEY_UP] && key[KEY_RIGHT])
        {
          cdirection = itofix(32);
        }
        if(key[KEY_DOWN] && key[KEY_LEFT])
        {
          cdirection = itofix(160);
        }
        if(key[KEY_DOWN] && key[KEY_RIGHT])
        {
          cdirection = itofix(96);
        }
      }
      // troll 1
      if(key[KEY_4_PAD] && t1x > 0)
      {
        --cx;
        t1direction = itofix(192);
        t1moving = 1;
      }
      if(key[KEY_6_PAD] && t1x < SCREEN_W)
      {
        ++t1x;
        t1direction = itofix(64);
        t1moving = 1;
      }
      if(key[KEY_8_PAD] && t1y > 0)
      {
        --t1y;
        t1direction = itofix(0);
        t1moving = 1;
      }
      if(key[KEY_2_PAD] && t1y < SCREEN_H)
      {
        ++t1y;
        t1direction = itofix(128);
        t1moving = 1;
      }
      if(t1moving)
      {
        // kinda redundant, but check for diaganols and display it correctly
        if(key[KEY_8_PAD] && key[KEY_4_PAD])
        {
          t1direction = itofix(224);
        }
        if(key[KEY_8_PAD] && key[KEY_6_PAD])
        {
          t1direction = itofix(32);
        }
        if(key[KEY_2_PAD] && key[KEY_4_PAD])
        {
          t1direction = itofix(160);
        }
        if(key[KEY_2_PAD] && key[KEY_6_PAD])
        {
          t1direction = itofix(96);
        }
      }
      // troll 2
      if(key[KEY_A] && t2x > 0)
      {
        --t2x;
        t2direction = itofix(192);
        t2moving = 1;
      }
      if(key[KEY_D] && t2x < SCREEN_W)
      {
        ++t2x;
        t2direction = itofix(64);
        t2moving = 1;
      }
      if(key[KEY_W] && t2y > 0)
      {
        --t2y;
        t2direction = itofix(0);
        t2moving = 1;
      }
      if(key[KEY_S] && t2y < SCREEN_H)
      {
        ++t2y;
        t2direction = itofix(128);
        t2moving = 1;
      }
      if(t2moving)
      {
        // kinda redundant, but check for diaganols and display it correctly
        if(key[KEY_W] && key[KEY_A])
        {
          t2direction = itofix(224);
        }
        if(key[KEY_W] && key[KEY_D])
        {
          t2direction = itofix(32);
        }
        if(key[KEY_S] && key[KEY_A])
        {
          t2direction = itofix(160);
        }
        if(key[KEY_S] && key[KEY_D])
        {
          t2direction = itofix(96);
        }
      }
      
      if(cmoving)
        update_animation(char_ins);
      cmoving = 0;
      if(t1moving)
        update_animation(troll1_ins);
      t1moving = 0;
      if(t2moving)
        update_animation(troll2_ins);
      t2moving = 0;
      
      ++soffset;
      
      al_poll_duh(dumbp);
      --game_time;
    }
    while(game_time < 0); // let it catch up, no need in doing extra logic / drawing cycles
    // draw
    clear_bitmap(buffer);
    ablit_r(char_ins, buffer, cx, cy, cdirection);
    ablit_r(troll1_ins, buffer, t1x, t1y, t1direction);
    ablit_r(troll2_ins, buffer, t2x, t2y, t2direction);
    textprintf_right_ex(buffer, font, SCREEN_W, 0, makecol(255,255,255), makecol(0,0,0), "FPS: %d", fps);
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    ++cfps;
  }
  destroy_abitmap_instance(char_ins);
  destroy_abitmap(character);
  //sleep(100);
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
      case 1:
        // start a new game
        game();
        sleep(100);
        poll_keyboard();
        al_stop_duh(dumbp);
        dumbp = al_start_duh(beyondfo, 2, 0, 1.0f, 8192, 48000);
        al_poll_duh(dumbp);
        break;
      case 2:
        // show the help page
        help();
        sleep(100);
        poll_keyboard();
        break;
      case 3:
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
