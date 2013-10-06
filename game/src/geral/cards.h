#ifndef _CARDS_H_
#define _CARDS_H_

// Posição e tamanho da área "programação"
#define PROG_X 35
#define PROG_Y 350
#define PROG_W 150
#define PROG_H 210

// Posição e tamanho da área "condição"
#define COND_X 215
#define COND_Y 350
#define COND_W 150
#define COND_H 210

// Posição e tamanho da área "ações"
#define ACT_X 395
#define ACT_Y 350
#define ACT_W 150
#define ACT_H 210

// Posição e tamanho do botão memória
#define MEM_X 608
#define MEM_Y 372
#define MEM_W 64
#define MEM_H 64

// Posição e tamanho do botão help
#define HELP_X 678
#define HELP_Y 372
#define HELP_W 64
#define HELP_H 64

// Posição e tamanho do botão compilar
#define COMP_X 610
#define COMP_Y 442
#define COMP_W 128
#define COMP_H 128

// Posição e tamanho do botão reset
#define RES_X 20
#define RES_Y 230
#define RES_W 150
#define RES_H 210

// Posição e tamanho para área de "cartas selecionadas"
#define SLCT_X 570
#define SLCT_Y 10
#define SLCT_W 210
#define SLCT_H 350

// Espaçamento entre os botões
#define BTN_MARGIN 70


void draw_compile_card(ALLEGRO_BITMAP *imagem);
void draw_memory_card(ALLEGRO_BITMAP *imagem);
void draw_help_card(ALLEGRO_BITMAP *imagem);

void draw_prog_cards(ALLEGRO_BITMAP *img[], int n);
void draw_conditional_cards(ALLEGRO_BITMAP *img[], int n);
void draw_action_cards(ALLEGRO_BITMAP *img[], int n);

void draw_selected_cards(ALLEGRO_BITMAP *imagem, int i);

#endif