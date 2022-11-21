//
// Created by Alexandre
//

#include "AlexandreBiblioteca.h"

//crie e escreva sua funcao compartilhada entre arquivos aqui
// void exemple_function(){
//     ...
// }

void ReadChar(FILE *p, Registro *RegisAtual){
  char aux = 'c';//inicializacao generica para um char
  int i = 0, j = 0;

  while(aux != '|'){ // armazena a informação atual no vetor campo[]
    fread(&aux, sizeof(char), 1, p);
    RegisAtual->nomePoPs[i] = aux;
    i++;
  }
  RegisAtual->nomePoPs[i-1] = '\0'; // recebe o \0
  aux = 'c';

  while(aux != '|'){// armazena a informação atual no vetor campo[]
    fread(&aux, sizeof(char), 1, p);
    RegisAtual->nomePais[j] = aux; 
    j++;
  }
  RegisAtual->nomePais[j-1] = '\0'; // recebe o \0
  fseek(p, (44-i-j), SEEK_CUR); // vai para a posicao do proximo registro
}

void ImprimirRegistro(Registro RegisAtual){

  //int idConecta
  printf("Identificador do ponto: %d\n", RegisAtual.idConecta);

  //char  nomePoPsPais[]
  if (RegisAtual.nomePoPs[0] != '\0'){
    printf("Nome do ponto: %s\n",RegisAtual.nomePoPs);
  }

  //char nomePais[]
  if (RegisAtual.nomePais[0] != '\0'){
  printf("Pais de localizacao: %s\n", RegisAtual.nomePais);
  }

  //char siglaPais[2]
  if (RegisAtual.siglaPais[0] != '$'){
    printf("Sigla do pais: %s\n", RegisAtual.siglaPais);
  }

  //int idPoPsConectado
  if (RegisAtual.idPoPsConectado != -1){
  printf("Identificador do ponto conectado: %d\n", RegisAtual.idPoPsConectado);
  }

  //int  velocidade e char unidadeMedida
  if (RegisAtual.velocidade!=-1 && RegisAtual.unidadeMedida[0]!= '$'){  // velocidade e uni.medida nao nulos
    printf("Velocidade de transmissao: %d %sbps\n", RegisAtual.velocidade, RegisAtual.unidadeMedida);
  } else if(RegisAtual.velocidade!=-1){ // velocidade nao nula
    printf("Velocidade de transmissao: %d\n", RegisAtual.velocidade);
  }

  return;
}



void LerRegistro(FILE *fd){
  Registro RegisAtual;
  
  fread(&RegisAtual.removido, sizeof(char),1, fd); // le se o registro foi removido
  
  if (RegisAtual.removido == '0'){

    fread(&RegisAtual.encadeamento, sizeof(int),1, fd); // le o encademamento se foi removido

    fread(&RegisAtual.idConecta, sizeof(int),1,fd);  //armazena a idconecta do registro atual
    
    fread(&RegisAtual.siglaPais, sizeof(char),2,fd);  //armazena a siglaPais do registro atual
    RegisAtual.siglaPais[2] = '\0'; // coloca um \0 no final do elemento para printalo como string posteriormente
    
    fread(&RegisAtual.idPoPsConectado, sizeof(int),1,fd); //armazena a idPoPsConectado do registro atual
    
    fread(&RegisAtual.unidadeMedida, sizeof(char),1,fd); //armazena a unidadeMedida do registro atual
    RegisAtual.unidadeMedida[1] = '\0';// coloca um \0 no final do elemento para printalo como string posteriormente

    fread(&RegisAtual.velocidade, sizeof(int),1,fd); //armazena a velocidade do registro atual
    
    ReadChar(fd,&RegisAtual); // armazena os dois campos variaveis na struct
    
    ImprimirRegistro(RegisAtual); // imprime o registro atual

    printf("\n"); 
  } else {
    fseek(fd, 63, SEEK_CUR); // se o registro está removido, o programa o pula com fseek
  }
}