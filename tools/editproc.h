#ifndef EDITPROC_H
#define EDITPROC_H
#include <allegro.h>


int file_new();
int file_open();
int file_close();
int file_exit();
int file_save();

int edit_undo();
int edit_redo();



static MENU filemenu[] = {
    { "&New", file_new, NULL, 0, NULL },
    { "&Open", file_open, NULL, 0, NULL },
    { "&Save", file_save, NULL, 0, NULL },
    { "&Close", file_close, NULL, 0, NULL },
    { "E&xit", file_exit, NULL , 0, NULL }
};    

static MENU editmenu[] = {
    { "&Undo", edit_undo, NULL, 0, NULL },
    { "&Redo", edit_redo, NULL, 0, NULL }
};    

static MENU mm[] = {
    { "&File",  NULL, filemenu,  0, NULL },
    { "&Edit",  NULL, editmenu,  0, NULL }
};    

static DIALOG md[] = {
    { d_menu_proc, 0, 0, 500, 25, 0x00000000, 0x00FFFFFF, 0, 0, 0, 0, mm, NULL, NULL },
    { NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

     

#endif
