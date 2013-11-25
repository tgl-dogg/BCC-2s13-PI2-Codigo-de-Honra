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

void desafio_sea_serpent(int v[]);
void desafio_hydra(int v[]);

int fase2_init() {
	return 0;
}

void desafio_sea_serpent(int v[]) {
	inicializa_vetor(v);

	v[0] = IF;
	v[1] = 10000+3; //alguma condição "Se a serpente está destraída"
	v[2] = ATK_DOUBLE;
	v[3] = IF_ELSE;
	v[4] = ATK;
}

void desafio_hydra(int v[]) {
	inicializa_vetor(v);

	v[0] = WHILE;
	v[1] = 10000+1; // alguma condição "enquanto ela tiver cabeças"
	v[2] = IF;
	v[3] = 10000+3; // alguma condição "se ela estiver atacando"
	v[4] = DEF;
	v[5] = IF_ELSE;
	v[6] = ATK_DOUBLE;
	v[7] = WHILE_BREAK;
}