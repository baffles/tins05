#include <allegro.h>
//#include <map.h>
#include <sblend.h>

#include "editproc.h"


    

int main() {
    allegro_init();
    install_keyboard();
    install_timer();
    install_mouse();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
    
    do_dialog(md, -1);
    
    
    set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
    return 0;
}
END_OF_MAIN();
    


