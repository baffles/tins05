#ifndef EDITPROC_H
#define EDITPROC_H
#include <allegro.h>
#include <map.h>

int eproc_init();
int eproc_fini();

int e_lw_proc(int msg, DIALOG *d, int c);
int e_ur_proc(int msg, DIALOG *d, int c);

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
    int curlayer;
    char ltex[15];
    map *mdata;
} edit_data;    

#ifndef EDITPROC_C
extern edit_data insdata;
extern MENU filemenu[];
extern MENU editmenu[];
extern MENU mm[];
extern DIALOG md[];
extern DATAFILE *sf;
#endif

     

#endif
