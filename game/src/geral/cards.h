#ifndef _CARDS_H_
#define _CARDS_H_

// Flag para os cliques nas cartas
typedef struct {
		// evento que se espera acontecer
		int ev_esperado;
		// status do evento
		int ev_status;
		// posição da carta a ser desenhada
		int card_pos;
		// contador do número de cartas já desenhadas
		int card_num;
        } clk_flag;

void draw_compile_card(ALLEGRO_BITMAP *imagem);
void draw_memory_card(ALLEGRO_BITMAP *imagem);
void draw_help_card(ALLEGRO_BITMAP *imagem);

void draw_prog_cards(ALLEGRO_BITMAP *img[], int n);
void draw_conditional_cards(ALLEGRO_BITMAP *img[], int n);
void draw_action_cards(ALLEGRO_BITMAP *img[], int n);

void draw_selected_cards(ALLEGRO_BITMAP *imagem, int i);

int check_bounds(ALLEGRO_EVENT ev, int left, int top, int right, int bottom);
int check_cards_bounds(ALLEGRO_EVENT ev, int left, int top, int right, int bottom, clk_flag *flags);
int detect_click_pos(ALLEGRO_EVENT ev, clk_flag *flags);

#endif