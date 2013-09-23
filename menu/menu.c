#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

// Atributos da tela
const int LARGURA_TELA = 800;
const int ALTURA_TELA = 600;
 
int main(void){
    // Variável representando a janela principal
    ALLEGRO_DISPLAY *janela = NULL;
    // Variável representando a imagem
    ALLEGRO_BITMAP *fundo = NULL, *start = NULL, *sair = NULL;
    // Variável representando interação de eventos
    ALLEGRO_EVENT_QUEUE *interacao = NULL;

    // Inicializa a Allegro
    al_init();
    // Inicializa o add-on para utilização de imagens
    al_init_image_addon();
    // Configura a janela
    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    // Configura o título da janela
    al_set_window_title(janela, "AMNÉSIA!");

    // Torna apto o uso de mouse na aplicação
    if (!al_install_mouse()){
        fprintf(stderr, "Falha ao inicializar o mouse.\n");
        al_destroy_display(janela);
        return -1;
    }

    // Atribui o cursor padrão do sistema para ser usado
    if (!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT)){
        fprintf(stderr, "Falha ao atribuir ponteiro do mouse.\n");
        al_destroy_display(janela);
        return -1;
    }

    // Carrega a imagem
    fundo = al_load_bitmap("fundo.png");
    start = al_load_bitmap("start.png");
    sair = al_load_bitmap("sair.png");

    // Desenha a imagem na tela
    al_draw_bitmap(fundo, 0, 0, 0);    //x, y, z(inverte imagem)
    al_draw_bitmap(start, 255, 0, 0); //x, y, z(inverte imagem)
    al_draw_bitmap(sair, 380, 400, 0); //x, y, z(inverte imagem)
   
    // Atualiza a tela
    al_flip_display();

    interacao = al_create_event_queue();
    if (!interacao){
        fprintf(stderr, "Falha ao inicializar a interacao.\n");
        al_destroy_display(janela);
        return -1;
    }

    // Inicialização das interações do mouse
    al_register_event_source(interacao, al_get_mouse_event_source());
    
    int na_start= 0;

    while (1){    
        // Espera por um evento
        ALLEGRO_EVENT evento;
        al_wait_for_event(interacao, &evento);

        // Se for um evento do tipo clique, vê a posição.
        if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
            // Clique no botão sair.
            if (evento.mouse.x >= 380 && evento.mouse.x <= al_get_bitmap_width(sair) + 380 &&
                evento.mouse.y >= 400 && evento.mouse.y <= al_get_bitmap_height(sair) + 400) {
                printf("\nParando a execução...");
                break;
            } 
            // Clique no botão start.
            else if (evento.mouse.x >= 255  && evento.mouse.x <= 255 + al_get_bitmap_width(start) &&
                    evento.mouse.y >= 0  && evento.mouse.y <= al_get_bitmap_height(start)) {
                na_start = 1;
                printf("\nJogador clicou no start!");
                continue;
            } else {
                printf("\nEvento não suportado.");
                continue;
            }
        }
        else if (evento.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
            printf("\nMouse entrou no display.");
        }
        else if (evento.type == ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY) {
            printf("\nMouse saiu do display.");
        }

        //if (al_is_event_queue_empty(interacao) == 0) {
            // Atualiza a tela
            al_flip_display();            
        //}
    }

    // Segura a execução
    al_rest(5.0);
    printf("\nFim da execução!\n");
 
    // Finaliza a janela
    al_destroy_display(janela);
 
    return 0;
}
