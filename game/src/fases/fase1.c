#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "desafios/desafios.h"

void fase1_init(ALLEGRO_DISPLAY *janela, ALLEGRO_EVENT_QUEUE *interacao){
    ALLEGRO_COLOR clr = al_map_rgb(255, 255, 255);
    al_clear_to_color(clr);

    desafio1_fase1(janela, interacao);
    al_flip_display();
}