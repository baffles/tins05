#ifndef EDITPROC_H
#define EDITPROC_H
#include <allegro.h>
#include <map.h>

int eproc_init();
int eproc_fini();

int load_tiles(char *filename);
int clear_tiles();
int e_makemap();
int e_destroymap();

int e_lw_proc(int msg, DIALOG *d, int c);
int e_ur_proc(int msg, DIALOG *d, int c);
int e_damnit_proc(int msg, DIALOG *d, int c);
int e_sbutton_proc(int msg, DIALOG *d, int c);

int file_new();
int file_open();
int file_close();
int file_exit();
int file_save();
int file_open_tiles();
int file_close_tiles();


int edit_undo();
int edit_redo();

#define F_TILES_LOADED 0x1
#define F_MAP_OPENED   0x2

typedef struct edit_data {
    DATAFILE *eda;
    char fn[256]; // current filename
    int flags;
    int curlayer;
    char ltex[15];
    int tiles;
    DATAFILE *tls;
    BITMAP **psd;
    map *mdata;
} edit_data;    

#ifndef EDITPROC_C
extern edit_data insdata;
extern MENU filemenu[];
extern MENU editmenu[];
extern MENU mm[];
extern DIALOG md[];
extern char n_WD[];
extern char n_HG[];
extern char n_LY[];
extern DIALOG nf[];
extern DATAFILE *sf;
#endif

     

#endif
