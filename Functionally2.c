//
// Created by Alexandre
//

#include "Functionally2.h"
#include "LuigiBiblioteca.h"

void functionality_2(char file_name[21]){
  FILE *fd; //file descriptor
  Registro *RegisAtual; // declara um registro

  fd = fopen(file_name, "rb");

  if (fd == NULL){ // erro ao abrir o arquivo
    printf("Falha no processamento do arquivo.");
    exit(0);
  }

  char ifCorrompido; // testa o status
  fread(&ifCorrompido, sizeof(char), 1, fd);
  if (ifCorrompido == '0'){ // checa status
    printf("Falha no processamento do arquivo.");
    exit(0);
  }

  int aux = 'c'; // inicialização generica de char
  int pag, numRegis; // variaveis que armazenaram o numero de registros ede pagians de disco

  fseek(fd, 0, SEEK_END); 

  numRegis = (ftell(fd) - 960) / 64; // calculo de quantos registros o arquivo tem - os registros do cabeçalho;

  if (ftell(fd) % 960 != 0){ // calculo do numero de pag de disco
    pag = (ftell(fd) / 960) + 1; // resto da divisao diferente de zero, portanto uma pagina a mais
  } else {
    pag = (ftell(fd) / 960); // resto da divisao igual a zero
  }

  if (numRegis == 0){
    printf("Registro inexistente.\n\n"); // mensagem de erro para nenhum registro
  } else {
    fseek(fd, 960, SEEK_SET); // ponteiro posicionado no começo do registro de dados

    for (int i = 0; i < numRegis; i++){ // le as informações
      LerRegistro(fd);
    }
  }

  printf("Numero de paginas de disco: %d\n\n", pag); // Numero paginas de disco

  fclose(fd); // fecha o arquivo
}