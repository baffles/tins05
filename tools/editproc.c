#define EDITPROC_C
#include "editproc.h"

edit_data insdata;
DATAFILE *sf;

MENU filemenu[] = {
    { "&New", file_new, NULL, 0, NULL },
    { "&Open", file_open, NULL, 0, NULL },
    { "&Save", file_save, NULL, 0, NULL },
    { "&Close", file_close, NULL, 0, NULL },
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
    { d_box_proc, 506, 50,  80, 500, 0x000000, 0xA0A0A0, 0, 0, 0, 0, NULL, NULL, NULL },
    { d_menu_proc, 0, 0, 500, 10, 0x00000000, 0x00FFFFFF, 0, 0, 0, 0, mm, NULL, NULL },
    { d_edit_proc, 3, 16, 80, 30, 0x0, 0x00FFFFFF, 0, 0, 0, 0, insdata.ltex, NULL, NULL },
    { e_lw_proc, 3, 25, 40, 13, 0x0, 0xa0a0a0, 0, 0, 0, 0, "Down", NULL, NULL },
    { e_ur_proc, 3+40, 25, 40, 13, 0x0, 0xa0a0a0, 0, 0, 0, 0, "Up", NULL, NULL },
    //{ d_ctext_proc, 3+250, 50+250, 0, 0, 0x000000, 0xA0A0A0, 0, 0, 0, 0, "-=Workspace=-", NULL, NULL },
    { NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};



int eproc_init()
{
    sf = load_datafile("editor.dat");
    if (!sf) return -1;
    
    insdata.curlayer = 0;
    strcpy(insdata.ltex, "0");
    
    return 0;
}
    
int eproc_fini()
{
    unload_datafile(sf);
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


int file_new()
{
    return 0;
}
    
int file_open()
{
    return D_O_K;
}
    
int file_close()
{
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

int edit_undo()
{
    return D_O_K;
}
    
int edit_redo()
{
    return D_O_K;
}
    


