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

    // Inicialização das interacoes do mouse
    al_register_event_source(interacao, al_get_mouse_event_source());
 
    int na_start= 0;
    while (!sair){
        // Verificacao das interacoes do mouse
        while (!al_is_event_queue_empty(interacao)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(interacao, &evento);
 
            // Se o evento foi de movimentação do mouse
            if (evento.type == ALLEGRO_EVENT_MOUSE_AXES){
                // Verifica se está sobre a região do START
                if (evento.mouse.x >= 255 - al_get_bitmap_width(start)  && evento.mouse.x <= 255 + al_get_bitmap_width(start) &&
                    evento.mouse.y >= 0 - al_get_bitmap_height(start)  && evento.mouse.y <= 0 + al_get_bitmap_height(start) ){
                    na_start = 1;
                }
                else{
                    na_start = 0;
                }
            }
            //Senao... verifica se a interacao foi um clique do mouse
            else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                if (evento.mouse.x >= LARGURA_TELA /*local de clique do mouse*/ - al_get_bitmap_width(sair) - 10 &&
                    evento.mouse.x <= LARGURA_TELA /*local de clique do mouse*/ - 10 && evento.mouse.y <= ALTURA_TELA - 10 &&
                    evento.mouse.y >= ALTURA_TELA /*local de clique do mouse*/ - al_get_bitmap_height(sair) - 10){
                    sair = 0;
                }
            }
        }

        // Atualiza a tela
        al_flip_display();
    }
 
    // Segura a execução
    al_rest(100.0);
 
    // Finaliza a janela
    al_destroy_display(janela);
 
    return 0;
}