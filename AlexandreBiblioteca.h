//
// Created by Alexandre
//

#ifndef UNTITLED_ALEXANDREBIBLIOTECA_H
#define UNTITLED_ALEXANDREBIBLIOTECA_H

//Coloque os includes usados pela sua ALUNObiblioteca.c aqui
#include <stdio.h>
#include <stdlib.h>
#include "DefaultPrints.h"
#include "funcoesFornecidas.h"
#include "LuigiBiblioteca.h"

//Declare seus defines, compartilhados entre arquivos aqui
// #define num 10;

//Declare suas structs, compartilhadas entre arquivos aqui
// typedef struct Exemple_Sruct{
//    char s[20];
//    int x;
//}ex;

//define um registro com campos variaveis separados
typedef struct Registro{
  char removido;
  int encadeamento;
  int idConecta;
  char siglaPais[3];
  int idPoPsConectado;
  char unidadeMedida[2];
  int  velocidade;
  char  nomePoPs[44];
  char nomePais[44];
}Registro;


//Declare suas funcoes, compartilhadas entre arquivos aqui
// void exemple_function( int n);
void ReadChar(FILE *p, Registro *RegisAtual);
void LerRegistro(FILE *fd);
void ImprimirRegistro(Registro RegisAtual);
#endif //UNTITLED_ALEXANDREBIBLIOTECA_H
