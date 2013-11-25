#include "fases.h"

// Variável externa de janela.
extern ALLEGRO_DISPLAY *janela;

// Background.
extern ALLEGRO_BITMAP *im_bg;

// Tutor
extern ALLEGRO_BITMAP *im_tutor;

// Text file.
extern char ***text;

// Condições.
extern char cond[500];
extern char cond_buttons[500];

void intro() {
    // Guarda qual texto do file queremos utilizar;
    int text_pos;

    // Cor para limpar a tela
    ALLEGRO_COLOR clean_color;
    
    // Define a cor para limpar a tela (preto), limpa e adiciona o background.
    clean_color = al_map_rgb(0, 0, 0);
    al_clear_to_color(clean_color);
    al_draw_bitmap(im_bg, 0, 0, 0);
    al_flip_display();

    // Pequena introdução do jogo.
    text_pos = 0;
    draw_text(text, text_pos, im_tutor);

    text_pos = 1;
    draw_text(text, text_pos, im_tutor);

    text_pos = 2;
    draw_text(text, text_pos, im_tutor);
}