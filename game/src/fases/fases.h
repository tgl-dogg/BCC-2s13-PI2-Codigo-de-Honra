#ifndef _FASES_H_
#define _FASES_H_

#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "../geral/cards.h"
#include "../geral/dialog.h"
#include "desafios/desafios.h"
#include "descricao/descricao.h"

int fases_manager();

int fase1_init();
int fase2_init();
int fase3_init();
#endif