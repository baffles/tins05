#include "bullet.h"

bullet *create_bullet(int x, int y, fixed angle) {
    bullet *ret;
    ret = malloc(sizeof(bullet));
    
    memset(ret, 0, sizeof(bullet));
    ret->x = x;
    ret->y = y;
    ret->rad = 1;
    ret->tr = 30;
    ret->f = M_PI*2;
    ret->c = 0.;
    ret->angle = fixtof(angle);
    
    
    return ret;
}    

int update_bullet(bullet *blt, map *cmap) {
    int x,y,z;
    
    z = 1;
    
    blt->rad+=2;
    blt->c++;
    blt->t = (blt->f*blt->rad)/blt->tr;
    blt->t = blt->f/blt->t;
    blt->i = cos(blt->c) * blt->t;
    blt->kunt = sin(blt->c) * blt->t;
    
    blt->x = (int)(cos(blt->angle + blt->i) * blt->rad);
    blt->y = (int)(sin(blt->angle + blt->kunt) * blt->rad);
    
    blt->x += blt->sx;
    blt->y += blt->sy;
    
    x = blt->x/40;
    y = blt->y/40;
    
    if (x >= cmap->w || y >= cmap->h || y < 0 || x < 0) {
        free(blt);
        return 1;
    }
    
    if (cmap->layers[z].data[y][x].blocking) {\
        free(blt);
        return 1;
    }       
    
    if (cmap->layers[z].data[y][x].act) {
        cmap->layers[z].data[y][x].act->health -= 10;
        if (cmap->layers[z].data[y][x].act->health < 1) {
            destroy_actor_instance(cmap->layers[z].data[y][x].act);
            cmap->layers[z].data[y][x].act = NULL;
        }   
        free(blt);
        return 1; 
    }    
    
    return 0;
}
    
