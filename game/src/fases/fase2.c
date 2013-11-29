#include "fases.h"

// Variável externa de janela.
extern ALLEGRO_DISPLAY *janela;

// Background.
extern ALLEGRO_BITMAP *im_bg;

// Monstros.
extern ALLEGRO_BITMAP *im_boss;
extern ALLEGRO_BITMAP *im_mon_set[5];

// Tutor.
extern ALLEGRO_BITMAP *im_tutor;

// Text file.
extern char ***text;

// Condições.
extern char cond[500];
extern char cond_buttons[500];

void desafio_sea_serpent(int v[]);
void desafio_hydra(int v[]);

int fase2_init() {
	// Guarda qual texto do file queremos utilizar;
	int text_pos, resultado_desafio;
	// Aloca os desafios desta fase.
	int v[15];

	// Cor para limpar a tela
	ALLEGRO_COLOR clean_color;

	// Imagem de quem está falando com o jogador;
	ALLEGRO_BITMAP *speaker;

	// Struct que controla o desafio
	challenger_rule cr;	
	// Inicializa a struct dos desafios
	cr_init(&cr);
	
	// Define a cor para limpar a tela (preto), limpa e adiciona o background.
 	clean_color = al_map_rgb(0, 0, 0);
    al_clear_to_color(clean_color);
    al_draw_bitmap(im_bg, 0, 0, 0);

    // Define as cartas a serem desenhadas.
    cr.prog = 2;
    cr.cond = 2;
    cr.act = 2;

    draw_prog_cards(cr);    
    draw_conditional_cards(cr);
    draw_action_cards(cr);
    al_flip_display();

	text_pos = 0;
    speaker = im_tutor;
    draw_text(text, text_pos, speaker);

    cr.prog = 2;
    cr.cond = 2;
    cr.act = 3;

    draw_prog_cards(cr);    
    draw_conditional_cards(cr);
    draw_action_cards(cr);
    al_flip_display();

	text_pos = 1;
    draw_text(text, text_pos, speaker);

	text_pos = 2;
    draw_text(text, text_pos, speaker);
    
    // Desafio da Serpente 1.
	text_pos = 3;
    speaker = im_mon_set[3];
    draw_text(text, text_pos, speaker);

    desafio_sea_serpent(v);
    transferir_desafio(&cr, v);
    resultado_desafio = create_desafio(cr);

    if (resultado_desafio <= 0) {
        resultado_desafio = show_try_again_dialog("Desafio da Serpente Marinha");
        if (resultado_desafio == 1) {
            return 0;
        } else {
            return resultado_desafio;
        }
    }

    al_clear_to_color(clean_color);
    al_draw_bitmap(im_bg, 0, 0, 0);
    al_flip_display();
    
	text_pos = 4;
    speaker = im_tutor;
    draw_text(text, text_pos, speaker);
    
    // Desafio da Serpente 2.
	text_pos = 5;
    speaker = im_mon_set[3];
    draw_text(text, text_pos, speaker);

    desafio_sea_serpent(v);
    transferir_desafio(&cr, v);
    resultado_desafio = create_desafio(cr);

    if (resultado_desafio <= 0) {
        resultado_desafio = show_try_again_dialog("Desafio da Serpente Marinha");
        if (resultado_desafio == 1) {
            return 0;
        } else {
            return resultado_desafio;
        }
    }

    al_clear_to_color(clean_color);
    al_draw_bitmap(im_bg, 0, 0, 0);
    al_flip_display();

    cr.prog = 3;
    cr.cond = 3;
    cr.act = 3;

    draw_prog_cards(cr);    
    draw_conditional_cards(cr);
    draw_action_cards(cr);
    al_flip_display();
    
	text_pos = 6;
    speaker = im_tutor;
    draw_text(text, text_pos, speaker);
    
	text_pos = 7;
    draw_text(text, text_pos, speaker);
    
	text_pos = 8;
    draw_text(text, text_pos, speaker);
    
	text_pos = 9;
    draw_text(text, text_pos, speaker);
    
    // Boss.
	text_pos = 10;
    speaker = im_boss;
    draw_text(text, text_pos, speaker);

    desafio_hydra(v);
    transferir_desafio(&cr, v);
    resultado_desafio = create_desafio(cr);

    if (resultado_desafio <= 0) {
        resultado_desafio = show_try_again_dialog("Desafio da Hydra");
        if (resultado_desafio == 1) {
            return 0;
        } else {
            return resultado_desafio;
        }
    }

    al_clear_to_color(clean_color);
    al_draw_bitmap(im_bg, 0, 0, 0);
    al_flip_display();
    
	text_pos = 11;
    speaker = im_tutor;
    draw_text(text, text_pos, speaker);

	return 1;
}

void desafio_sea_serpent(int v[]) {
	inicializa_vetor(v);
    transferir_condicao(cond, "I- Se a serpente marinha estiver distraída;\nII- Se a serpente marinha for fêmea;\nIII- Se a serpente marinha estiver submersa;\nIV- Se a serpente não for marinha.");
    transferir_condicao(cond_buttons, "Condição I|Condição II|Condição III|Condição IV");

	v[0] = IF;
	v[1] = 10000+3; //alguma condição "Se a serpente está destraída"
	v[2] = ATK_DOUBLE;
	v[3] = IF_ELSE;
	v[4] = ATK;
}

void desafio_hydra(int v[]) {
	inicializa_vetor(v);
    transferir_condicao(cond, "I- Enquanto a hydra possuir cabeças;\nII- Se a hydra estiver se regenerando;\nIII- Se a hydra preparar um ataque;\nIV- Enquanto a hydra for uma serpente marinha;\nV- Se a hydra estiver na água.");
    transferir_condicao(cond_buttons, "Condição I|Condição II|Condição III|Condição IV|Condição V");

	v[0] = WHILE;
	v[1] = 10000+1; // alguma condição "enquanto ela tiver cabeças"
	v[2] = IF;
	v[3] = 10000+3; // alguma condição "se ela estiver atacando"
	v[4] = DEF;
	v[5] = IF_ELSE;
	v[6] = ATK_DOUBLE;
	v[7] = WHILE_BREAK;
}