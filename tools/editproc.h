#ifndef EDITPROC_H
#define EDITPROC_H
#include <allegro.h>
#include <map.h>

int eproc_init();
int eproc_fini();

int file_new();
int file_open();
int file_close();
int file_exit();
int file_save();

int edit_undo();
int edit_redo();


typedef struct edit_data {
    char fn[256]; // current filename
    int flags;
    map *mdata;
} edit_data;

edit_data insdata;    

#ifndef EDITPROC_C
extern MENU filemenu[];
extern MENU editmenu[];
extern MENU mm[];
extern DIALOG md[];
extern DATAFILE *sf;
#endif

     

#endif
