#include "file_loader.h"


/* limpa a entrada até encontrar o caracter t. */
void limpa (FILE *entrada, char t) {
    char c;
    do {
        // Verifica se o que foi lido é igual a -1, o que significa que acabou o file.
        if (fscanf(entrada, "%c", &c) == -1) {
            break;
        }
    } while(c != t);
}

/* Carrega os textos de um arquivo de texto e retorna como ponteiro para matriz tridimensional. */
char ***load_file (const char *path) {
    int n, i, j, k;
    char ***txt;
    char c;

    FILE *entrada = fopen(path, "r");
    if(!entrada) {
        fprintf(stderr, "Falha ao carregar o arquivo de texto.\n");
    }

    // Carrega o inteiro inicial que diz quantos textos serão alocados.
    fscanf(entrada, "%d", &n);
    limpa(entrada, '\n');
    
    // Aloca os textos de estrutura fixa (n x 9 x 34).
    txt = matriz_tri(n, 9, 34);
    
    for(i = 0; i < n; i++) {
        for(j = 0; j < 9; j++) {
            for(k = 0; k < 34; k++) {
                // Lê caracter por caracter do file.
                fscanf(entrada, "%c", &c);
                
                if(c == '*'){
                    txt[i][j][k] = '\0';
                    break;
                } else {
                    txt[i][j][k] = c;
                }
            } 
            limpa(entrada, '\n');
        }
    }

    fclose(entrada);
    return txt;
}