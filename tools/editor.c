#include <allegro.h>
#include <sblend.h>

#include "editproc.h"

   

int main() {
    int ret;
    
    
    ret = allegro_init();
    if (ret) {
        printf("Error %u\n", 1); 
        return -1;
    }       
    
    ret = install_keyboard();
    if (ret) {
        printf("Error %u\n", 2); 
        return -2;
    }  
    
    ret = install_timer();
    if (ret) {
        printf("Error %u\n", 3);
        return -3;
    }  
    
    ret = install_mouse();
    if (ret < 0) {
        printf("Error %u\n", 4);
        return -4;
    }  
    
    set_color_depth(32);
    ret = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0); // blah!
    if (ret) {
        set_color_depth(desktop_color_depth());
        ret = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
        if (ret) {
            ret = set_gfx_mode(GFX_SAFE, 800, 600, 0, 0);
            if (ret) {
                 printf("Error %u\n", 5); 
                 return -5;
            }  
        }    
    }    
    
    ret = eproc_init();
    if (ret) {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        return -6;
    }    
    
    do_dialog(md, -1);
    
    eproc_fini();
    
    set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
    return 0;
}
END_OF_MAIN();
    


