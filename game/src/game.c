// libs padrões do C
#include <stdio.h>
#include <stdlib.h>

// libs do allegro
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

// libs implementadas
#include "fases/fases.h"
#include "fases/descricao/descricao.h"
#include "geral/dialog.h"

// Atributos da tela
const int LARGURA_TELA = 800;
const int ALTURA_TELA = 600;
    
// Variável representando a janela principal
ALLEGRO_DISPLAY *janela = NULL;

int main() {
    // Variável representando a posição de tela
    ALLEGRO_DISPLAY_MODE disp_data;
    // Variável representando as imagens (menu)
    ALLEGRO_BITMAP *logo = NULL, *jogar = NULL, *sair = NULL;
    // Variável representando as interações de eventos
    ALLEGRO_EVENT_QUEUE *interacao = NULL;
    // Variável representando eventos
    ALLEGRO_EVENT evento;
    // Variável representando cor da fonte
    ALLEGRO_COLOR font_color;
    // Variável representando as fontes utilizadas
    ALLEGRO_FONT *font;

    // Inicializa a Allegro
    al_init();
    // Inicializa o add-on para utilização de imagens
    al_init_image_addon();
    // inicializa a font_addon
    al_init_font_addon();
    // inicializa a ttf_(True Type Font)_addon
    al_init_ttf_addon(); 
    // Atribui em disp_data as configurações de tela
    al_get_display_mode(0, &disp_data);

    // Configura o display
    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if (!janela){
        fprintf(stderr, "Falha ao criar display!\n");
        return -1;
    }
    
    // Atribui onde o display será posicionado
    al_set_window_position(janela, (disp_data.width-LARGURA_TELA)/2, (disp_data.height-ALTURA_TELA)/2);
    // Configura o título do display
    al_set_window_title(janela, "CÓDIGO DE HONRA!");

    // Torna apto o uso de mouse na aplicação
    if (!al_install_mouse()){
        fprintf(stderr, "Falha ao inicializar o mouse.\n");
        al_destroy_display(janela);
        return -1;
    }

    // Atribui o cursor padrão do sistema para ser usado
    if (!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT)) {
        fprintf(stderr, "Falha ao atribuir ponteiro do mouse.\n");
        al_destroy_display(janela);
        return -1;
    }

    // carrega a font a ser usada
    font_color = al_map_rgb(0, 0, 0);
    font = al_load_ttf_font("res/font/architectsdaughter.ttf", 60, 0);
    if (!font) {
        printf("Falha ao inicializar architectsdaughter.ttf");
        return 0;
    }  

    // Carrega as imagens
    logo = al_load_bitmap("res/img/menu/logo.png");
    jogar = al_load_bitmap("res/img/menu/jogar.png");
    sair = al_load_bitmap("res/img/menu/sair.png");

    // Desenha as imagens na tela
    al_clear_to_color(al_map_rgb(255, 255, 255)); // desenha fundo branco
    al_draw_bitmap(logo, 100, 50, 0); // x, y, z(inverte imagem)
    al_draw_bitmap(jogar, 50, 350, 0); // x, y, z(inverte imagem)
    al_draw_bitmap(sair, 50, 450, 0); // x, y, z(inverte imagem)

    // Atualiza a tela
    al_flip_display();

    // Criando interações do mouse
    interacao = al_create_event_queue();
    if (!interacao) {
        fprintf(stderr, "Falha ao inicializar a interacao.\n");
        al_destroy_display(janela);
        return -1;
    }

    // Inicialização das interações do mouse
    al_register_event_source(interacao, al_get_mouse_event_source());
    al_register_event_source(interacao, al_get_display_event_source(janela));
    
    while (1) {
        // Passando parâmetros da função
        al_wait_for_event(interacao, &evento);
        
        // Se houver clique no [X] ele registra o evento e para a execução do jogo
        if (interacao && evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }

        // Se for um evento do tipo clique, vê a posição do clique.
        if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            // Clique no botão sair.
            if (evento.mouse.x >= 50 && evento.mouse.x <= al_get_bitmap_width(sair) + 50 &&
                evento.mouse.y >= 450 && evento.mouse.y <= al_get_bitmap_height(sair) + 450) {
                printf("\nParando a execução...");
                break;
            } 
            // Clique no botão jogar.
            else if (evento.mouse.x >= 50  && evento.mouse.x <= al_get_bitmap_width(jogar) + 50 &&
                     evento.mouse.y >= 350  && evento.mouse.y <= al_get_bitmap_height(jogar) + 350) {
                printf("\nCarregando a primeira fase...\n");

                // Desregistra os eventos de mouse (novos eventos serão criados)
                al_unregister_event_source(interacao, al_get_mouse_event_source());

                // Carrega primeira fase
                load_description_f1(janela);
                fase1_init();

                break;
            } else {
                printf("\nEvento não suportado.");
                continue;
            }
        }
        else if (evento.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
            printf("\nMouse saiu do display.");
        }
        else if (evento.type == ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY) {
            printf("\nMouse entrou no display.");
        }
        // Atualiza a tela
        al_flip_display();            
    }

    // Segura a execução
    al_rest(0.5);
    printf("\nFim da execução!\n");
 
    // Finaliza a display
    al_destroy_display(janela);
 
    return 0;
}

