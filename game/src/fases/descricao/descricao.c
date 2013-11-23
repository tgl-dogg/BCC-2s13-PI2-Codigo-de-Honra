#include "descricao.h"

extern ALLEGRO_FONT *font;
extern ALLEGRO_COLOR font_color;
extern ALLEGRO_BITMAP *text_pos, *original_pos;

// variaveis globais
extern ALLEGRO_DISPLAY *janela;

/* Desenha as 9 linhas de texto da posição inicial n de uma matriz tridimensional.
    Termina a execução quando o usuário der um clique na tela. */
void draw_text(char ***txt, int n, ALLEGRO_BITMAP *speaker){
    // TODO tornar a void draw_text em int draw_text e retornar erros.
    int i;
    ALLEGRO_COLOR color;
    ALLEGRO_EVENT ev;
    ALLEGRO_EVENT_QUEUE *ev_queue = NULL;

    color = al_map_rgb(0, 0, 0);

    // Desenha a imagem de quem está falando com o jogador (geralmente o tutor).
    al_draw_bitmap(speaker, 15, 15, 0);
    al_flip_display();

    // Muda o target bitmap para a área de textos.
    al_set_target_bitmap(text_pos);
    al_clear_to_color(color);
    al_flip_display();

    // Desenha as 9 linhas de texto.
    for (i = 0; i < 9; i++) {
        al_draw_text(font, font_color, 0, i*22, 0, txt[n][i]);
    }

    al_flip_display();
    // Volta o target bitmap para o original.
    al_set_target_bitmap(original_pos);

    // Cria uma fila de eventos.
    ev_queue = al_create_event_queue();
    if (!ev_queue) {
        fprintf(stderr, "Falha ao inicializar a interação de eventos!\n");
        return;
    }

    // Registra o evento esperado.
    al_register_event_source(ev_queue, al_get_mouse_event_source());
    al_register_event_source(ev_queue, al_get_display_event_source(janela));    

    while(1) {
        al_wait_for_event(ev_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            // Clique dentro da tela do jogo já é válido.
            if (evento.mouse.x >= 0 && evento.mouse.x <= 800 && evento.mouse.y >= 0 && evento.mouse.y <= 600) {
                // Fim da execução do texto.
                return; 
            } 
        }
    }
}