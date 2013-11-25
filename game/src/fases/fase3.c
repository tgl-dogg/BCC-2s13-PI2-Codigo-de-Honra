#include "fases.h"

// Variável externa de janela.
extern ALLEGRO_DISPLAY *janela;

// Background.
extern ALLEGRO_BITMAP *im_bg;

// Monstros.
extern ALLEGRO_BITMAP *im_boss;
extern ALLEGRO_BITMAP *im_mon_set[5];

// Tutor.
extern ALLEGRO_BITMAP *im_tutor;

// Text file.
extern char ***text;

// Condições.
extern char *cond;
extern char *cond_buttons;

void desafio_gosma1(int v[]);
void desafio_gosma2(int v[]);
void desafio_fantasma(int v[]);

int fase3_init() {
	return 0;
}

void desafio_gosma1(int v[]) {
	inicializa_vetor(v);

	v[0] = DIRECT;
	v[1] = ATK;
	v[2] = WHILE;
	v[3] = ARRAY;
	v[4] = ARRAY_GRAB;
	v[5] = WHILE_BREAK;
}

void desafio_gosma2(int v[]) {
	inicializa_vetor(v);

	v[0] = DIRECT;
	v[1] = ATK_DOUBLE;
	v[2] = WHILE;
	v[3] = ARRAY;
	v[4] = ARRAY_GRAB;
	v[5] = WHILE_BREAK;
}

void desafio_fantasma(int v[]) {
	inicializa_vetor(v);

	v[0] = WHILE;
	v[1] = ARRAY;
	v[2] = ARRAY_USE;
	v[3] = WHILE_BREAK;
	v[4] = WHILE;
	v[5] = 10000+2; //alguma condição
	v[6] = ATK;
	v[7] = WHILE_BREAK;
}