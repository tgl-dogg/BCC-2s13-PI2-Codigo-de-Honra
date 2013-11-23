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

    // TODO definir textos a serem mostrados, a regra do desafio, o speaker, etc...
    cr.prog = 2;
    cr.cond = 2;
    cr.act = 2;

    speaker = tutor;
    speaker = im_mon_set[0];
    speaker = im_mon_set[1];
    speaker = im_mon_set[2];
    speaker = boss;

	// texto texto texto
	text_pos = 0;
	draw_text(text, text_pos, speaker);

    // Cria desafio de acordo com as regras especificadas.
    create_desafio(cr);
    al_flip_display();

    return 0;
}