#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "cards.h"

void draw_cards(ALLEGRO_BITMAP *img[], int n, int x, int y){
	if(n >= 15){
		return;
	}

	int i = 0;
	int start_x = x;
	int start_y = y;
	int lim_x = x+128;
	int lim_y = y+172;

	for(i; i < n; i++){
		if(img[i] != NULL){
			if(x > lim_x){
				x = start_x;
				y += BTN_MARGIN;
			}

			al_draw_bitmap(img[i], x, y, 0);
			x += BTN_MARGIN;
		}
	}
}

void draw_compile_card(ALLEGRO_BITMAP *imagem){
	ALLEGRO_BITMAP *img[] = { imagem };
	draw_cards(img, 1, COMP_X, COMP_Y);
}

void draw_memory_card(ALLEGRO_BITMAP *imagem){
	ALLEGRO_BITMAP *img[] = { imagem };
	draw_cards(img, 1, MEM_X, MEM_Y);
}

void draw_help_card(ALLEGRO_BITMAP *imagem){
	ALLEGRO_BITMAP *img[] = { imagem };
	draw_cards(img, 1, HELP_X, HELP_Y);
}

void draw_prog_cards(ALLEGRO_BITMAP *img[], int n){	
	draw_cards(img, n, PROG_X, PROG_Y);
}

void draw_conditional_cards(ALLEGRO_BITMAP *img[], int n){	
	draw_cards(img, n, COND_X, COND_Y);
}

void draw_action_cards(ALLEGRO_BITMAP *img[], int n){	
	draw_cards(img, n, ACT_X, ACT_Y);
}

void draw_selected_cards(ALLEGRO_BITMAP *imagem, int i){
	if(i >= 15){
		return;
	}

	ALLEGRO_BITMAP *img[] = { imagem };
	int x = SLCT_X, y = SLCT_Y;

	while((i/3) >= 1){
		i -= 3;
		y += BTN_MARGIN;
	}

	x += (BTN_MARGIN * i);
	draw_cards(img, 1, x, y);	
}