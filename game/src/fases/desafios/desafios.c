#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "../../geral/cards.h"

// Flag para os cliques
typedef struct {
				// status do evento
				int ev_status;
				// posição da carta a ser desenhada
				int card_pos;
				// contador do número de cartas já desenhadas
				int card_num;
              } clk_flag;  

// Arrays globais da área de seleção do usuário
static int img_size = 6;
static ALLEGRO_BITMAP *im_prog_set[6];
static ALLEGRO_BITMAP *im_cond_set[6];
static ALLEGRO_BITMAP *im_act_set[6];

//extern evento;
//extern interacao;
//extern ALLEGRO_DISPLAY *display;

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

// Verifica se o clique foi dentro das posições dos botões
int check_button_bounds(ALLEGRO_EVENT ev, int left, int top, int right, int bottom, clk_flag *flags){
	int i = 0;
	int aux = top;

	for(i; i < 3; i++){
		top = (i * BTN_MARGIN) + aux;

		if(check_bounds(ev, left, top, left+64, top+64) == 1){
			(*flags).card_pos = (2*i);
			(*flags).card_num = (*flags).card_num + 1;
			return 1;
		} else if (check_bounds(ev, right-64, top, right, top+64) == 1){
			(*flags).card_pos = (2*i) + 1;
			(*flags).card_num = (*flags).card_num + 1;
			return 1;
		}
	}

	(*flags).ev_status = -1;
	return 0;
}

// Clique nas cartas de programação
void click_prog_buttons(clk_flag flags){
	if(flags.ev_status == 1){
		draw_selected_cards(im_prog_set[flags.card_pos], flags.card_num);
	}
}

// Clique nas cartas de condição
void click_condition_buttons(clk_flag flags){
	if(flags.ev_status == 1){
		draw_selected_cards(im_cond_set[flags.card_pos], flags.card_num);
	}
}

// Clique nas cartas de ação
void click_action_buttons(clk_flag flags){
	if(flags.ev_status == 1){
		draw_selected_cards(im_act_set[flags.card_pos], flags.card_num);
	}
}

// depois de detectar o evento, executa o mesmo de acordo com o tipo e as flags
void execute_event(int ev_type, clk_flag flags){
	switch(ev_type){
		case 1:
			click_prog_buttons(flags);
			break;

		case 2:
			click_condition_buttons(flags);
			break;

		case 3:
			click_action_buttons(flags);
			break;

		case 4:
			break;	

		case 5:
			break;

		case 6:
			break;

		case 7:
			break;
	}

	al_flip_display();
}

/*
 Detecta a posição do clique do usuário, returna -1 em erro, 0 em click no "nada", 1 para prog, 
 2 para condition, 3 para action 4 para memory, 5 para help, 6 para compile, 7 para reset.
*/
int detect_click_pos(ALLEGRO_EVENT ev, clk_flag *flags){
	if(check_button_bounds(ev, PROG_X, PROG_Y, PROG_X+PROG_W, PROG_Y+PROG_H, flags) == 1){
		(*flags).ev_status = 1;
		return 1;
	} else if (check_button_bounds(ev, COND_X, COND_Y, COND_X+COND_W, COND_Y+COND_H, flags) == 1){
		(*flags).ev_status = 1;
		return 2;
	} else if (check_button_bounds(ev, ACT_X, ACT_Y, ACT_X+ACT_W, ACT_Y+ACT_H, flags) == 1){
		(*flags).ev_status = 1;
		return 3;
	} else if (check_bounds(ev, MEM_X, MEM_Y, MEM_X+MEM_W, MEM_Y+MEM_H) == 1){
		(*flags).ev_status = 0;
		return 4;
	} else if (check_bounds(ev, HELP_X, HELP_Y, HELP_X+HELP_W, HELP_Y+HELP_H) == 1){
		(*flags).ev_status = 0;
		return 5;
	} else if (check_bounds(ev, COMP_X, COMP_Y, COMP_X+COMP_W, COMP_Y+COMP_H) == 1){
		(*flags).ev_status = 0;
		return 6;
	} else if (check_bounds(ev, RES_X, RES_Y, RES_X+RES_W, RES_Y+RES_H) == 1){
		(*flags).ev_status = 0;
		return 7;
	} else {
		(*flags).ev_status = 0;
		return 0;
	}

	return -1;
}

void desafio1_fase1(ALLEGRO_DISPLAY *janela, ALLEGRO_EVENT_QUEUE *interacao){
   	// Evento para os novos cliques
	ALLEGRO_EVENT ev_click;

	// Background
	ALLEGRO_BITMAP *bg = NULL;

	// Botões
	ALLEGRO_BITMAP *im_help = NULL;
	ALLEGRO_BITMAP *im_memory = NULL;
	ALLEGRO_BITMAP *im_compile = NULL;  
   	
   	bg = al_load_bitmap("res/img/bg/battle_layout.png");
    al_draw_bitmap(bg, 0, 0, 0);

 	im_help = al_load_bitmap("res/img/gen/help.png");
	im_memory = al_load_bitmap("res/img/gen/memory.png");
	im_compile = al_load_bitmap("res/img/prog/compile_symbol.png");
	
    im_prog_set[0] = al_load_bitmap("res/img/prog/if_symbol.png");    
    im_prog_set[1] = al_load_bitmap("res/img/prog/while_symbol.png");
    im_prog_set[2] = al_load_bitmap("res/img/prog/array_symbol.png");
    im_prog_set[3] = al_load_bitmap("res/img/prog/direct_symbol.png");
    im_prog_set[4] = im_prog_set[5] = NULL;

    im_cond_set[0] = al_load_bitmap("res/img/prog_condition/if_condition.png");    
    im_cond_set[1] = al_load_bitmap("res/img/prog_condition/if_elseif.png");
    im_cond_set[2] = al_load_bitmap("res/img/prog_condition/if_else.png");
    im_cond_set[3] = al_load_bitmap("res/img/prog_condition/while_break.png");
    im_cond_set[4] = im_cond_set[5] = NULL;
	
    im_act_set[0] = al_load_bitmap("res/img/act/atk.png");    
    im_act_set[1] = al_load_bitmap("res/img/act/atk_double.png");
    im_act_set[2] = al_load_bitmap("res/img/act/def.png");
    im_act_set[3] = al_load_bitmap("res/img/act/def_magic.png");
    im_act_set[4] = al_load_bitmap("res/img/act/def_projectile.png");
    im_act_set[5] = NULL;


	// Desenha as cartas na tela
    draw_help_card(im_help);
    draw_memory_card(im_memory);
    draw_compile_card(im_compile);

    draw_prog_cards(im_prog_set, img_size);    
    draw_conditional_cards(im_cond_set, img_size);
    draw_action_cards(im_act_set, img_size);

    al_flip_display();
	
	// Registra a interação com o mouse novamente
	al_register_event_source(interacao, al_get_mouse_event_source());
    // Cria flag para controle dos eventos de clique
    clk_flag ev_flag = {-1, -1, -1};   
    
    while(1){    
    	int ev_type = -1;	
    	al_wait_for_event(interacao, &ev_click);

        if (ev_click.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
        	// detecta o tipo de evento e seta as flags
        	ev_type = detect_click_pos(ev_click, &ev_flag);
        	//executa o evento especificado
        	execute_event(ev_type, ev_flag);
        	
        	// Se o usuário clicou em compile ou reset, por enquanto finalizamos os eventos.
        	if(ev_type == 6 || ev_type == 7){
        		al_unregister_event_source(interacao, al_get_mouse_event_source());
        		break;
        	}
        }
    }
}