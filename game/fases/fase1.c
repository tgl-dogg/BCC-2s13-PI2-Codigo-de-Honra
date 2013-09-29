#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

void fase1_init(ALLEGRO_DISPLAY *janela){
    ALLEGRO_COLOR clr = al_map_rgb(255, 255, 255);
    al_clear_to_color(clr);
    al_flip_display();
}