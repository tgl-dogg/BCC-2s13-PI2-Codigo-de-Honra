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

void draw_text(ALLEGRO_FONT *font, ALLEGRO_COLOR font_color, char ***txt, int n);
void load_description_f1(ALLEGRO_DISPLAY *janela);

#endif
