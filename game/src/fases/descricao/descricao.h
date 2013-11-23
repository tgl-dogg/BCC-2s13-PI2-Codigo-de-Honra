#ifndef _DESCRICAO_H_
#define _DESCRICAO_H_

#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

void init_ev();

char ***load_file();
char ***matriz_tri(int x, int y, int z);

void limpa(FILE *entrada);
void limpar_matriz(char ***M, int x, int y);

void init_ev();
void init_font();
void init_img(ALLEGRO_BITMAP *bg, ALLEGRO_BITMAP *personage, ALLEGRO_BITMAP *next);

void draw_text(ALLEGRO_FONT *font, ALLEGRO_COLOR font_color, char ***txt, int n);
void draw_description(char ***textos, int n);
void next_description(int close);


void load_description_f1(ALLEGRO_DISPLAY *janela);
void load_description_f2(ALLEGRO_DISPLAY *janela);

void destroy_recus(ALLEGRO_BITMAP *bg, ALLEGRO_BITMAP *personage, ALLEGRO_BITMAP *next, 
                   ALLEGRO_BITMAP *pos_txt, ALLEGRO_BITMAP *reset_pos, ALLEGRO_EVENT_QUEUE *reg_ev);

#endif
