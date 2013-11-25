#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "desafios.h"
#include "../../geral/cards.h"
#include "../../geral/dialog.h"

// Condições.
extern char cond[500];
extern char cond_buttons[500];

extern ALLEGRO_BITMAP *select_cards_pos, *original_pos;

void click_prog_buttons(clk_flag flags, challenger_rule cr, card_pile *cp);
void click_condition_buttons(clk_flag flags, challenger_rule cr, card_pile *cp);
void click_action_buttons(clk_flag flags, challenger_rule cr, card_pile *cp);

int execute_event(int ev_type, clk_flag *flags, challenger_rule cr, card_pile *cp);

/* Cria o desafio de acordo com a regra de desafio (challenger_rule). */
int create_desafio(challenger_rule cr) {
    // Guarda o resultado da nossa operação.
    int resultado = 0;

    // cor para limpar área de cartas selecionadas
    ALLEGRO_COLOR color = al_map_rgb(0, 0, 0);

    // Cria flag para controle dos eventos de clique.
    clk_flag ev_flag = {-1, -1, -1, -1};   
    // Cria pilha de cartas.
    card_pile card_set;

    // Nova event queue para registrar os eventos desta janela.
    ALLEGRO_EVENT_QUEUE *ev_queue = NULL;

    // Evento para os novos cliques.
    ALLEGRO_EVENT ev_click;

    // Limpa a área de cartas selecionadas.
    al_set_target_bitmap(select_cards_pos);
    al_clear_to_color(color);
    al_set_target_bitmap(original_pos);

    // Desenha os botões.
    draw_undo_card();
    //draw_help_card();
    //draw_memory_card();
    draw_compile_card();

    // Desenha as cartas.
    draw_prog_cards(cr);    
    draw_conditional_cards(cr);
    draw_action_cards(cr);

    al_flip_display();

    // Inicializa a struct de set de card.
    card_pile_init(&card_set);

    // Cria uma event queue diferente da tela principal.
    ev_queue = al_create_event_queue();
    // Registra a interação com o mouse novamente.
    al_register_event_source(ev_queue, al_get_mouse_event_source());
    
    while(1) {    
        int ev_type = -1;   
        al_wait_for_event(ev_queue, &ev_click);

        // Detecta o tipo de evento.
        if (ev_click.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            // Detecta onde foi o clique do usuário e seta as flags referentes.
            ev_type = detect_click_pos(ev_click, &ev_flag, cr);

            //Executa o evento registrado na flag.
            resultado = execute_event(ev_type, &ev_flag, cr, &card_set);

            al_flip_display();  
            
            // Se o usuário clicou em compile finalizamos os eventos.
            if(ev_type == 6 && resultado != 2) {
                al_unregister_event_source(ev_queue, al_get_mouse_event_source());
                printf("Chegou no compile!\n");
                break;
            }
        }
    }

    // Destrói esta instância de eventos para não interferir nos outros eventos do jogo.
    al_destroy_event_queue(ev_queue);

    // Limpa a tela de novo
    al_set_target_bitmap(select_cards_pos);
    al_clear_to_color(color);
    al_set_target_bitmap(original_pos);
    return resultado;
}

/* Clique nas cartas de programação. */
void click_prog_buttons(clk_flag flags, challenger_rule cr, card_pile *cp) {
    // Verifica se o status está ok (== 1).
    if(flags.ev_status == 1) {
        // verifica o "nível de carta" em programação.
        // para saber se o usuário pode utilizar a posição em que clicou.
        if(flags.card_pos < cr.prog) {
            // Adiciona a carta à pilha de cartas do usuário de acordo com
            // a nossa definição de index de cartas (cartas de programação começam do 0).
            card_pull(cp, flags.card_pos + 0);            
    
            // Desenha ela na área de cartas selecionadas.
            draw_selected_card(flags.card_pos + 0, flags.card_num);  
        }
    }
}

/* Clique nas cartas de condição. */
void click_condition_buttons(clk_flag flags, challenger_rule cr, card_pile *cp) {
    int aux; 
    if(flags.ev_status == 1) {
        // verifica o "nível de carta" em programação.
        // para saber se o usuário pode utilizar a posição em que clicou.
        if(flags.card_pos < cr.cond) {
            // Define condições do if
            if (flags.card_pos == 0) {
                // Pega a condição definida pelo usuário
                aux = show_cond_dialog(cond, cond_buttons);

                // Adiciona a carta à pilha de cartas do usuário de acordo com
                // a nossa definição de index de cartas (cartas de condição começam do 1000).
                card_pull(cp, aux + 10000);

                // Desenha ela na área de cartas selecionadas.
                draw_selected_card(aux + 10000, flags.card_num);
            } else {
                // Adiciona a carta à pilha de cartas do usuário de acordo com
                // a nossa definição de index de cartas (cartas de condição começam do 1000).
                card_pull(cp, flags.card_pos + 1000);

                // Desenha ela na área de cartas selecionadas.
                draw_selected_card(flags.card_pos + 1000, flags.card_num);
            }
        }
    }
}

/* Clique nas cartas de ação. */
void click_action_buttons(clk_flag flags, challenger_rule cr, card_pile *cp) {
    if(flags.ev_status == 1){      
        // verifica o "nível de carta" em programação.
        // para saber se o usuário pode utilizar a posição em que clicou.
        if(flags.card_pos < cr.act) {
            // Adiciona a carta à pilha de cartas do usuário de acordo com
            // a nossa definição de index de cartas (cartas de ação começam do 2000).
            card_pull(cp, flags.card_pos + 2000);

            // Desenha ela na área de cartas selecionadas.
            draw_selected_card(flags.card_pos + 2000, flags.card_num);  
        }
    }
}

/* Executa o mesmo de acordo com o tipo e as flags. */
int execute_event(int ev_type, clk_flag *flags, challenger_rule cr, card_pile *cp) {
    switch(ev_type){
        /* Cartas de programação. */
        case 1:
            click_prog_buttons(*flags, cr, cp);
        break;

        /* Cartas de condição. */
        case 2:
            click_condition_buttons(*flags, cr, cp);
        break;

        /* Cartas de ação. */
        case 3:
            click_action_buttons(*flags, cr, cp);
        break;

        /* Carta de memória. */
        case 4:
            // mostrar combinações de cartas.
        break;  

        /* Carta de ajuda */
        case 5:
            // mostrar ajuda.
        break;

        /* Carta de compilar. */
        case 6:
            if (card_stack_count(*cp) > 0) {
                return validate_selection(cr.v, (*cp).v);
            } else {
                show_alert_dialog("Não é possível compilar sem cartas!");
                return 2;
            }
        break;

        /* Carta de desfazer. */
        case 7:
            // Verifica se a pilha não está vazia e dá um pop nela.
            // TODO criar sub_bitmap para área de de cartas selecionadas para limpar as seleções erradas do usuário.
            if (card_stack_count(*cp) > 0) {
                card_pop(cp);
                redraw_selected_cards(*cp);
                (*flags).card_num = (*flags).card_num - 1;
            }
        break;
    }

    return -1;
}