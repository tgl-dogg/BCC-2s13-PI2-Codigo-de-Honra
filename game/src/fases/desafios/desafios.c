#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "desafios.h"
#include "../../geral/cards.h"



void click_prog_buttons(clk_flag flags);
void click_condition_buttons(clk_flag flags);
void click_action_buttons(clk_flag flags);

int detect_click_pos(ALLEGRO_EVENT ev, clk_flag *flags);
void execute_event(int ev_type, clk_flag flags);


// Arrays globais da área de seleção do usuário
static int img_size = 6;
static ALLEGRO_BITMAP *im_prog_set[6];
static ALLEGRO_BITMAP *im_cond_set[6];
static ALLEGRO_BITMAP *im_act_set[6];

// Variável externa
extern ALLEGRO_DISPLAY *janela;

int create_desafio(){
    // Nova event queue para registrar os eventos desta janela
    ALLEGRO_EVENT_QUEUE *ev_queue = NULL;

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
	
    im_prog_set[0] = al_load_bitmap("res/img/prog/direct_symbol.png");
    im_prog_set[1] = al_load_bitmap("res/img/prog/if_symbol.png");    
    im_prog_set[2] = al_load_bitmap("res/img/prog/while_symbol.png");
    im_prog_set[3] = al_load_bitmap("res/img/prog/array_symbol.png");
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

    // Cria uma event queue diferente da tela principal
	ev_queue = al_create_event_queue();
	// Registra a interação com o mouse novamente
	al_register_event_source(ev_queue, al_get_mouse_event_source());
    // Cria flag para controle dos eventos de clique
    clk_flag ev_flag = {-1, -1, -1, -1};   
    
    while(1){    
    	int ev_type = -1;	
    	al_wait_for_event(ev_queue, &ev_click);

        if (ev_click.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
        	// detecta o tipo de evento e seta as flags
        	ev_type = detect_click_pos(ev_click, &ev_flag);
        	//executa o evento especificado
        	execute_event(ev_type, ev_flag);
        	
        	// Se o usuário clicou em compile ou reset, por enquanto finalizamos os eventos.
        	if(ev_type == 6 || ev_type == 7){
        		al_unregister_event_source(ev_queue, al_get_mouse_event_source());
        		break;
        	}
        }
    }

    // Destrói esta instância de eventos para não interferir nos outros eventos do jogo
    al_destroy_event_queue(ev_queue);
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