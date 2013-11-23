#include "fases.h"
#include "descricao/descricao.h"

// Pega a variável global da janela.
extern ALLEGRO_DISPLAY *janela;

// Declara as variáveis globais das cartas.
ALLEGRO_BITMAP *im_prog_set[3];
ALLEGRO_BITMAP *im_cond_set[4];
ALLEGRO_BITMAP *im_act_set[5];

// Background.
ALLEGRO_BITMAP *im_bg;

// Botões.
ALLEGRO_BITMAP *im_help;
ALLEGRO_BITMAP *im_memory;
ALLEGRO_BITMAP *im_compile;  

/* Inicialização das fases no geral. */
void fases_init() {
	// Carrega na memória em partes, pegando apenas o que será utilizado em cada desafio.
    
   	// Botões (estarão em todas as fases, então já carrega de uma vez)
 	im_help = al_load_bitmap("res/img/gen/help.png");
	im_memory = al_load_bitmap("res/img/gen/memory.png");
	im_compile = al_load_bitmap("res/img/prog/compile_symbol.png");

	/* Fase 1 */
	// Background
   	bg = al_load_bitmap("res/img/bg/bg_test.png");

   	// Cartas
    im_prog_set[0] = al_load_bitmap("res/img/prog/direct_symbol.png");
    im_prog_set[1] = al_load_bitmap("res/img/prog/if_symbol.png");  

    im_cond_set[0] = al_load_bitmap("res/img/prog_condition/if_condition.png");    
    im_cond_set[1] = al_load_bitmap("res/img/prog_condition/if_else.png");

    im_act_set[0] = al_load_bitmap("res/img/act/atk.png");    
    im_act_set[1] = al_load_bitmap("res/img/act/def.png");

    // File
    // TODO load txt
    load_description_f1(janela);
    fase1_init();

    /* Fase 2 */
    im_prog_set[2] = al_load_bitmap("res/img/prog/while_symbol.png");

    im_cond_set[2] = al_load_bitmap("res/img/prog_condition/while_break.png");

    im_act_set[2] = al_load_bitmap("res/img/act/atk_double.png");

    // TODO load txt
    // carrega fase 2
    fase2_init();

    /* Fase 3 */
    im_cond_set[3] = al_load_bitmap("res/img/prog_condition/array_symbol.png");
	
    im_act_set[3] = al_load_bitmap("res/img/act/grab.png");
    im_act_set[4] = al_load_bitmap("res/img/act/array_item.png");

    // TODO load txt.
    fase3_init();
}