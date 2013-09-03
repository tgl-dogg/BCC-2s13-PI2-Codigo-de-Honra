#ifndef CARDS_H_INCLUDED
#define CARDS_H_INCLUDED

#define ATACAR 1
#define MOVER 2
#define COLETAR_ITEM 3
#define REPETICAO 4
#define USAR_ITEM 5

// Valida o primeiro nível.
// Recebe como parâmetro v[] (o vetor de escolhas do usuário)
// length (tamanho do vetor)
// seq[] (vetor com a sequência correta
// try (tentativa de validação (de 0 até encontrar um erro, ou chegar no fim do vetor)

int validar_nivel_1(int v[], int length, int seq[], int try){
  if(try == length){
    return 1;
  }
  if(v[try] == seq[try]){
    return validar_nivel_1(v, length, seq, try+1);
  }else{
    switch(v[try]){
      case ATACAR:
      printf("\nAtacar e sempre bom, mas talvez voce esteja se precipitando. Tente se organizar para que voce ataque todos os monstros repetidamente antes de fazer qualquer acao.");
      return 0;
              
      case MOVER:
      printf("\nOps, voce se moveu no momento errado! Tente derrotar os monstros primeiro e ver quais itens eles estavam carregando.");
      return 0;
              
      case COLETAR_ITEM:
      printf("\nNao ha itens disponiveis para coletar. Talvez voce tenha que derrotar alguns monstros antes.");
      return 0;
              
      case USAR_ITEM:
      printf("\nAinda nao e hora para utilizar itens. Tente derrotar os monstros e se mover ate o outro lado da sala primeiro.");
      return 0;
              
      case REPETICAO:
      printf("\nAparentemente voce esta tentando repetir a acao errada. Tente analisar em qual situacao seria mais interessante repetir uma acao e tente novamente.");
      return 0;
    }
  }
}
#endif // CARDS_H_INCLUDED
