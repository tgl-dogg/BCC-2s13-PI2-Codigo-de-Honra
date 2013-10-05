#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

//extern evento;
//extern interacao;
//extern ALLEGRO_DISPLAY *display;

void draw_cards(ALLEGRO_BITMAP *img[], int n){
	// cards opções: x40 y445
	// cards seleconado: x670 y25

	int x = 40, y = 445;
	int i = 0;

	for(i; i < n; i++){
		if(x > 550){
			x = 40;
			y += 70;
		}

		al_draw_bitmap(img[i], x, y, 0);
		x += 75;
	}
}

void desafio1_fase1(ALLEGRO_DISPLAY *janela){
    ALLEGRO_COLOR font_color = al_map_rgb(0, 0, 0);

    ALLEGRO_BITMAP *bg = al_load_bitmap("res/img/bg/battle_layout.png");
    al_draw_bitmap(bg, 0, 0, 0);
 
	al_init_font_addon(); // initialize the font addon
	al_init_ttf_addon();// initialize the ttf (True Type Font) addon
	
	ALLEGRO_FONT *font = al_load_ttf_font("res/font/judson.ttf", 40, 0);
	
	if (!font){
		printf("Could not load judson.ttf");
		return;
	}

	ALLEGRO_BITMAP *img[3];
	int img_size = 3;
    img[0] = al_load_bitmap("res/img/prog/if_symbol.png");    
    img[1] = al_load_bitmap("res/img/prog/while_symbol.png");
    img[2] = al_load_bitmap("res/img/prog/array_symbol.png");

    draw_cards(img, img_size);
    
    ALLEGRO_BITMAP *teste = al_create_sub_bitmap(al_get_backbuffer(janela), 200, 150, 600, 150);
    al_draw_bitmap(teste, 0, 200, 0);

    al_set_target_bitmap(teste);

    char txt[] = "Gotta code'em all!";	
	//al_draw_text(font, font_color, 800/2, (600/4), ALLEGRO_ALIGN_CENTRE, txt);
	al_draw_text(font, font_color, 0, 0, 0, txt);
	al_flip_display();

    al_rest(5);

	ALLEGRO_COLOR clr = al_map_rgb(255, 255, 255);
    al_clear_to_color(clr);

    char txt2[] = "Faça x coisa á é í ó ú ão!";	
    //al_draw_text(font, font_color, 800/2, (600/4), ALLEGRO_ALIGN_CENTRE, txt2);	
    al_draw_text(font, font_color, 0, 0, 0, txt2);	
    al_update_display_region(0, 0, 800, 400);

    al_set_target_bitmap(al_get_backbuffer(janela));
    al_draw_text(font, font_color, 0, 0, 0, txt2);	
}