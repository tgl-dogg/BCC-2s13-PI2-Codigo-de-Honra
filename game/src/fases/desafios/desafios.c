#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>

void draw_cards(ALLEGRO_BITMAP *img[], int n){
	// cards opções: x40 y445
	// cards seleconado: x670 y25

	int x = 40, y = 445;
	int i = 0;

	for(i; i < n; i++){		
		al_draw_bitmap(img[i], x, y, 0);
		x += 75;
	}

	y += 70;
	al_draw_bitmap(img[0], x, y, 0);
}

void desafio1_fase1(ALLEGRO_DISPLAY *janela){
    ALLEGRO_COLOR font_color = al_map_rgb(0, 0, 0);
 
	al_init_font_addon(); // initialize the font addon
	al_init_ttf_addon();// initialize the ttf (True Type Font) addon
	
	ALLEGRO_FONT *font = al_load_ttf_font("res/font/poke_hollow.ttf", 20, 0);
	
	if (!font){
		printf("Could not load poke_hollow.ttf");
		return;
	}

	ALLEGRO_BITMAP *img[3];
	int img_size = 3;
    img[0] = al_load_bitmap("res/img/prog/if_symbol.png");    
    img[1] = al_load_bitmap("res/img/prog/while_symbol.png");
    img[2] = al_load_bitmap("res/img/prog/array_symbol.png");

    draw_cards(img, img_size);

    char txt[] = "Gotta code'em all!";	
	al_draw_text(font, font_color, 800/2, (600/4), ALLEGRO_ALIGN_CENTRE, txt);
	al_flip_display();
}