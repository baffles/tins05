#include "sblend.h"

void sblend_32(BITMAP *src, BITMAP *dst, int src_x, int src_y, int dst_x, int dst_y, int w, int h) {


    	int i, j;

		for (j = 0; j < h; j++) {

			unsigned long *s, *d;
			unsigned long color1, color2;
			unsigned long alpha;
	
			/* Read src line */
			
			bmp_select(dst);
			s = (unsigned long*)(src->line[src_y + j] + src_x * sizeof(long));
			d = (unsigned long*)(bmp_write_line(dst, dst_y + j) + dst_x * sizeof(long));
	    
			for (i = w; i; i--) {
				unsigned long temp1, temp2;
 
				/* Read data, 1 pixel at a time */
				color2 = *s;
				color1 = *d;
				
				// what the hell is this, Bob?
				
				/*
				if (color2 == MASK_COLOR_32) {
					s++;
					d++;
					continue;
				}
				*/
				
				alpha = ((color2 & 0xFF000000) >> 24);
				/* Mutiply by the factor */
				temp2 = color1 & 0xFF00FF;
				temp1 = (color2 & 0xFF00FF) - temp2;
				temp1 = (((temp1 * alpha) >> 8) + temp2) & 0xFF00FF;
				color1 &= 0xFF00;
				color2 &= 0xFF00;
				temp2 = ((((color2 - color1) * alpha) >> 8) + color1) & 0xFF00;

	 			/* Write the data */
				s++;
				bmp_write32((unsigned long)d, temp1 | temp2);
				d++;
			}
		}
	
	return;
}
