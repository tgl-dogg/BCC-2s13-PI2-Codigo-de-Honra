#include "fases.h"

void desafio_lobo(int v[]);
void desafio_cobra(int v[]);
void desafio_salamandra(int v[]);
void desafio_minotauro(int v[]);

// Variável externa de janela.
extern ALLEGRO_DISPLAY *janela;

// Background.
extern ALLEGRO_BITMAP *im_bg;

// Monstros.
extern ALLEGRO_BITMAP *im_boss;
extern ALLEGRO_BITMAP *im_mon_set[5];

// Tutor
extern ALLEGRO_BITMAP *im_tutor;

// Text file.
extern char ***text;

// Condições.
extern char *cond;
extern char *cond_buttons;

int fase1_init() {
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
	
	// Define a cor para limpar a tela (preto) e limpa.
 	clean_color = al_map_rgb(0, 0, 0);
    al_clear_to_color(clean_color);

    // Desenha o background.
    al_draw_bitmap(im_bg, 0, 0, 0);

    // Define as cartas a serem desenhadas.
    cr.prog = 1;
    cr.cond = 0;
    cr.act = 1;

    draw_prog_cards(cr);    
    draw_conditional_cards(cr);
    draw_action_cards(cr);

    // Texto de introdução sobre as primeiras cartas
    speaker = im_tutor;
	text_pos = 0;
    draw_text(text, text_pos, speaker);

    // Texto de explicação de como usar as cartas
	text_pos = 1;
    draw_text(text, text_pos, speaker);

    // Primeiro desafio
    text_pos = 2;
    speaker = im_mon_set[0];
    draw_text(text, text_pos, speaker);

    desafio_lobo(v);
    transferir_desafio(&cr, v);
    resultado_desafio = create_desafio(cr);

    if (resultado_desafio < 0) {
        return show_try_again_dialog("Desafio do Lobo");
    }

    cr.prog = 2;
    cr.cond = 0;
    cr.act = 1;

    draw_prog_cards(cr);    
    draw_conditional_cards(cr);
    draw_action_cards(cr);

    text_pos = 3;
    speaker = im_tutor;
    draw_text(text, text_pos, speaker);

    text_pos = 4;
    draw_text(text, text_pos, speaker);

    cr.prog = 2;
    cr.cond = 1;
    cr.act = 1;

    draw_prog_cards(cr);    
    draw_conditional_cards(cr);
    draw_action_cards(cr);

    text_pos = 5;
    draw_text(text, text_pos, speaker);

    // Segundo desafio 
    text_pos = 6;
    speaker = im_mon_set[1];
    draw_text(text, text_pos, speaker);

    desafio_cobra(v);
    transferir_desafio(&cr, v);
    resultado_desafio = create_desafio(cr);

    if (resultado_desafio < 0) {
        return show_try_again_dialog("Desafio da Cobra");
    }

    cr.prog = 2;
    cr.cond = 2;
    cr.act = 2;

    text_pos = 7;
    speaker = im_tutor;
    draw_text(text, text_pos, speaker);

    text_pos = 8;
    draw_text(text, text_pos, speaker);
    
    text_pos = 9;
    speaker = im_mon_set[2];
    draw_text(text, text_pos, speaker);

    desafio_salamandra(v);
    transferir_desafio(&cr, v);
    resultado_desafio = create_desafio(cr);

    if (resultado_desafio < 0) {
        return show_try_again_dialog("Desafio da Salamandra");
    }

    text_pos = 10;
    speaker = im_tutor;
    draw_text(text, text_pos, speaker);

    text_pos = 11;
    draw_text(text, text_pos, speaker);

    speaker = im_boss;
    text_pos = 12;
    draw_text(text, text_pos, speaker);
    
    desafio_minotauro(v);
    transferir_desafio(&cr, v);
    resultado_desafio = create_desafio(cr);

    if (resultado_desafio < 0) {
        return show_try_again_dialog("Desafio da Cobra");
    }

    text_pos = 13;
    speaker = im_tutor;
    draw_text(text, text_pos, speaker);


    // Retorna sucesso do jogador.
    return 1;
}

void desafio_lobo(int v[]) {
	inicializa_vetor(v);

	v[0] = DIRECT;
	v[1] = ATK;
}

void desafio_cobra(int v[]) {
	inicializa_vetor(v);

    v[0] = IF;
    v[1] = 10002; //alguma condição "se a cobra estiver destraída"
    v[2] = ATK;
}

void desafio_salamandra(int v[]) {
	inicializa_vetor(v);

    v[0] = IF;
    v[1] = 10000+2; //alguma condição "se a salamandra estiver pegando fogo"
    v[2] = DEF;
    v[3] = IF_ELSE;
    v[4] = ATK;
}

void desafio_minotauro(int v[]) {
	inicializa_vetor(v);

    v[0] = IF;
    v[1] = 10000+1; //alguma condição "se ele estiver vulnerável"
    v[2] = ATK;
    v[3] = IF_ELSE;
    v[4] = DEF;
}