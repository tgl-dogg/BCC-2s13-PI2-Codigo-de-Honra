#include "fases.h"
#include "../geral/file_loader.h"

void init_images();
void destroy_images();

// Declara as variáveis globais das cartas.
ALLEGRO_BITMAP *im_prog_set[5];
ALLEGRO_BITMAP *im_cond_set[5];
ALLEGRO_BITMAP *im_act_set[5];

// Background.
ALLEGRO_BITMAP *im_bg;

// Botões.
ALLEGRO_BITMAP *im_redo;
ALLEGRO_BITMAP *im_help;
ALLEGRO_BITMAP *im_memory;
ALLEGRO_BITMAP *im_compile;

// Imagens da interação com textos  
ALLEGRO_BITMAP *tutor;
ALLEGRO_BITMAP *dialog;

// Text file
char ***text;

/* Inicialização das fases no geral.
Retorna -1 caso o usuário desista em algum ponto, ou 1 caso vença todas as fases. */
int fases_manager() {
    int text_counter, fase_result;

    // Inicializa imagens como NULL.
    init_images();

	/* Carrega na memória em partes, pegando apenas o que será utilizado em cada desafio. 
        Elimina a necessidade de telas de loading, pois o carregamento está sendo executado bem rapidamente. */
    
   	// Botões (estarão em todas as fases, então já carrega de uma vez).
    im_undo = al_load_bitmap("res/img/gen/undo.png")
 	im_help = al_load_bitmap("res/img/gen/help.png");
	im_memory = al_load_bitmap("res/img/gen/memory.png");
	im_compile = al_load_bitmap("res/img/prog/compile_symbol.png");

    // Imagens de interação com texto (também estarão em todas as fases).
    tutor = al_load_bitmap("res/img/gen/tutor.png");
    dialog = al_load_bitmap("res/img/gen/dialog.png");

	/* Fase 1 */
	// Background.
   	bg = al_load_bitmap("res/img/bg/bg_test.png");

   	// Cartas.
    im_prog_set[0] = al_load_bitmap("res/img/prog/direct_symbol.png");
    im_prog_set[1] = al_load_bitmap("res/img/prog/if_symbol.png");  

    im_cond_set[0] = al_load_bitmap("res/img/prog_condition/if_condition.png");    
    im_cond_set[1] = al_load_bitmap("res/img/prog_condition/if_else.png");

    im_act_set[0] = al_load_bitmap("res/img/act/atk.png");    
    im_act_set[1] = al_load_bitmap("res/img/act/def.png");

    // Carrega os textos da fase 1.
    text = load_file("res/text/des_file1.txt", &text_counter);

    // Repete a fase 1 enquanto usuário não vencer ou desistir;
    do {
        fase_result = fase1_init();
    } while (fase_result == 0);

    // Libera textos da fase 1.
    free_tri_matrix(text, text_counter, 9);

    if (fase_result == -1) {
        // Usuário desistiu, libera recursos das imagens.
        destroy_images();
        return -1;
    }

    /* Fase 2 */
    // Cartas.
    im_prog_set[2] = al_load_bitmap("res/img/prog/while_symbol.png");
    im_cond_set[2] = al_load_bitmap("res/img/prog_condition/while_break.png");
    im_act_set[2] = al_load_bitmap("res/img/act/atk_double.png");

    // Carrega os textos da fase 1.
    text = load_file("res/text/des_file2.txt", &text_counter);

    // Repete a fase 2 enquanto usuário não vencer ou desistir;
    do {
        fase_result = fase2_init();
    } while (fase_result == 0);

    // Libera textos da fase 2.
    free_tri_matrix(text, text_counter, 9);

    if (fase_result == -1) {
        // Usuário desistiu, libera recursos das imagens.
        destroy_images();
        return -1;
    }

    /* Fase 3 */
    // Cartas.
    im_cond_set[3] = al_load_bitmap("res/img/prog_condition/array_symbol.png");
	
    im_act_set[3] = al_load_bitmap("res/img/act/grab.png");
    im_act_set[4] = al_load_bitmap("res/img/act/array_item.png");

    // Carrega os textos da fase 3.
    text = load_file("res/text/des_file3.txt", &text_counter);

    // Repete a fase 3 enquanto usuário não vencer ou desistir;
    do {
        fase_result = fase3_init();
    } while (fase_result == 0);

    // Libera textos da fase 3.
    free_tri_matrix(text, text_counter, 9);

    if (fase_result == -1) {
        // Usuário desistiu, libera recursos das imagens.
        destroy_images();
        return -1;
    }

    // TODO fazer arena aqui?
    destroy_images();
    return 0;
}

/* Inicializa todas as imagens como NULL. Facilita e garante verificações de NULL posteriores. */
void init_images() {
    int i;

    im_bg = NULL;

    im_redo = NULL;
    im_help = NULL;
    im_memory = NULL
    im_compile = NULL;

    tutor = NULL;
    dialog = NULL;

    for (i = 0; i < 5; i++) {
        im_prog_set[i] = NULL;
        im_cond_set[i] = NULL;
        im_act_set[i] = NULL;
    }
}

/* Libera os recursos utilizados por todas as imagens. */
void destroy_images() {
    int i;

    // Documentação do allegro garante que nada acontecerá caso os ponteiros sejam NULL.
    al_destroy_bitmap(im_bg);

    al_destroy_bitmap(im_redo);
    al_destroy_bitmap(im_help);
    al_destroy_bitmap(im_memory);
    al_destroy_bitmap(im_compile);

    al_destroy_bitmap(tutor);
    al_destroy_bitmap(dialog);

    for (i = 0; i < 5; i++) {
        al_destroy_bitmap(im_prog_set[i]);
        al_destroy_bitmap(im_cond_set[i]);
        al_destroy_bitmap(im_act_set[i]);
    }
}