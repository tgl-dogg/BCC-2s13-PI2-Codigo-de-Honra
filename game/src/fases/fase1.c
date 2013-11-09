#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "desafios/desafios.h"
#include "../geral/cards.h"

void fase1_init(){
	int i;
	ALLEGRO_COLOR color = al_map_rgb(255, 255, 255);

	//struct que controla o desafio
	challenger_rule cr;	

	cr.prog = 3;
	cr.cond = 3;
	cr.act = 3;

	for(i = 0; i < 15; i++){
		cr.v[i] = -1;
	}

    al_clear_to_color(color);

    create_desafio(cr);
    al_flip_display();
}