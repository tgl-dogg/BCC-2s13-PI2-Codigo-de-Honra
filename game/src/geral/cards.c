#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "cards.h"

// Posição e tamanho da área "programação"
#define PROG_X 47
#define PROG_Y 390
#define PROG_W 134
#define PROG_H 204

// Posição e tamanho da área "condição"
#define COND_X 228
#define COND_Y 390
#define COND_W 134
#define COND_H 204

// Posição e tamanho da área "ações"
#define ACT_X 395
#define ACT_Y 390
#define ACT_W 134
#define ACT_H 204

// Posição e tamanho do botão memória
#define MEM_X 608
#define MEM_Y 372
#define MEM_W 64
#define MEM_H 64

// Posição e tamanho do botão help
#define HELP_X 678
#define HELP_Y 372
#define HELP_W 64
#define HELP_H 64

// Posição e tamanho do botão compilar
#define COMP_X 610
#define COMP_Y 442
#define COMP_W 128
#define COMP_H 128

// Posição e tamanho do botão reset
#define RES_X 20
#define RES_Y 230
#define RES_W 150
#define RES_H 210

// Posição e tamanho para área de "cartas selecionadas"
#define SLCT_X 570
#define SLCT_Y 10
#define SLCT_W 210
#define SLCT_H 350

// Espaçamento entre os botões
#define BTN_MARGIN 70

void draw_cards(ALLEGRO_BITMAP *img[], int n, int x, int y){
	int i = 0;
	int start_x = x;
	int start_y = y;
	int lim_x = x+128;
	int lim_y = y+172;

	if(n >= 15){
		return;
	}

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

// Verifica se o clique do evento foi dentro das posições especificadas
int check_bounds(ALLEGRO_EVENT ev, int left, int top, int right, int bottom){
	int x = ev.mouse.x;
	int y = ev.mouse.y;
	
	if(x >= left && x <= right && y >= top && y <= bottom){
		return 1;
	} else {
		return 0;
	}
}

// Verifica se o clique foi nas cartas (prog, cond, action) e valida o evento
int check_cards_bounds(ALLEGRO_EVENT ev, int left, int top, int right, int bottom, clk_flag *flags){
	int i = 0;
	int aux = top;

	for(i; i < 3; i++){
		top = (i * BTN_MARGIN) + aux;

		// Clique na primeira coluna
		if(check_bounds(ev, left, top, left+64, top+64) == 1){
			// Valida o evento
			(*flags).ev_status = 1;	
			// Posição da carta na matriz
			(*flags).card_pos = (2*i);
			// Número onde deve ser desenhada a carta na área de cartas selecionadas
			(*flags).card_num = (*flags).card_num + 1;	
			return 1;
		}
		// Clique na segunda coluna
		else if (check_bounds(ev, right-64, top, right, top+64) == 1){
			(*flags).ev_status = 1;
			(*flags).card_pos = (2*i) + 1;
			(*flags).card_num = (*flags).card_num + 1;
			return 1;
		}
	}

	(*flags).ev_status = -1;
	return 0;
}

/*
 Detecta a posição do clique do usuário, retorna 0 caso não seja válido,
 retorna 1 para prog, 2 para condition, 3 para action
 4 para memory, 5 para help, 6 para compile, 7 para reset.
*/
int detect_click_pos(ALLEGRO_EVENT ev, clk_flag *flags){
	if(check_cards_bounds(ev, PROG_X, PROG_Y, PROG_X+PROG_W, PROG_Y+PROG_H, flags) == 1){
		return 1;
	} else if (check_cards_bounds(ev, COND_X, COND_Y, COND_X+COND_W, COND_Y+COND_H, flags) == 1){
		return 2;
	} else if (check_cards_bounds(ev, ACT_X, ACT_Y, ACT_X+ACT_W, ACT_Y+ACT_H, flags) == 1){
		return 3;
	} else if (check_bounds(ev, MEM_X, MEM_Y, MEM_X+MEM_W, MEM_Y+MEM_H) == 1){
		return 4;
	} else if (check_bounds(ev, HELP_X, HELP_Y, HELP_X+HELP_W, HELP_Y+HELP_H) == 1){
		return 5;
	} else if (check_bounds(ev, COMP_X, COMP_Y, COMP_X+COMP_W, COMP_Y+COMP_H) == 1){
		return 6;
	} else if (check_bounds(ev, RES_X, RES_Y, RES_X+RES_W, RES_Y+RES_H) == 1){
		return 7;
	} else {
		return 0;
	}

	return 0;
}

/*
Verifica se os dois vetores são iguais. Se iguais, retorna -1.
Se diferentes, retorna o index onde começa a diferença entre eles.
*/
int validate_selection(int v1[], int v2[]) {
	int i;
	int index = -1;

	for (i = 0; i < 15; i++) {
		if (v1[i] != v2[i]) {
			index = i;
			break;
		}
	}

	return i;
}