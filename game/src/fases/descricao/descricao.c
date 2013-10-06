#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

void copy_str(char dest[], char orig[]){
    int i;

    for(i=0 ; i < 34; i++){
        dest[i] = orig[i];
    }
}

void draw_text(ALLEGRO_FONT *font, ALLEGRO_COLOR font_color, char text[][34], int l){
	int i;
	char s[34];
	
	for(i=0; i<l; i++){
		copy_str(s, text[i]);
		al_draw_text(font, font_color, 0, i*22, 0, s);
	}

	al_flip_display();
}

void draw_text_fase1(ALLEGRO_DISPLAY *janela){

	al_init_font_addon(); // initialize the font addon
	al_init_ttf_addon();// initialize the ttf (True Type Font) addon
    
    ALLEGRO_COLOR font_color = al_map_rgb(0, 0, 0);
	ALLEGRO_FONT *font = al_load_ttf_font("res/font/judson.ttf", 20, 0);
	
	if (!font){
		printf("Could not load judson.ttf");
		return;
	}

	char text[9][34]={"Frase 1", "Frase 2", "Frase 3",
					"Frase 4", "Frase 5", "Frase 6",
					"Frase 7", "Frase 8", "Frase 9"};
	
	ALLEGRO_BITMAP *area_texto = al_create_sub_bitmap(al_get_backbuffer(janela), 150, 50, 510, 270);
    
    al_set_target_bitmap(area_texto);
	draw_text(font, font_color, text, 9);
}