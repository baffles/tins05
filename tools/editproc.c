#define EDITPROC_C
#include "editproc.h"

edit_data insdata;
DATAFILE *sf;

char n_WD[5];
char n_HG[5];
char n_LY[5];

MENU filemenu[] = {
    { "&New", file_new, NULL, 0, NULL },
    { "&Open", file_open, NULL, 0, NULL },
    { "&Save", file_save, NULL, 0, NULL },
    { "&Close", file_close, NULL, 0, NULL },
    { "", NULL, NULL, 0, NULL },
    { "O&pen Tiles", file_open_tiles, NULL, 0, NULL },
    { "C&lose Tiles", file_close_tiles, NULL, 0, NULL },
    { "", NULL, NULL, 0, NULL },
    { "E&xit", file_exit, NULL , 0, NULL }
};    

MENU editmenu[] = {
    { "&Undo", edit_undo, NULL, 0, NULL },
    { "&Redo", edit_redo, NULL, 0, NULL },
    { "&Copy", edit_redo, NULL, 0, NULL },
    { "&Paste", edit_redo, NULL, 0, NULL }
};    

MENU mm[] = {
    { "&File",  NULL, filemenu,  0, NULL },
    { "&Edit",  NULL, editmenu,  0, NULL }
};    

DIALOG md[] = {
    { d_clear_proc, 0, 0, 800, 600, 0x00c0c0c0, 0x00c0c0c0, 0, 0, 0, 0, NULL, NULL, NULL },
    { d_box_proc, 3, 50,  500, 500, 0x000000, 0xA0A0A0, 0, 0, 0, 0, NULL, NULL, NULL },
    { d_box_proc, 506, 50,  42, 500, 0x000000, 0xA0A0A0, 0, 0, 0, 0, NULL, NULL, NULL },
    { d_menu_proc, 0, 0, 500, 10, 0x00000000, 0x00FFFFFF, 0, 0, 0, 0, mm, NULL, NULL },
    { d_edit_proc, 3, 16, 80, 30, 0x0, 0x00FFFFFF, 0, 0, 0, 0, insdata.ltex, NULL, NULL },
    { e_lw_proc, 3, 25, 40, 13, 0x0, 0xa0a0a0, 0, 0, 0, 0, "Down", NULL, NULL },
    { e_ur_proc, 3+40, 25, 40, 13, 0x0, 0xa0a0a0, 0, 0, 0, 0, "Up", NULL, NULL },
    { e_damnit_proc, 4, 51,  498, 498, 0x000000, 0xA0A0A0, 0, 0, 0, 0, NULL, NULL, NULL },
    //{ d_ctext_proc, 3+250, 50+250, 0, 0, 0x000000, 0xA0A0A0, 0, 0, 0, 0, "-=Workspace=-", NULL, NULL },
    { NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};


// this was the first thing that came to mind for a dialog that got info for a new map. so.. dont ask why i did it!

DIALOG nf[] = {
    { d_clear_proc, 0, 0, 800, 600, 0x00c0c0c0, 0x00c0c0c0, 0, 0, 0, 0, NULL, NULL, NULL },
    { d_text_proc, 3, 3, 0, 0, 0x0, 0xc0c0c0, 0, 0, 0, 0, "Width:", NULL, NULL },
    { d_text_proc, 3, 13, 0, 0, 0x0, 0xc0c0c0, 0, 0, 0, 0, "Height:", NULL, NULL },
    { d_text_proc, 3, 23, 0, 0, 0x0, 0xc0c0c0, 0, 0, 0, 0, "Layers:", NULL, NULL },
    { d_edit_proc, 60, 3, 80, 10, 0x0, 0xFFFFFF, 0, 0, 4, 0, n_WD, NULL, NULL },
    { d_edit_proc, 60, 13, 80, 10, 0x0, 0xFFFFFF, 0, 0, 4, 0, n_HG, NULL, NULL },
    { d_edit_proc, 60, 23, 80, 10, 0x0, 0xFFFFFF, 0, 0, 4, 0, n_LY, NULL, NULL },
    { e_sbutton_proc, 3, 33, 140, 15, 0x0, 0xc0c0c0, 0, 0, 0, 0, "Create Map", NULL, NULL },
    { NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL }
};    



int eproc_init()
{
    sf = load_datafile("editor.dat");
    if (!sf) return -1;
    
    insdata.curlayer = 0;
    insdata.mdata = NULL;
    insdata.flags = 0;
    insdata.eda = NULL;
    insdata.tls = NULL;
    strcpy(insdata.ltex, "0");
    
    return 0;
}
    
int eproc_fini()
{
    unload_datafile(sf);
    return 0;
}

int load_tiles(char *filename) {
    int g, h;
    
    if (insdata.flags & F_TILES_LOADED) clear_tiles();
    insdata.tls = load_datafile(filename);
    if (insdata.tls == NULL) return -1;
    
    for (g=0;insdata.tls[g].type != DAT_END;g++);
    g += 1;
    
    insdata.psd = malloc(sizeof(BITMAP *)*g);
    if (insdata.psd == NULL) {
        unload_datafile(insdata.tls);
        return -2;
    }    
    
    for (h=0;h<g;h++) {
        insdata.psd[h] = insdata.tls[h].dat;
    }    
    insdata.tiles = g;
    
    insdata.flags |= F_TILES_LOADED;
    
    return 0;
}    

int clear_tiles() {
    if (insdata.flags & F_TILES_LOADED) {
        free(insdata.psd);
        unload_datafile(insdata.tls);
        insdata.tiles = 0;
        insdata.psd = NULL;
        insdata.tls = NULL;
        insdata.flags &= ~F_TILES_LOADED;
    }    
    return 0;
}  



int e_makemap() {
    if (insdata.flags & F_MAP_OPENED) e_destroymap();
    
    if ( atoi(n_LY) && atoi(n_WD) && atoi(n_HG) ) { // create the map then
        insdata.mdata = create_map(atoi(n_LY), atoi(n_WD), atoi(n_HG));
        if (insdata.mdata == NULL) return -2;
        
    }
    else return -1;
    
    return 0;
}    

int e_destroymap() {
    if (insdata.flags & F_MAP_OPENED) {
        insdata.flags &= ~F_MAP_OPENED;
        destroy_map(insdata.mdata);
    }    
    return 0;
}
    

  


int e_lw_proc(int msg, DIALOG *d, int c) {
    int ret;
    
    
    ret = d_button_proc(msg, d, c);
    if (msg == MSG_CLICK) {
        while (mouse_b & 2);
        d->flags &= ~D_SELECTED;
        d_button_proc(MSG_DRAW, d, c);
        ret = D_REDRAW;
        
        insdata.curlayer--;
        if (insdata.curlayer < 0) insdata.curlayer = 0;
        sprintf(insdata.ltex, "%u", insdata.curlayer);
        
    }    
    
    return ret;
}      

int e_ur_proc(int msg, DIALOG *d, int c) {
    int ret;
    
    
    ret = d_button_proc(msg, d, c);
    if (msg == MSG_CLICK) {
        while (mouse_b & 2);
        d->flags &= ~D_SELECTED;
        d_button_proc(MSG_DRAW, d, c);
        ret = D_REDRAW;
        
        insdata.curlayer++;
        if (insdata.curlayer < 0) insdata.curlayer = 0;
        sprintf(insdata.ltex, "%u", insdata.curlayer);
        
    }    
    
    return ret;
}




int e_damnit_proc(int msg, DIALOG *d, int c) {
    
    int x,y;
    
    switch(msg) {
        case MSG_START:
            d->dp = create_bitmap(d->w, d->h);
            d->d1 = d->d2 = 0;
            break;
        case MSG_END:
            destroy_bitmap(d->dp);
            break;
        case MSG_DRAW:
            
            if (insdata.mdata != NULL && (insdata.flags & F_TILES_LOADED)) {
                for (y=d->d1;y<insdata.mdata->h && y<(d->h/40);y++) {
                    for (x=d->d2;x<insdata.mdata->w && x<(d->w/40);x++) {
                        if (insdata.mdata->layers[insdata.curlayer].data[y][x].tile >= insdata.tiles) {
                            blit(insdata.eda[0].dat, d->dp, 0, 0, 40, 40, (40*x), (40*y));
                        }
                        else {    
                            blit(insdata.psd[insdata.mdata->layers[insdata.curlayer].data[y][x].tile], d->dp, 0, 0, 40, 40, (40*x), (40*y));
                        }    
                    }    
                }    
            }
            
            if (!(insdata.flags & F_TILES_LOADED)) {
                rectfill(d->dp, 0, 0, d->w, d->h, 0xc0c0c0);
                textout_ex(d->dp, font, "No Tiles Loaded", 10, 10, 0x0, 0xc0c0c0);
            }    
            
            if (!insdata.mdata) {
                rectfill(d->dp, 0, 0, d->w, d->h, 0xc0c0c0);
                textout_ex(d->dp, font, "No Map Loaded", 10, 20, 0x0, 0xc0c0c0);
            }   
            
            blit(d->dp, gui_get_screen(), 0, 0, d->w, d->h, 0, 0);
            
            
            break;
        case MSG_GOTMOUSE:
            break;    
        default:
            break;
    }    
    
    return D_O_K;
}
    

int e_sbutton_proc(int msg, DIALOG *d, int c) {
    int ret;
    ret = d_button_proc(msg, d, c);
    if (msg == MSG_CLICK) {
        while (mouse_b & 2);
        d->flags &= ~D_SELECTED;
        d_button_proc(MSG_DRAW, d, c);
        ret = D_CLOSE;
        e_makemap();
    }    
    return ret;
}    


      


int file_new()
{
    do_dialog(nf, -1);
    return D_REDRAW;
}
    
int file_open()
{
    return D_O_K;
}
    
int file_close()
{
    e_destroymap();
    return D_O_K;
}
    
int file_exit()
{
    return D_CLOSE;
}
    
int file_save()
{
    return D_O_K;
}

int file_open_tiles() {
    return D_O_K;
}
    
int file_close_tiles() {
    return D_O_K;
}    
    

int edit_undo()
{
    return D_O_K;
}
    
int edit_redo()
{
    return D_O_K;
}
    


