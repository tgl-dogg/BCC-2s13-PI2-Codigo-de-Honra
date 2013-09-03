#include <stdio.h>
#include "cards.h"
#include "level.h"

// Caso existisse mais de uma "sequência correta", poderíamos ter mais vetores seq[]
// e a comparação seria feita if(v[try] == seq1[try] || v[try] == seq2[try]) e assim por diante.
// Não se assustem com lista dinâmica nem alocação de memória, dá pra fazer de uma maneira mais simples (por enquanto). 
int main(){
    int v[20];
    int seq[] = {REPETICAO, ATACAR, COLETAR_ITEM, MOVER, USAR_ITEM};
    int scan, i;
    int novo_level = 0;
    int exp_in=0, exp_at=0, new_lvl=0; //aumento de nivel! quanto maior, mais dificil fica os codigos.
    
    // Strings para introduzir o usuario no jogo
    char intro[] =   "Ola guerreiro. Voce esta em uma sala com 20 monstros. Precisa derrotar os monstros, pegar a chave que eles guardam, atravessar a sala, abrir a porta e sair daqui.";
    char options[] = "Suas cartas sao:\n\n1. Carta de ataque unico\n2. Carta de movimentacao\n3. Carta de coletar item\n4. Carta de repeticao\n5. Carta de utilizar item.\n\n";
    char usuario[] = "Digite o numero das cartas cartas que deseja utilizar, e -1 quando ja tiver escolhido todas. \n"; 
    
    printf("%s %s %s", intro, options, usuario);
    
    // Inicializa o vetor
    for(i = 0; i < 20; i++){
          v[i] = -1;
    }
    
    // Faz a leitura das escolhas do usuário.
    for(i = 0; i < 20; i++){
          scanf("%d", &scan);
          
          v[i] = scan;
          // Cancela as escolhas no -1 (sinal de pare)
          if(scan == -1){
                  break;
          }
    }
    
    // recebe o resultado da tentativa
    novo_level = validar_nivel_1(v, i, seq, 0);    
    
    // resultado == 1, a sequência estava correta.
    if(novo_level == 1){
      printf("\nParabens, voce passou de nivel!\n");
      exp_at = exp_in + 5;
    } else {
      printf("\nParece que nao foi dessa vez! Repense seu conjunto de instrucoes e tente novavmente.\n");
      exp_at = exp_in + 1;
    }
    level(exp_in,exp_at,new_lvl);
    fflush(stdin);
    getchar();
    return 0;
}

// Ah, e curtam essa música também, curto pra caralho:
// http://www.youtube.com/watch?v=hnYsErYrCS8
