void novaTela() {
	int largura = 800;
	int altura = 600;

	ALLEGRO_DISPLAY *novaJanela = NULL;

	novaJanela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if (!novaJanela){
        fprintf(stderr, "Falha ao criar display!\n");
        return -1;
    }

    al_set_window_position(novaJanela, (disp_data.width-LARGURA_TELA)/2, (disp_data.height-ALTURA_TELA)/2);
}