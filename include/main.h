// team booges tins 2005 entry
// baf 2005

// main.h
// main / logging functions

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <allegro.h>

extern FILE *logfile;

#define BLOG(msg) if(logfile != NULL) fprintf(logfile, "%s: %s\n", __FUNCTION__, msg)
#define BASSERT(v) if(!(v)) { char error[4096]; sprintf(error, "Error caught!\n%s in %s on line %d\n", #v, __FILE__, __LINE__); LOG(error); printf("%s", error); exit(EXIT_FAILURE); }

int init();

#endif
