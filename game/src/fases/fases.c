#include "fases.h"
#include "descricao/descricao.h"

extern ALLEGRO_DISPLAY *janela;

/* Inicialização das fases no geral. */
void fases_init(){
	load_description_f1(janela);
    fase1_init();
}