#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define TAM 2
#define MAX 25

static    ALLEGRO_DISPLAY_MODE disp_data;
static    ALLEGRO_BITMAP *bnew1 = NULL, *bnew2 = NULL, *pos_cond1, *pos_cond2;
static    ALLEGRO_EVENT_QUEUE *reg_ev = NULL;
static    ALLEGRO_EVENT ev;
static    ALLEGRO_COLOR font_color;
static    ALLEGRO_FONT *font;

// Variável representando a display principal
ALLEGRO_DISPLAY *display = NULL;

void copy_str(char dest[], char orig[]){
    int i;
 
    for(i=0 ; i < MAX; i++){
        dest[i] = orig[i];
    }
}
 
void print_cond(ALLEGRO_FONT *font, ALLEGRO_COLOR font_color, char cond1[][MAX], char cond2[][MAX]){
    int i, j;
    char string1[MAX];
    char string2[MAX];

    pos_cond1 = al_create_sub_bitmap(al_get_backbuffer(display), 30, 20, 370, 70);
    al_set_target_bitmap(pos_cond1);    
    for(i=0; i<TAM; i++){
        copy_str(string1, cond1[i]);
        al_draw_text(font, font_color, 0, i*22, 0, string1);
    }

    pos_cond2 = al_create_sub_bitmap(al_get_backbuffer(display), 30, 70, 370, 140);
    al_set_target_bitmap(pos_cond2);   
    for(j=0; j<TAM; j++){
        copy_str(string2, cond2[j]);
        al_draw_text(font, font_color, 0, j*22, 0, string2);
    }
 
    al_flip_display();
}

int load_cond(char cond1[][MAX], char cond2[][MAX]) {

    al_init();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon(); 
    al_get_display_mode(0, &disp_data);

    // Configura o display
    display = al_create_display(400, 250);
    if (!display){
        fprintf(stderr, "Falha ao criar display!\n");
        return -1;
    }
    
    // Atribui onde o display será posicionado
    al_set_window_position(display, (disp_data.width-400)/2, (disp_data.height-250)/2);
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

    font_color = al_map_rgb(255, 255, 255);
    font = al_load_ttf_font("../../res/font/architectsdaughter.ttf", 20, 0);
    if(!font){
        printf("Falha ao carregar architectsdaughter.ttf");
        return 0;
    }

    // carrega as imagens
    bnew1 = al_load_bitmap("../../res/img/dialog/bnew.png");
    bnew2 = al_load_bitmap("../../res/img/dialog/bnew.png");

    // desenha as imagens
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(bnew1, 60, 175, 0);
    al_draw_bitmap(bnew2, 240, 175, 0);

    // desenha texto em tela
    al_draw_text(font, font_color, 75, 180, 0, "cond 1");
    al_draw_text(font, font_color, 250, 180, 0, "cond 2");
    print_cond(font, font_color, cond1, cond2);

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
            if (ev.mouse.x >= 60 && ev.mouse.x <= al_get_bitmap_width(bnew1) + 60 &&
                ev.mouse.y >= 175 && ev.mouse.y <= al_get_bitmap_height(bnew1) + 175) {
                return 0;
            } // clique no botão2 
            else if (ev.mouse.x >= 240  && ev.mouse.x <= al_get_bitmap_width(bnew2) + 240 &&
                     ev.mouse.y >= 175  && ev.mouse.y <= al_get_bitmap_height(bnew2) + 175) {
                    // desintegra as interações atuais
                    al_unregister_event_source(reg_ev, al_get_mouse_event_source());
                    return 1;
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