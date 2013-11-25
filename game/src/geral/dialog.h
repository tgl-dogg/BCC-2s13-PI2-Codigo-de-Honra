#ifndef _DIALOG_H_
#define _DIALOG_H_

#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

/* Retorna 0 em erro, 1 caso clique no botão 1 ou 2 caso clique no botão 2. */

int show_alert_dialog(char *content);
int show_try_again_dialog(char *title);
int show_cond_dialog(char *cond, char *buttons);
int show_dialog(char *title, char *heading, char *content, char *buttons, int flags);

#endif
