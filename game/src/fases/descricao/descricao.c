#include <stdio.h>
#include <string.h>
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
	char string[34];
	
	for(i=0; i<l; i++){
		copy_str(string, text[i]);
		al_draw_text(font, font_color, 0, i*22, 0, string);
	}

	al_flip_display();
}

static ALLEGRO_COLOR clr, font_color;
static ALLEGRO_FONT *font;
static ALLEGRO_BITMAP *bg = NULL, *personage = NULL, *next = NULL;
static ALLEGRO_BITMAP *area_texto, *reset_area;
static ALLEGRO_EVENT_QUEUE *interacao = NULL;
static ALLEGRO_EVENT evento;

void draw_text_fase1(ALLEGRO_DISPLAY *janela){
	al_init_font_addon(); // initialize the font addon
	al_init_ttf_addon();// initialize the ttf (True Type Font) addon

	font_color = al_map_rgb(255, 255, 255);
	font = al_load_ttf_font("res/font/architectsdaughter.ttf", 20, 0);
	area_texto = al_create_sub_bitmap(al_get_backbuffer(janela), 150, 50, 350, 210);
	reset_area = al_create_sub_bitmap(al_get_backbuffer(janela), 0, 0, 800, 600);

	char tutor[9][34]= {"Olá! Seja Bem Vindo!", "Ouvi dizer que voce quer,", "participar do torneio, bem,",
			            "você ja tem seu passport?", "Se ainda não tem, siga-me", "tenho algo para você fazer.",
			            "Se você se sair bem nisto,", "ganhará um passport.", "E então... Vamos?"};

	char text1[9][34]= {"frase1", "frase2", "frase3", 
				        "frase4", "frase5", "frase6", 
				        "frase7", "frase8", "frase9"};
    
    // carrega as bitmaps
    bg = al_load_bitmap("res/img/bg/bg_test.png");
	personage = al_load_bitmap("res/img/gen/tutor.png");
	next = al_load_bitmap("res/img/gen/next.png");
    // desenha as bitmaps
    al_draw_bitmap(bg, 0, 0, 0);
    al_draw_bitmap(personage, 15, 15, 0);
    al_draw_bitmap(next, 15, 150, 0);
	// reposiciona a tela e pinta de preto
	al_set_target_bitmap(area_texto);
	clr = al_map_rgb(0, 0, 0);
    al_clear_to_color(clr);
    // desenha o texto
    draw_text(font, font_color, tutor, 9);
    al_flip_display();
	
    if (!al_install_mouse()){
    	return;
    }
    if (!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT)){
    	return;
    }
    interacao = al_create_event_queue();
    if (!interacao){
    	return;
    }

    al_register_event_source(interacao, al_get_mouse_event_source());

    int click=0;
    
    while(click != 1){
	    al_wait_for_event(interacao, &evento);
    	if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
    		if (evento.mouse.x >= 15 && evento.mouse.x <= al_get_bitmap_width(next) + 15 &&
            	evento.mouse.y >= 150 && evento.mouse.y <= al_get_bitmap_height(next) + 150) {
				clr = al_map_rgb(0, 0, 0);
    			al_clear_to_color(clr);
   			    draw_text(font, font_color, text1, 9);
                al_set_target_bitmap(reset_area);
                al_rest(5.0);
                al_destroy_event_queue(interacao);
                click = 1;
            }
		} 
	}
}


