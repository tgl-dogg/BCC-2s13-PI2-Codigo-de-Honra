#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define TAM 15

// Atributos da tela
const int LARGURA_TELA = 300;
const int ALTURA_TELA = 200;
    
// Variável representando a display principal
ALLEGRO_DISPLAY *display = NULL;

void copy_str(char dest[], char orig[]){
    int i;

    for(i=0 ; i < TAM; i++){
        dest[i] = orig[i];
    }
}

void print_text(ALLEGRO_FONT *font, ALLEGRO_COLOR font_color, char text[TAM]){
    int i;
    char string[TAM];
    
    for(i=0; i<2; i++){
        copy_str(string, text);
        al_draw_text(font, font_color, 0, i*22, 0, string);
    }

    al_flip_display();
}

void print_bname(ALLEGRO_FONT *font, ALLEGRO_COLOR font_color, char text[TAM]){
    int i;
    char string[TAM];
    
    copy_str(string, text);
    al_draw_text(font, font_color, 0, 0, 0, string);
    al_flip_display();
}

int dialog(char text[TAM], char bname1[TAM], char bname2[TAM]) {
    ALLEGRO_DISPLAY_MODE disp_data;
    ALLEGRO_BITMAP *bnew1 = NULL, *bnew2 = NULL, *pos_text, *pos_bname1, *pos_bname2;
    ALLEGRO_EVENT_QUEUE *reg_ev = NULL;
    ALLEGRO_EVENT ev;
    ALLEGRO_COLOR font_color;
    ALLEGRO_FONT *font;

    al_init();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon(); 
    al_get_display_mode(0, &disp_data);

    // Configura o display
    display = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if (!display){
        fprintf(stderr, "Falha ao criar display!\n");
        return -1;
    }
    
    // Atribui onde o display será posicionado
    al_set_window_position(display, (disp_data.width-LARGURA_TELA)/2, (disp_data.height-ALTURA_TELA)/2);
    // Configura o título do display
    al_set_window_title(display, "NOME DA JANELA!");

    // Torna apto o uso de mouse na aplicação
    if (!al_install_mouse()){
        fprintf(stderr, "Falha ao inicializar o mouse.\n");
        al_destroy_display(display);
        return -1;
    }

    // Atribui o cursor padrão do sistema para ser usado
    if (!al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT)){
        fprintf(stderr, "Falha ao atribuir ponteiro do mouse.\n");
        al_destroy_display(display);
        return -1;
    }

    font_color = al_map_rgb(0, 0, 0);
    font = al_load_ttf_font("../../res/font/architectsdaughter.ttf", 20, 0);
    if(!font){
        printf("Falha ao carregar architectsdaughter.ttf");
        return 0;
    }
    
    bnew1 = al_load_bitmap("../../res/img/dialog/bnew.png");
    bnew2 = al_load_bitmap("../../res/img/dialog/bnew.png");
    pos_text = al_create_sub_bitmap(al_get_backbuffer(display), 50, 25, 210, 100);
    pos_bname1 = al_create_sub_bitmap(al_get_backbuffer(display), 45, 135, 125, 200);
    pos_bname2 = al_create_sub_bitmap(al_get_backbuffer(display), 195, 135, 175, 200);
    
    // desenha imagens
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_draw_bitmap(bnew1, 25, 125, 0);
    al_draw_bitmap(bnew2, 175, 125, 0);

    // desenha texto em tela
    al_set_target_bitmap(pos_text);
    print_text(font, font_color, text);
    al_set_target_bitmap(pos_bname1);
    print_bname(font, font_color, bname1);
    al_set_target_bitmap(pos_bname2);    
    print_bname(font, font_color, bname2);

    al_flip_display();

    // Criando interações do mouse
    reg_ev = al_create_event_queue();
    if (!reg_ev){
        fprintf(stderr, "Falha ao inicializar o registro de eventos.\n");
        al_destroy_display(display);
        return -1;
    }

    // Inicialização das interações do mouse
    al_register_event_source(reg_ev, al_get_mouse_event_source());
    while (1){
        al_wait_for_event(reg_ev, &ev);
        
        if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
            // clique no botão1
            if (ev.mouse.x >= 25 && ev.mouse.x <= al_get_bitmap_width(bnew1) + 25 &&
                ev.mouse.y >= 125 && ev.mouse.y <= al_get_bitmap_height(bnew1) + 125) {
                return -1;
            } // clique no botão2 
            else if (ev.mouse.x >= 175  && ev.mouse.x <= al_get_bitmap_width(bnew2) + 175 &&
                     ev.mouse.y >= 125  && ev.mouse.y <= al_get_bitmap_height(bnew2) + 125) {
                    // desintegra as interações atuais
                    al_unregister_event_source(reg_ev, al_get_mouse_event_source());
                    return 0;
            } else {
                printf("\nEvento não suportado.\n");
                continue;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
            printf("\nMouse saiu do display.\n");
        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY) {
            printf("\nMouse entrou no display.\n");
        }
        al_flip_display();            
    }
    al_rest(0.5);
    al_destroy_display(display);

    return 0;
}

int main() {
    char txt[TAM]={"012345678912345"};
    char bt1[TAM]={"false"}, bt2[TAM]={"true"};

    dialog(txt, bt1, bt2);
}