#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

// variaveis estaticas que serão usados em descrição.c
static ALLEGRO_FONT *font;
static ALLEGRO_COLOR clear, font_color;
static ALLEGRO_EVENT ev;
static ALLEGRO_EVENT_QUEUE *reg_ev = NULL;
static ALLEGRO_BITMAP *bg = NULL, *personage = NULL, *next = NULL, *pos_txt, *reset_pos;

// variaveis globais
ALLEGRO_DISPLAY *janela;
char ***txt;

// limpa a entrada
void limpa(FILE *entrada) {
    char c;
    // verifica se o que foi lido é igual a -1, neste caso, significa que acabou o file
    do {
        if(fscanf(entrada, "%c", &c) == -1) {
            break;
        }
    } while(c!='\n');
}

// matriz tridimensional dinâmica 
char ***matriz_tri(int x, int y, int z) {
    char ***M;
    int i, j;

    M = malloc(x*sizeof(char**));
    for(i=0; i<x; i++) {
        M[i] = malloc(y*sizeof(char*));
        for(j=0; j<y; j++) {
            M[i][j] = malloc(z*sizeof(char));
        }
    }
    return M;
}

// limpar matriz tridimensional
void limpar_matriz(char ***M, int x, int y) {
    int i, j;

    for(i = 0; i < x; i++) {
        for(j = 0; j < y; j++) {
            free(M[i][j]);
            M[i][j] = NULL;
        }
        free(M[i]);
        M[i] = NULL;
    }
    free(M);
    M = NULL;
}

// carrega os textos do file e aloca dinâmicamente
char ***load_file() {
    int n, i, j, k;
    char ***txt;
    char c;

    FILE *entrada = fopen("res/txt/textos.txt", "r");
    if(!entrada) {
        printf("Falha ao carregar o arquivo de texto.\n");
    }

    fscanf(entrada, "%d", &n);
    limpa(entrada);
    
    txt = matriz_tri(n, 9, 34);
    
    for(i=0; i<n; i++) {
        for(j=0; j<9; j++) {
            for(k=0; k<34; k++) {
                fscanf(entrada, "%c", &c);
                
                if(c=='*'){
                    txt[i][j][k] = '\0';
                    break;
                } else {
                    txt[i][j][k] = c;
                }
            } 
            limpa(entrada);
        }
    }

    fclose(entrada);
    return txt;
}

// função implementada para desenhar na tela qualquer texto carregado pelo file
void draw_text(ALLEGRO_FONT *font, ALLEGRO_COLOR font_color, char ***txt, int n){
    int i;

    // desenha texto enquanto o lopping não terminar de acordo com o (n)
    for (i = 0; i <9; i++) {
            al_draw_text(font, font_color, 0, i*22, 0, txt[n][i]);
   }
    al_flip_display();
}

// criado para facilitar a inicialização dos eventos
void init_ev() {
    // Inicialização das interações do mouse
    al_register_event_source(reg_ev, al_get_mouse_event_source());
    al_register_event_source(reg_ev, al_get_display_event_source(janela));    
    // Passando os parâmetros dos possiveis eventos
    al_wait_for_event(reg_ev, &ev);
}

// criado para facilitar na hora de desenhar os textos
void init_txt() {
    // atribuição de cores as variaveis
    clear = al_map_rgb(0, 0, 0);    
    font_color = al_map_rgb(255, 255, 255);

    // carrega a fonte padrao a ser usada
    font = al_load_ttf_font("res/font/architectsdaughter.ttf", 20, 0);
    if (!font) {
        fprintf(stderr, "Falha ao carregar font!\n");
        return;
    }

    // criando subs bitmaps para desenhar os textos
    pos_txt = al_create_sub_bitmap(al_get_backbuffer(janela), 150, 50, 350, 210);
    reset_pos = al_create_sub_bitmap(al_get_backbuffer(janela), 0, 0, 800, 600);
    if (!pos_txt || !reset_pos) {
        fprintf(stderr, "Falha ao criar os subs bitmaps!\n");
        return;
    }
}

void init_img(ALLEGRO_BITMAP *bg, ALLEGRO_BITMAP *personage, ALLEGRO_BITMAP *next) {

    // desenha imagens na tela
    al_draw_bitmap(bg, 0, 0, 0);
    al_draw_bitmap(personage, 15, 15, 0);
    al_draw_bitmap(next, 15, 150, 0);

    // reposiciona a tela e pinta de preto
    al_set_target_bitmap(pos_txt);
    al_clear_to_color(clear);
    al_flip_display();  
}

// carrega a introdução da fase
void load_description_f1(ALLEGRO_DISPLAY *janela){ 

    // inicializa fonte entre outros
    init_txt();

    // variavel recebe os dados do file
    char ***textos = load_file();

    // variaveis recebem imagens a ser desenhadas
    bg = al_load_bitmap("res/img/bg/bg_test.png");
    personage = al_load_bitmap("res/img/gen/tutor.png");
    next = al_load_bitmap("res/img/gen/next.png");
    if (!bg || !personage || !next) {
        fprintf(stderr, "Falha ao carregar imagens!\n");
        return;
    }

    // desenha imagens na tela e posiciona para desenhar o texto
    init_img(bg, personage, next);

    // desenha texto na tela
    draw_text(font, font_color, textos, 0);

    // Criando interações do mouse
    reg_ev = al_create_event_queue();
    if (!reg_ev) {
        fprintf(stderr, "Falha ao criar fila de eventos.\n");
        al_destroy_display(janela);
        return;
    }

    // variavel criada para facilitar o fechamento do loop
    int close=0;

    while (close!=1) {
        // inicia os eventos atuais
        init_ev();

        // Se for um evento do tipo clique, vê a posição do clique.
        if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            // Clique no botão next.
            if (ev.mouse.x >= 15 && ev.mouse.x <= al_get_bitmap_width(next) + 15 &&
                ev.mouse.y >= 150 && ev.mouse.y <= al_get_bitmap_height(next) + 150) {
                
                // atribui 1 ao close para encerrar o loop
                close = 1;

                // apaga os textos antigos e sobrescreve com os atuais
                al_clear_to_color(clear);
                draw_text(font, font_color, textos, 1);
                al_flip_display();

                // Desregistra os eventos de mouse para que novos eventos sejam criados
                al_unregister_event_source(reg_ev, al_get_mouse_event_source());
            } else
                printf("Evento nao suportado.\n");
        }
    }

    while (close!=0) {
        // inicia os eventos atuais
        init_ev();

        // Se for um evento do tipo clique, vê a posição do clique.
        if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            // Clique no botão next.
            if (ev.mouse.x >= 15 && ev.mouse.x <= al_get_bitmap_width(next) + 15 &&
                ev.mouse.y >= 150 && ev.mouse.y <= al_get_bitmap_height(next) + 150) {
                
                // atribui 1 ao close para encerrar o loop
                close = 0;

                // reposiciona a tela ao seu normal 800x600 e atualiza com a background atual
                al_set_target_bitmap(reset_pos);
                al_draw_bitmap(bg, 0, 0, 0);
                al_flip_display();

                // Desregistra os eventos de mouse para que novos eventos sejam criados
                al_unregister_event_source(reg_ev, al_get_mouse_event_source());
            } else
                printf("Evento nao suportado.\n");
        }
    }
}