#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
 
int main(){
    int clique_yes=0;
    
    ALLEGRO_DISPLAY *display = NULL;
 
    al_init();
    display = al_create_display(500, 400);
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_flip_display();
    
    clique_yes = al_show_native_message_box(NULL, "CODE WARRIOR",
        "EXIT:", "DESEJA SAIR?",
        NULL, ALLEGRO_MESSAGEBOX_YES_NO);

    if(clique_yes == 1){
        al_show_native_message_box(NULL, "Test",
            "Mensagem:", "ERROR",
            NULL, ALLEGRO_MESSAGEBOX_WARN);
    }else

    al_destroy_display(display);

    return 0;
}