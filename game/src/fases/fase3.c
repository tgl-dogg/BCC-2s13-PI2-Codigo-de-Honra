#include "fases.h"

// Variável externa de janela.
extern ALLEGRO_DISPLAY *janela;

// Background.
extern ALLEGRO_BITMAP *im_bg;

// Monstros.
extern ALLEGRO_BITMAP *im_boss;
extern ALLEGRO_BITMAP *im_mon_set[5];

// Tutor.
extern ALLEGRO_BITMAP *im_tutor;

// Text file.
extern char ***text;

// Condições.
extern char cond[500];
extern char cond_buttons[500];

void desafio_gosma1(int v[]);
void desafio_gosma2(int v[]);
void desafio_fantasma(int v[]);

int fase3_init() {
	// Guarda qual texto do file queremos utilizar;
	int text_pos, resultado_desafio;
	// Aloca os desafios desta fase.
	int v[15];

	// Cor para limpar a tela
	ALLEGRO_COLOR clean_color;

	// Imagem de quem está falando com o jogador;
	ALLEGRO_BITMAP *speaker;

	// Struct que controla o desafio
	challenger_rule cr;	
	// Inicializa a struct dos desafios
	cr_init(&cr);
	
	// Define a cor para limpar a tela (preto), limpa e adiciona o background.
 	clean_color = al_map_rgb(0, 0, 0);
    al_clear_to_color(clean_color);
    al_draw_bitmap(im_bg, 0, 0, 0);

    // Define as cartas a serem desenhadas.
    cr.prog = 3;
    cr.cond = 3;
    cr.act = 3;

    draw_prog_cards(cr);    
    draw_conditional_cards(cr);
    draw_action_cards(cr);
    al_flip_display();

	text_pos = 0;
    speaker = im_tutor;
    draw_text(text, text_pos, speaker);

    cr.prog = 3;
    cr.cond = 4;
    cr.act = 3;

    draw_prog_cards(cr);    
    draw_conditional_cards(cr);
    draw_action_cards(cr);
    al_flip_display();

	text_pos = 1;
    draw_text(text, text_pos, speaker);

	text_pos = 2;
    draw_text(text, text_pos, speaker);

    cr.prog = 3;
    cr.cond = 4;
    cr.act = 5;

    draw_prog_cards(cr);    
    draw_conditional_cards(cr);
    draw_action_cards(cr);
    al_flip_display();

	text_pos = 3;
    draw_text(text, text_pos, speaker);

	text_pos = 4;
    draw_text(text, text_pos, speaker);

	text_pos = 5;
    draw_text(text, text_pos, speaker);

    // Desafio da gosminha 1.
	text_pos = 6;
    speaker = im_mon_set[4];
    draw_text(text, text_pos, speaker);

    desafio_gosma1(v);
    transferir_desafio(&cr, v);
    resultado_desafio = create_desafio(cr);

    if (resultado_desafio <= 0) {
        resultado_desafio = show_try_again_dialog("Desafio da Gosma");
        if (resultado_desafio == 1) {
            return 0;
        } else {
            return resultado_desafio;
        }
    }

	text_pos = 7;
    speaker = im_tutor;
    draw_text(text, text_pos, speaker);

    // Desafio da gosminha 2.
	text_pos = 8;
    speaker = im_mon_set[4];
    draw_text(text, text_pos, speaker);

    desafio_gosma2(v);
    transferir_desafio(&cr, v);
    resultado_desafio = create_desafio(cr);

    if (resultado_desafio <= 0) {
        resultado_desafio = show_try_again_dialog("Desafio das Gosmas");
        if (resultado_desafio == 1) {
            return 0;
        } else {
            return resultado_desafio;
        }
    }

	text_pos = 9;
    speaker = im_tutor;
    draw_text(text, text_pos, speaker);

	text_pos = 10;
    draw_text(text, text_pos, speaker);

	text_pos = 11;
    draw_text(text, text_pos, speaker);

    // Desafio do fantasma
	text_pos = 12;
    speaker = im_boss;
    draw_text(text, text_pos, speaker);

    desafio_fantasma(v);
    transferir_desafio(&cr, v);
    resultado_desafio = create_desafio(cr);

    if (resultado_desafio <= 0) {
        resultado_desafio = show_try_again_dialog("Desafio do Fantasma");
        if (resultado_desafio == 1) {
            return 0;
        } else {
            return resultado_desafio;
        }
    }

	text_pos = 13;
    speaker = im_tutor;
    draw_text(text, text_pos, speaker);

	return 1;
}

void desafio_gosma1(int v[]) {
	inicializa_vetor(v);

	v[0] = DIRECT;
	v[1] = ATK;
	v[2] = WHILE;
	v[3] = ARRAY;
	v[4] = ARRAY_GRAB;
	v[5] = WHILE_BREAK;
}

void desafio_gosma2(int v[]) {
	inicializa_vetor(v);

	v[0] = DIRECT;
	v[1] = ATK_DOUBLE;
	v[2] = WHILE;
	v[3] = ARRAY;
	v[4] = ARRAY_GRAB;
	v[5] = WHILE_BREAK;
}

void desafio_fantasma(int v[]) {
	inicializa_vetor(v);
    transferir_condicao(cond, "I- Enquanto o fantasma estiver vivo;\nII- Enquanto o fantasma for imaterial;\nIII- Enquanto o fantasma for assustador;\nIV- Enquanto o fantasma estiver vulnerável;\nV- Enquanto você não tiver medo de fantasma.");
    transferir_condicao(cond_buttons, "Condição I|Condição II|Condição III|Condição IV|Condição V");

	v[0] = WHILE;
	v[1] = ARRAY;
	v[2] = ARRAY_USE;
	v[3] = WHILE_BREAK;
	v[4] = WHILE;
	v[5] = 10000+4; //alguma condição "Enquanto o fantasma estiver vulnerável"
	v[6] = ATK;
	v[7] = WHILE_BREAK;
}