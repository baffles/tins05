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
    //{ d_box_proc, 3, 50,  500, 500, 0x000000, 0xA0A0A0, 0, 0, 0, 0, NULL, NULL, NULL },
    //{ d_box_proc, 506, 50,  42, 500, 0x000000, 0xA0A0A0, 0, 0, 0, 0, NULL, NULL, NULL },
    { d_menu_proc, 0, 0, 500, 10, 0x00000000, 0x00FFFFFF, 0, 0, 0, 0, mm, NULL, NULL },
    { d_edit_proc, 3, 16, 80, 30, 0x0, 0x00FFFFFF, 0, 0, 0, 0, insdata.ltex, NULL, NULL },
    { e_lw_proc, 3, 25, 40, 13, 0x0, 0xa0a0a0, 0, 0, 0, 0, "Down", NULL, NULL },
    { e_ur_proc, 3+40, 25, 40, 13, 0x0, 0xa0a0a0, 0, 0, 0, 0, "Up", NULL, NULL },
    { d_text_proc, 3, 38, 80, 13, 0x0, 0xC0C0C0, 0, 0, 0, 0, "Current Layer", NULL, NULL },
    { e_damnit_proc, 4, 51,  498, 498, 0x000000, 0xA0A0A0, 0, 0, 0, 0, NULL, NULL, NULL },
    { e_scrupm_proc, 4+498, 51, 30, 244, 0x0, 0xa0a0a0, 0, 0, 0, 0, "Up", NULL, NULL },
    { e_scrdwnm_proc, 4+498, 51+244, 30, 244, 0x0, 0xa0a0a0, 0, 0, 0, 0, "Dwn", NULL, NULL },
    { e_scrlftm_proc, 4, 51+498, 244, 30, 0x0, 0xa0a0a0, 0, 0, 0, 0, "Left", NULL, NULL },
    { e_scrrhtm_proc, 4+244, 51+498, 244, 30, 0x0, 0xa0a0a0, 0, 0, 0, 0, "Right", NULL, NULL },
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
    insdata.eda = sf;
    if (!sf) return -1;
    
    insdata.curlayer = 0;
    insdata.mdata = NULL;
    insdata.flags = 0;
    insdata.eda = NULL;
    insdata.tls = NULL;
    insdata.x = insdata.y = 0;
    strcpy(insdata.ltex, "0");
    
    return 0;
}
    
int eproc_fini()
{
    unload_datafile(sf);
    if (insdata.flags & F_TILES_LOADED) clear_tiles();
    if (insdata.flags & F_MAP_OPENED) e_destroymap();
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
    
    if (!(insdata.flags & F_TILES_LOADED)) {
        insdata.flags |= F_TILES_LOADED;
    }    
    
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
            insdata.x = insdata.y = 0;
            break;
            e_damnit_proc(MSG_DRAW, d, c);
        case MSG_END:
            destroy_bitmap(d->dp);
            break;
        case MSG_DRAW:
            clear_bitmap(d->dp);
            if (insdata.mdata != NULL && (insdata.flags & F_TILES_LOADED)) {
                for (y=insdata.y;y<insdata.mdata->h && y<(d->h/40);y++) {
                    for (x=insdata.x;x<insdata.mdata->w && x<(d->w/40);x++) {
                        if (insdata.mdata->layers[insdata.curlayer].data[y][x].tile >= insdata.tiles) {
                            blit(insdata.eda[0].dat, d->dp, 0, 0, (40*x), (40*y), 40, 40);
                        }
                        else {    
                            blit(insdata.psd[insdata.mdata->layers[insdata.curlayer].data[y][x].tile], d->dp, 0, 0, (40*x), (40*y),  40, 40);
                        }    
                    }    
                }    
            }
            
            if (!(insdata.flags & F_TILES_LOADED) || !insdata.mdata) rectfill(d->dp, 0, 0, d->w, d->h, 0xc0c0c0);
            
            if (!(insdata.flags & F_TILES_LOADED)) {
                textout_ex(d->dp, font, "No Tiles Loaded", 10, 10, 0x0, 0xc0c0c0);
            }    
            
            if (!insdata.mdata) {
                //rectfill(d->dp, 0, 0, d->w, d->h, 0xc0c0c0);
                textout_ex(d->dp, font, "No Map Loaded", 10, 20, 0x0, 0xc0c0c0);
            }   
            
            blit(d->dp, gui_get_screen(), 0, 0, d->x, d->y, d->w, d->h);
            
            
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

int e_scrupm_proc(int msg, DIALOG *d, int c)
{
    d_button_proc(msg, d, c);
    switch(msg) {
        case MSG_CLICK:
            if (insdata.y > 0) {
                 insdata.y -= 5;
            }
            if (insdata.y < 0) insdata.y = 0;
            d->flags &= ~D_SELECTED;
            while (mouse_b & 2);
            d_button_proc(MSG_DRAW, d, c);    
            break;
        default:
            break;
    }    
    return D_O_K;
}
    
int e_scrdwnm_proc(int msg, DIALOG *d, int c)
{
    d_button_proc(msg, d, c);
    switch(msg) {
        case MSG_CLICK:
            if (insdata.y < 10000) {
                 insdata.y += 5;
            }
            d->flags &= ~D_SELECTED;
            while (mouse_b & 2);
            d_button_proc(MSG_DRAW, d, c);    
            break;
        default:
            break;
    }    
    return D_O_K;
}
    


int e_scrlftm_proc(int msg, DIALOG *d, int c)
{
    d_button_proc(msg, d, c);
    switch(msg) {
        case MSG_CLICK:
            if (insdata.x > 0) {
                 insdata.x -= 5;
            }
            if (insdata.x < 0) insdata.y = 0;
            d->flags &= ~D_SELECTED;
            while (mouse_b & 2);
            d_button_proc(MSG_DRAW, d, c);    
            break;
        default:
            break;
    }    
    return D_O_K;
}
    
int e_scrrhtm_proc(int msg, DIALOG *d, int c)
{
    d_button_proc(msg, d, c);
    switch(msg) {
        case MSG_CLICK:
            if (insdata.x < 10000) {
                 insdata.x += 5;
            }
            d->flags &= ~D_SELECTED;
            while (mouse_b & 2);
            d_button_proc(MSG_DRAW, d, c);    
            break;
        default:
            break;
    }    
    return D_O_K;
}

      


int file_new()
{
    do_dialog(nf, -1);
    return D_REDRAW;
}
    
int file_open()
{
    int ret;
    char path[1024];
    memset(path, 0, 1024);
    ret = file_select_ex("Load a Map file.", path, NULL, 1023, 0, 0);
    if (ret == 0) return D_O_K;
    if (insdata.flags & F_MAP_OPENED) e_destroymap();
    insdata.mdata = load_map(path);
    if (insdata.mdata == NULL) return D_O_K;
    insdata.flags |= F_MAP_OPENED; 
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
    int ret;
    char path[1024];
    memset(path, 0, 1024);
    
    ret = file_select_ex("Save a Map file.", path, NULL, 1023, 0, 0);
    if (ret == 0) return D_O_K;
    
    save_map(insdata.mdata, path);
    
    return D_O_K;
}

int file_open_tiles() {
    int ret;
    char path[1024];
    memset(path, 0, 1024);
    
    ret = file_select_ex("Load a Tileset file.", path, NULL, 1023, 0, 0);
    if (ret == 0) return D_O_K;
    
    ret = load_tiles(path);
    
    
    
    return D_REDRAW;
}
    
int file_close_tiles() {
    clear_tiles();
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
    


