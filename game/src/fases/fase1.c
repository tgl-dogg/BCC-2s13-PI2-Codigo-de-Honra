#include "fases.h"
#include "desafios/desafios.h"
#include "descricao/descricao.h"
#include "../geral/cards.h"

// Variável externa de janela.
extern ALLEGRO_DISPLAY *janela;

// Background.
extern ALLEGRO_BITMAP *im_bg;

// Monstros.
extern ALLEGRO_BITMAP *im_boss;
extern ALLEGRO_BITMAP *im_mon_set[5];

// Cartas
extern ALLEGRO_BITMAP *im_prog_set[5];
extern ALLEGRO_BITMAP *im_cond_set[5];
extern ALLEGRO_BITMAP *im_act_set[5];

// Tutor
extern ALLEGRO_BITMAP *im_tutor;

// Text file.
extern char ***text;

int fase1_init() {
	// Guarda qual texto do file queremos utilizar;
	int text_pos;

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

    draw_prog_cards(im_prog_set, cr);    
    draw_conditional_cards(im_cond_set, cr);
    draw_action_cards(im_act_set, cr);

    // Texto de introdução sobre as primeiras cartas
    speaker = im_tutor;
	text_pos = 0;
    draw_text(text, text_pos, speaker);

    // Texto de explicação de como usar as cartas
	text_pos++;
    draw_text(text, text_pos, speaker);

    // Primeiro desafio
    text_pos++;
    speaker = im_mon_set[0];
    draw_text(text, text_pos, speaker);

    create_desafio(cr);

    return 0;

    text_pos++;
    speaker = im_tutor;
    // TODO definir textos a serem mostrados, a regra do desafio, o speaker, etc...
    cr.prog = 2;
    cr.cond = 2;
    cr.act = 2;
    //cr.v = 

    //speaker = tutor;
    //speaker = im_mon_set[0];
    //speaker = im_mon_set[1];
    //speaker = im_mon_set[2];
    //speaker = boss;

	// texto texto texto
	draw_text(text, text_pos, speaker);

    // Cria desafio de acordo com as regras especificadas.
    create_desafio(cr);
    al_flip_display();

    return 0;
}