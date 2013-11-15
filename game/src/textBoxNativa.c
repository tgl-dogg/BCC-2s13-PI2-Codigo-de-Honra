#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

void textBoxNativa(char frase[]) {
	(al_show_native_message_box(NULL, "Código de Honra!",
     "", "frase[]",
     NULL, ALLEGRO_MESSAGEBOX_ERROR));

     return;
}