#include "fases.h"
#include "../geral/file_loader.h"

void init_images();
void destroy_images();

int init_font();
void destroy_font();

int init_text_bitmap();
void destroy_text_bitmap();

void free_resources();

// Cartas.
ALLEGRO_BITMAP *im_prog_set[5];
ALLEGRO_BITMAP *im_cond_set[5];
ALLEGRO_BITMAP *im_act_set[5];

// Monstros.
ALLEGRO_BITMAP *im_mon_set[5];
ALLEGRO_BITMAP *im_boss;

// Background.
ALLEGRO_BITMAP *im_bg;

// Botões.
ALLEGRO_BITMAP *im_undo;
ALLEGRO_BITMAP *im_help;
ALLEGRO_BITMAP *im_memory;
ALLEGRO_BITMAP *im_compile;

// Tutor.
ALLEGRO_BITMAP *im_tutor;

// Texto.
ALLEGRO_FONT *font;
ALLEGRO_COLOR font_color;
ALLEGRO_BITMAP *text_pos, *original_pos;

// Text file
char ***text;

/*  Inicialização das fases no geral.
    Retorna -1 caso dê erro em algum ponto, 
    0 caso o usuário desista ou
    1 caso vença todas as fases. */
int fases_manager() {
    int text_counter, fase_result, check;

    // Inicializa imagens como NULL.
    init_images();

    // Inicializa a fonte padrão para escrever textos nas fases.
    check = init_font();
    if (check == -1) {
        return -1;
    }

    // Inicializa bitmaps para escrever textos na tela.
    check = init_text_bitmap();
    if (check == -1) {
        return -1;
    }

	/* Carrega na memória em partes, pegando apenas o que será utilizado em cada desafio. 
        Elimina a necessidade de telas de loading, pois o carregamento está sendo executado bem rapidamente. */
    
   	// Botões (estarão em todas as fases, então já carrega de uma vez).
    im_undo = al_load_bitmap("res/img/gen/undo.png")
 	im_help = al_load_bitmap("res/img/gen/help.png");
	im_memory = al_load_bitmap("res/img/gen/memory.png");
	im_compile = al_load_bitmap("res/img/prog/compile_symbol.png");

    // Imagens de interação com texto (também estarão em todas as fases).
    im_tutor = al_load_bitmap("res/img/gen/tutor.png");

	/* Fase 1 */
	// Background.
    // TODO adicionar background
   	im_bg = al_load_bitmap("res/img/bg/bg_test.png");

   	// Cartas.
    im_prog_set[0] = al_load_bitmap("res/img/prog/direct_symbol.png");
    im_prog_set[1] = al_load_bitmap("res/img/prog/if_symbol.png");  

    im_cond_set[0] = al_load_bitmap("res/img/prog_condition/if_condition.png");    
    im_cond_set[1] = al_load_bitmap("res/img/prog_condition/if_else.png");

    im_act_set[0] = al_load_bitmap("res/img/act/atk.png");    
    im_act_set[1] = al_load_bitmap("res/img/act/def.png");

    // Monstros.
    im_mon_set[0] = al_load_bitmap("res/img/mon/wolf.png");
    im_mon_set[1] = al_load_bitmap("res/img/mon/snake.png");
    im_mon_set[2] = al_load_bitmap("res/img/mon/salamander.png");

    // Carrega os textos da fase 1.
    text = load_file("res/text/des_file1.txt", &text_counter);

    // Repete a fase 1 enquanto usuário não vencer (1), desistir (0) ou dar erro (-1);
    do {
        fase_result = fase1_init();
    } while (fase_result == 2);

    // Libera textos da fase 1.
    free_tri_matrix(text, text_counter, 9);

    if (fase_result == -1 || fase_result == 0) {
        // Usuário desistiu ou houve algum erro, libera recursos e volta para tela inicial.
        free_resources();
        return fase_result;
    }

    /* Fase 2 */
    // Background.
    // TODO adicionar background
    im_bg = al_load_bitmap("res/img/bg/bg_test.png");

    // Cartas.
    im_prog_set[2] = al_load_bitmap("res/img/prog/while_symbol.png");
    im_cond_set[2] = al_load_bitmap("res/img/prog_condition/while_break.png");
    im_act_set[2] = al_load_bitmap("res/img/act/atk_double.png");

    // Monstros.
    im_mon_set[3] = al_load_bitmap("res/img/mon/sea_serpent.png");

    // Carrega os textos da fase 1.
    text = load_file("res/text/des_file2.txt", &text_counter);

    // Repete a fase 2 enquanto usuário não vencer (1), desistir (0) ou dar erro (-1);
    do {
        fase_result = fase2_init();
    } while (fase_result == 0);

    // Libera textos da fase 2.
    free_tri_matrix(text, text_counter, 9);

    if (fase_result == -1 || fase_result == 0) {
        // Usuário desistiu ou houve algum erro, libera recursos e volta para tela inicial.
        free_resources();
        return fase_result;
    }

    /* Fase 3 */
    // Background.
    // TODO adicionar background
    im_bg = al_load_bitmap("res/img/bg/bg_test.png");
    
    // Cartas.
    im_cond_set[3] = al_load_bitmap("res/img/prog_condition/array_symbol.png");
	
    im_act_set[3] = al_load_bitmap("res/img/act/grab.png");
    im_act_set[4] = al_load_bitmap("res/img/act/array_item.png");

    // Monstros.
    im_mon_set[3] = al_load_bitmap("res/img/mon/mini_ghost.png");

    // Carrega os textos da fase 3.
    text = load_file("res/text/des_file3.txt", &text_counter);

    // Repete a fase 3 enquanto usuário não vencer (1), desistir (0) ou dar erro (-1);
    do {
        fase_result = fase3_init();
    } while (fase_result == 0);

    // Libera textos da fase 3.
    free_tri_matrix(text, text_counter, 9);

    if (fase_result == -1 || fase_result == 0) {
        // Usuário desistiu ou houve algum erro, libera recursos e volta para tela inicial.
        free_resources();
        return fase_result;
    }

    // TODO fazer arena aqui?
    free_resources();
    return 1;
}

/* Inicializa todas as imagens como NULL. Facilita e garante verificações de NULL posteriores. */
void init_images() {
    int i;

    im_bg = NULL;

    im_undo = NULL;
    im_help = NULL;
    im_memory = NULL
    im_compile = NULL;

    im_tutor = NULL;
    im_boss = NULL;

    for (i = 0; i < 5; i++) {
        im_prog_set[i] = NULL;
        im_cond_set[i] = NULL;
        im_act_set[i] = NULL;

        im_mon_set[i] = NULL;
    }
}

/* Libera os recursos utilizados por todas as imagens. */
void destroy_images() {
    int i;

    // Documentação do allegro garante que nada acontecerá caso os ponteiros sejam NULL.
    al_destroy_bitmap(im_bg);

    al_destroy_bitmap(im_undo);
    al_destroy_bitmap(im_help);
    al_destroy_bitmap(im_memory);
    al_destroy_bitmap(im_compile);

    al_destroy_bitmap(im_tutor);
    al_destroy_bitmap(im_boss);

    for (i = 0; i < 5; i++) {
        al_destroy_bitmap(im_prog_set[i]);
        al_destroy_bitmap(im_cond_set[i]);
        al_destroy_bitmap(im_act_set[i]);

        al_destroy_bitmap(im_mon_set[i]);
    }
}

int init_font() {
    // Atribui a cor padrão para textos de fase.
    font_color = al_map_rgb(255, 255, 255);
    
    // Carrega a fonte padrão para textos de fase.
    font = al_load_ttf_font("res/font/architectsdaughter.ttf", 20, 0);
    
    if (!font) {
        fprintf(stderr, "Falha ao carregar font!\n");
        return -1;
    }

    return 0;
}

void destroy_font() {
    al_destroy_font(font);
}

int init_text_bitmap() {
    // Salva o bitmap original.
    original_pos = al_get_target_bitmap();

    // Cria um sub_bitmap para desenhar os textos.
    text_pos = al_create_sub_bitmap(al_get_backbuffer(janela), 150, 50, 350, 210);

    if (text_pos == NULL || original_pos == NULL) {
        fprintf(stderr, "Falha ao criar os subs bitmaps!\n");
        return -1;
    }

    return 0;
}

void destroy_text_bitmap() {
    al_destroy_bitmap(post_txt);
    al_destroy_bitmap(original_pos);
}

/* Chama as outras funções de liberação dos recursos alocados. */
void free_resources() {
    destroy_font();
    destroy_images();
    destroy_text_bitmap();
}