// team booges tins 2005 entry
// baf 2005

// main.h
// main / logging functions

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <allegro.h>
#include <aldumb.h>
#include <alfont.h>
#include <alfontdll.h>

extern FILE *logfile;
extern DUH *beyondfo;
extern DUH *ck094;
extern AL_DUH_PLAYER *dumbp;
extern ALFONT_FONT *tfont;

#define BLOG(msg) if(logfile != NULL) fprintf(logfile, "%s: %s\n", __FUNCTION__, msg)
#define BASSERT(v) if(!(v)) { char error[4096]; sprintf(error, "Error caught!\n%s in %s on line %d\n", #v, __FILE__, __LINE__); BLOG(error); printf("%s", error); exit(EXIT_FAILURE); }

int init();

void introduction();
int menu();
void about();
void game();

#endif
