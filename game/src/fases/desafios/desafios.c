#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "desafios.h"
#include "../../geral/cards.h"
#include "..//descricao/descricao.h"

void click_prog_buttons(clk_flag flags, challenger_rule cr, card_pile *cp);
void click_condition_buttons(clk_flag flags, challenger_rule cr, card_pile *cp);
void click_action_buttons(clk_flag flags, challenger_rule cr, card_pile *cp);

void execute_event(int ev_type, clk_flag flags, challenger_rule cr, card_pile *cp);

// Variável externa de janela
extern ALLEGRO_DISPLAY *janela;

// Background
extern ALLEGRO_BITMAP im_bg;

// Botões
extern ALLEGRO_BITMAP *im_redo;
extern ALLEGRO_BITMAP im_help;
extern ALLEGRO_BITMAP im_memory;
extern ALLEGRO_BITMAP im_compile;

// Cartas
extern ALLEGRO_BITMAP *im_set[12];
extern ALLEGRO_BITMAP *im_prog_set[5];
extern ALLEGRO_BITMAP *im_cond_set[5];
extern ALLEGRO_BITMAP *im_act_set[5];

/* Cria o desafio de acordo com a regra de desafio (challenger_rule). */
int create_desafio(challenger_rule cr){
    // TODO rever o challenger_rule struct

    // Guarda o resultado da nossa operação.
    int resultado = 0;

    // Cria flag para controle dos eventos de clique.
    clk_flag ev_flag = {-1, -1, -1, -1};   
    // Cria pilha de cartas.
    card_pile card_set;

    // Nova event queue para registrar os eventos desta janela.
    ALLEGRO_EVENT_QUEUE *ev_queue = NULL;

    // Evento para os novos cliques.
    ALLEGRO_EVENT ev_click;
    
    // Desenha o background.
    al_draw_bitmap(im_bg, 0, 0, 0);

    // Desenha os botões.
    draw_help_card(im_help);
    draw_memory_card(im_memory);
    draw_compile_card(im_compile);

    // Desenha as cartas.
    draw_prog_cards(im_prog_set, cr);    
    draw_conditional_cards(im_cond_set, cr);
    draw_action_cards(im_act_set, cr);

    al_flip_display();

    // Inicializa a struct de set de card.
    card_pile_init(&card_set);

    // Cria uma event queue diferente da tela principal.
    ev_queue = al_create_event_queue();
    // Registra a interação com o mouse novamente.
    al_register_event_source(ev_queue, al_get_mouse_event_source());
    
    while(1){    
        int ev_type = -1;   
        al_wait_for_event(ev_queue, &ev_click);

        // Detecta o tipo de evento.
        if (ev_click.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
            // Detecta onde foi o clique do usuário e seta as flags referentes.
            ev_type = detect_click_pos(ev_click, &ev_flag, cr);

            //Executa o evento registrado na flag.
            execute_event(ev_type, ev_flag, cr, &card_set);

            al_flip_display();  
            
            // Se o usuário clicou em compile ou reset, por enquanto finalizamos os eventos.
            if(ev_type == 6 || ev_type == 7){
                al_unregister_event_source(ev_queue, al_get_mouse_event_source());
                printf("Chegou no compile/reset!\n");
                break;
            }
        }
    }

    // Destrói esta instância de eventos para não interferir nos outros eventos do jogo.
    al_destroy_event_queue(ev_queue);
    return resultado;
}

/* Clique nas cartas de programação. */
void click_prog_buttons(clk_flag flags, challenger_rule cr, card_pile *cp){
    // Verifica se o status está ok (== 1).
    if(flags.ev_status == 1){
        // verifica o "nível de carta" em programação.
        // para saber se o usuário pode utilizar a posição em que clicou.
        if(flags.card_pos < cr.prog){
            // Adiciona a carta à pilha de cartas do usuário de acordo com
            // a nossa definição de index de cartas (cartas de programação começam do 0).
            card_pull(cp, flags.card_num + 0);            
    
            // Desenha ela na área de cartas selecionadas.
            draw_selected_cards(im_prog_set[flags.card_pos], flags.card_num);  
        }
    }
}

/* Clique nas cartas de condição. */
void click_condition_buttons(clk_flag flags, challenger_rule cr, card_pile *cp){
    if(flags.ev_status == 1){
        // verifica o "nível de carta" em programação.
        // para saber se o usuário pode utilizar a posição em que clicou.
        if(flags.card_pos < cr.cond){
            // Adiciona a carta à pilha de cartas do usuário de acordo com
            // a nossa definição de index de cartas (cartas de condição começam do 1000).
            card_pull(cp, flags.card_num + 1000);

            // Desenha ela na área de cartas selecionadas.
            draw_selected_cards(im_cond_set[flags.card_pos], flags.card_num);
        }
    }
}

/* Clique nas cartas de ação. */
void click_action_buttons(clk_flag flags, challenger_rule cr, card_pile *cp){
    if(flags.ev_status == 1){      
        // verifica o "nível de carta" em programação.
        // para saber se o usuário pode utilizar a posição em que clicou.
        if(flags.card_pos < cr.act){
            // Adiciona a carta à pilha de cartas do usuário de acordo com
            // a nossa definição de index de cartas (cartas de ação começam do 2000).
            card_pull(cp, flags.card_num + 2000);

            // Desenha ela na área de cartas selecionadas.
            draw_selected_cards(im_act_set[flags.card_pos], flags.card_num);  
        }
    }
}

/* Executa o mesmo de acordo com o tipo e as flags. */
void execute_event(int ev_type, clk_flag flags, challenger_rule cr, card_pile *cp){
    switch(ev_type){
        /* Cartas de programação. */
        case 1:
            click_prog_buttons(flags, cr, cp);
            break;

        /* Cartas de condição. */
        case 2:
            click_condition_buttons(flags, cr, cp);
            break;

        /* Cartas de ação. */
        case 3:
            click_action_buttons(flags, cr, cp);
            break;

        /* Carta de memória. */
        case 4:
            // mostrar instruções.
            break;  

        /* Carta de ajuda */
        case 5:
            // mostrar ajuda.
            break;

        /* Carta de compilar. */
        case 6:
            // TODO melhorar esta validação
            return validate_selection(cr.v, (*cp).v)
            //GGWP return -1;
            //deubosta return indice da carta errada == 0;
            break;

        /* Carta de reset. */
        case 7:
            // Verifica se a pilha não está vazia e dá um pop nela.
            // TODO criar sub_bitmap para área de de cartas selecionadas para limpar as seleções erradas do usuário.
            if (card_stack_count(cp) != 0) {
                card_pop(cp);
            }
            break;
    }
}