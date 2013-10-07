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
	char string[34];
	
	for(i=0; i<l; i++){
		copy_str(string, text[i]);
		al_draw_text(font, font_color, 0, i*22, 0, string);
	}

	al_flip_display();
}

static ALLEGRO_COLOR clr, font_color;
static ALLEGRO_FONT *font;
static ALLEGRO_BITMAP *personage = NULL, *next = NULL;
static ALLEGRO_BITMAP *area_texto, *reset_area;
static ALLEGRO_EVENT_QUEUE *interacao = NULL;
static ALLEGRO_EVENT evento;

void draw_text_fase1(ALLEGRO_DISPLAY *janela){
	al_init_font_addon(); // initialize the font addon
	al_init_ttf_addon();// initialize the ttf (True Type Font) addon

	font_color = al_map_rgb(0, 0, 0);
	font = al_load_ttf_font("res/font/judson.ttf", 20, 0);
	area_texto = al_create_sub_bitmap(al_get_backbuffer(janela), 150, 50, 350, 200);
	reset_area = al_create_sub_bitmap(al_get_backbuffer(janela), 0, 0, 800, 600);

	char text[9][34]= {"Olá! Seja Bem Vindo!", "Ouvi dizer que voce quer,", "participar do torneio, bem,",
					   "acha que tem capacidade pra isso?", "Se ainda tem duvidas, venha comigo", "tenho algo para voce fazer.",
					   "Se voce se sair bem,", "lhe darei um passport,", "com ele você podera ir ao torneio"};
	
	char text2[9][34]= {"frase1", "frase2", "frase3",
			   		    "frase4", "frase5", "frase6",
				        "frase7", "frase8", "frase9"};
    
	personage = al_load_bitmap("res/img/gen/tutor.png");
	next = al_load_bitmap("res/img/gen/next.png");
    
    al_draw_bitmap(personage, 15, 15, 0);
    al_draw_bitmap(next, 15, 150, 0);
	al_set_target_bitmap(area_texto);
    draw_text(font, font_color, text, 9);
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
				clr = al_map_rgb(255, 255, 255);
    			al_clear_to_color(clr);
   			    draw_text(font, font_color, text2, 9);
   			    al_set_target_bitmap(reset_area);
   			    click = 1;
    		}
		} 
	}
}