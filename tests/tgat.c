#include <allegro.h>
#include <sblend.h>

int main() {
    BITMAP *ttga;
    
    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT, 1152,864,0,0);
    
    ttga = load_bitmap("..//media//microsoft.tga", NULL);
    
    clear_bitmap(screen);
    
    sblend_32(ttga, screen, 0, 0, 0, 0, ttga->w, ttga->h);
    
    readkey();
    
    destroy_bitmap(ttga);
    set_gfx_mode(GFX_TEXT,0,0,0,0);
    return 0;
}
END_OF_MAIN();

    
