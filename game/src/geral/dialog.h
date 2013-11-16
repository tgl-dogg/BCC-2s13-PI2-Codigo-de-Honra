#ifndef _DIALOG_H_
#define _DIALOG_H_

void copy_str(char dest[], char orig[]);
void print_text(ALLEGRO_FONT *font, ALLEGRO_COLOR font_color, char text[TAM]);
void print_bname(ALLEGRO_FONT *font, ALLEGRO_COLOR font_color, char text[TAM]);
int	dialog(char text[TAM], char bname1[TAM], char bname2[TAM]);

#endif
