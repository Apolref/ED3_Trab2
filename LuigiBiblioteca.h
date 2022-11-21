//
// Created by Luigi
//

#ifndef UNTITLED_LUIGIBIBLIOTECA_H
#define UNTITLED_LUIGIBIBLIOTECA_H

//Coloque os includes usados pela sua ALUNObiblioteca.c aqui
#include <stdio.h>
#include <stdlib.h>
#include "DefaultPrints.h"
#include "funcoesFornecidas.h"

//Declare seus defines, compartilhados entre arquivos aqui
// #define num 10;

//define o tamanho de uma pagina de disco
#define PagDisc 960

//define o valor atibuido ao lixo
#define LIXO '$'

//Declare suas structs, compartilhadas entre arquivos aqui
// typedef struct Exemple_Sruct{
//    char s[20];
//    int x;
//}ex;

//define o formato de um cabecalho
typedef struct Cabecalho{
  char status;
  int topo;
  int proxRRN;
  int nroRegRem;
  int nroPagDisco;
  int qttCompacta;
}Cabecalho;

//define um registro com os valores variaveis em um campo so
typedef struct RegistroDeCopia{
  char removido;
  int encadeamento;
  int idConecta;
  char siglaPais[2];
  int idPoPsConectado;
  char unidadeMedida;
  int  velocidade;
  char  nomePoPsPais[44];//valores variaveis juntos para ocupar espaco fixo
}RegistroDeCopia;



//Declare suas funcoes, compartilhadas entre arquivos aqui
// void exemple_function( int n);

//abre arquivo bianrio para escrita
FILE *OpenWB(char name[]);

//abre arquivo binario para leitura
FILE *OpenRB(char name[]);

//abre arquivo para leitura
FILE *OpenR(char name[]);

//fecha arquivo
void CloseFile(FILE *p);

//Printa uma struct cabecalho em um arquivo
void InicializaCabecalho(FILE *m, Cabecalho Cab);

//le inteiro em formato de char (ate encontrar virgula) e converte para int
int CopiarInt(FILE *p, int *FimDoArq);

//le um char
char CopiarChar(FILE *p, int *FimDoArq);


//le char de uma string e retorna '|' caso ',' 
char CopiarString(FILE *p, int *FimDoArq);


//escreve uma struct registro inteira no arquivo campo a campo
void EscreveRegistro(RegistroDeCopia auxiliar1, FILE *m);

//Le registro e chama funcao de escrever registro
int ReadRegister(FILE *p, FILE *m);

#endif //UNTITLED_LUIGIBIBLIOTECA_H
