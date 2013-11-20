#ifndef _DIALOG_H_
#define _DIALOG_H_

#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define TAM 2
#define MAX 25

void copy_str(char dest[], char orig[]);

void print_cond(ALLEGRO_FONT *font, ALLEGRO_COLOR font_color, char cond1[][MAX], char cond2[][MAX]);

int load_cond(char cond1[][MAX], char cond2[][MAX]);

#endif
