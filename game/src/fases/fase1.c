#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "desafios/desafios.h"
#include "../geral/cards.h"

void fase1_init(){
    ALLEGRO_COLOR clr = al_map_rgb(255, 255, 255);
    al_clear_to_color(clr);

    create_desafio();
    al_flip_display();
}