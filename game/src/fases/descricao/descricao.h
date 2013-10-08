#ifndef _DESCRICAO_H_
#define _DESCRICAO_H_

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

void copy_str(char dest[], char orig[]);
void draw_text(ALLEGRO_FONT *font, ALLEGRO_COLOR font_color, char text[][34], int l);
void draw_text_fase1(ALLEGRO_DISPLAY *janela);


#endif
