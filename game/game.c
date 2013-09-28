#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

// Atributos da tela
const int LARGURA_TELA = 800;
const int ALTURA_TELA = 600;
 
int main(void){
    // Variável representando a janela principal
    ALLEGRO_DISPLAY *janela = NULL;
    // Variável representando as imagens (background)
    ALLEGRO_BITMAP *b01 = NULL, *b02 = NULL;
    // Variável representando as imagens (menu)
    ALLEGRO_BITMAP *start = NULL, *leave = NULL, *name = NULL, *credits = NULL;
    // Variável representando as imagens (animale)
    ALLEGRO_BITMAP  *reptile = NULL, *snake = NULL, *skull = NULL, *waps = NULL, *spider = NULL, *bug = NULL;
    // Variável representando as imagens (boss)
    ALLEGRO_BITMAP *demon = NULL, *hydra = NULL, *phantom = NULL, *dragon = NULL;
    // Variável representando as imagens (actions)
    ALLEGRO_BITMAP *atk = NULL, *atk_2x = NULL, *run = NULL, *def = NULL; 
    ALLEGRO_BITMAP *healer = NULL, *book = NULL, *potion = NULL, *door = NULL, *key = NULL;
    ALLEGRO_BITMAP *repetir = NULL, *next = NULL, *se = NULL, *map = NULL, *help = NULL;
    // Variável representando as interações de eventos
    ALLEGRO_EVENT_QUEUE *interacao = NULL;

    // Inicializa a Allegro
    al_init();
    // Inicializa o add-on para utilização de imagens
    al_init_image_addon();
    // Configura a janela
    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    // Configura o título da janela
    al_set_window_title(janela, "Algorithms!");

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
    b01 = al_load_bitmap("resources/background/b01.png");
    name = al_load_bitmap("resources/menu/name.png");
    start = al_load_bitmap("resources/menu/start.png");
    leave = al_load_bitmap("resources/menu/exit.png");

    // Desenha a imagem na tela
    al_draw_bitmap(b01, 0, 0, 0);    //x, y, z(inverte imagem)
    al_draw_bitmap(name, 280, 100, 0);    //x, y, z(inverte imagem)
    al_draw_bitmap(start, 350, 250, 0); //x, y, z(inverte imagem)
    al_draw_bitmap(leave, 350, 400, 0); //x, y, z(inverte imagem)

    // Atualiza a tela
    al_flip_display();

    // Criando interações do mouse
    interacao = al_create_event_queue();
    if (!interacao){
        fprintf(stderr, "Falha ao inicializar a interacao.\n");
        al_destroy_display(janela);
        return -1;
    }

    // Inicialização das interações do mouse
    al_register_event_source(interacao, al_get_mouse_event_source());
    
    int clique = 0;

    while (1){    
        // Espera por um evento
        ALLEGRO_EVENT evento;
        al_wait_for_event(interacao, &evento);

        // Se for um evento do tipo clique, vê a posição do clique.
        if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
            // Clique no botão leave.
            if (evento.mouse.x >= 350 && evento.mouse.x <= al_get_bitmap_width(leave) + 350 &&
                evento.mouse.y >= 400 && evento.mouse.y <= al_get_bitmap_height(leave) + 400) {
                printf("\nParando a execução...");
                break;
            } 
            // Clique no botão start.
            else if (evento.mouse.x >= 350  && evento.mouse.x <= al_get_bitmap_width(start) + 350 &&
                     evento.mouse.y >= 250  && evento.mouse.y <= al_get_bitmap_height(start) + 250) {
                printf("\nCarregando a primeira fase...");
                
                //Atribui 1, desta forma valida o if abaixo e inicializa o jogo 
                clique = 1;
                // primeira fase
                if(clique == 1){
                    al_destroy_display(janela);
                    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
                    al_set_window_title(janela, "FASE1!");
                
                    b01 = al_load_bitmap("resources/background/b01.png");
                    skull = al_load_bitmap("resources/animale/skull.png");
                    atk = al_load_bitmap("resources/actions/atk.png");
                    def = al_load_bitmap("resources/actions/def.png");
                    run = al_load_bitmap("resources/actions/run.png");
                    healer = al_load_bitmap("resources/actions/healer.png");
                    next = al_load_bitmap("resources/actions/next.png");

                    al_draw_bitmap(b01, 0, 0, 0);
                    al_draw_bitmap(skull, 30, 30, 0);
                    al_draw_bitmap(atk, 53, 450, 0);
                    al_draw_bitmap(def, 193, 450, 0);
                    al_draw_bitmap(run, 333, 450, 0);
                    al_draw_bitmap(healer, 473, 450, 0);
                    al_draw_bitmap(next, 613, 450, 0);
                    
                    al_flip_display();
                    al_rest(100.0);
                    break;
                }

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
 
    // Finaliza a janela
    al_destroy_display(janela);
 
    return 0;
}

