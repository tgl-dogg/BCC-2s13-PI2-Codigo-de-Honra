#include "dialog.h"

int show_dialog(char *title, char *heading, char *content, char *buttons, int flags) {
    return al_show_native_message_box(al_get_current_display(), title, heading, content, buttons, flags);
}

int show_error_dialog(char *content) {
    return show_dialog("Erro", "Falha ao lidar com recursos", content, NULL, ALLEGRO_MESSAGEBOX_ERROR);
}

int show_alert_dialog(char *content) {
    return show_dialog("Aviso", "Ação inválida!", content, NULL, ALLEGRO_MESSAGEBOX_WARN);
}

int show_try_again_dialog(char *title) {
    char seq_incorreta[] = "Sequência Incorreta";
    char tentar_novamente[] = "Você não montou a sequência correta de cartas. Deseja tentar novamente desde o início?";
    char bt_sim_nao[] = "Não :(|Sim :)";

    return show_dialog(title, seq_incorreta, tentar_novamente, bt_sim_nao, ALLEGRO_MESSAGEBOX_QUESTION);
}

int show_cond_dialog(char *cond, char *buttons) {
    int valid;
    char titulo[] = "Seleção de Condição";
    char selecione[] = "Selecione uma condição:";

    // Garante que o usuário não vai sair sem definir uma condição.
    do {
        valid = show_dialog(titulo, selecione, cond, buttons, ALLEGRO_MESSAGEBOX_QUESTION);
    } while (valid == 0);

    return valid;
}