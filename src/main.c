// team booges tins 2005 entry
// baf 2005

// main.c
// main / logging functions

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

int main(int argc, char *argv[])
{
  init();
  //game();
  deinit();
}
END_OF_MAIN()
