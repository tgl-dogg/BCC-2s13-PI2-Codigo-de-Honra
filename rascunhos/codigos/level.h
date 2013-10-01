#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED
#endif // LEVEL_H_INCLUDED

int level(int exp_in, int exp_at, int lvl_at){

	if(lvl_at <= 3){
		if(exp_at >= 2*exp_in){
			printf("Parabens, voce subiu o seu nivel de conhecimento!\nNvl.%d\n", lvl_at+1);
			return lvl_at+1;
		}else
			printf("Lembre-se, nao existe erros, tudo e aprendizado.\nLogo ira subir de nivel\n");
		return lvl_at;
	}

	if(lvl_at <= 6){
		if(exp_at >= 3*exp_in){
			printf("Parabens, voce subiu o seu nivel de conhecimento!\nNvl.%d\n", lvl_at+1);
			return lvl_at+1;
		}else
			printf("Lembre-se, nao existe erros, tudo e aprendizado.\nLogo ira subir de nivel\n");
		return lvl_at;
	}

	if(lvl_at <= 9){
		if(exp_at >= 4*exp_in){
			printf("Parabens, voce subiu o seu nivel de conhecimento!\nNvl.%d\n", lvl_at+1);
			return lvl_at+1;
		}else
			printf("Lembre-se, nao existe erros, tudo e aprendizado.\nLogo ira subir de nivel\n");
		return lvl_at;
	}

	if(lvl_at <= 12){
		if(exp_at >= 5*exp_in){
			printf("Parabens, voce subiu o seu nivel de conhecimento!\nNvl.%d\n", lvl_at+1);
			return lvl_at+1;
		}else
			printf("Lembre-se, nao existe erros, tudo e aprendizado.\nLogo ira subir de nivel\n");
		return lvl_at;
	}
}