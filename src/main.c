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
  BASSERT(install_keyboard() == 0);
  BASSERT(install_timer() == 0);
  if(install_mouse() != 0)
    BLOG("Couldn't initialize mouse... non-fatal, continuing.");
  
}

int main(int argc, char *argv[])
{
  init();
}
END_OF_MAIN()
