//
// Created by Fernando
//

#ifndef UNTITLED_FERNANDOBIBLIOTECA_H
#define UNTITLED_FERNANDOBIBLIOTECA_H

//Coloque os includes usados pela sua ALUNObiblioteca.c aqui
#include <stdio.h>
#include <string.h>
#include "DefaultPrints.h"
#include "funcoesFornecidas.h"

//Declare seus defines, compartilhados entre arquivos aqui
// #define num 10;
#define inputCharSize 21 //max size to each input file names
#define pageSize 960 // constant page size
#define regSize 64 //constant registry size
#define varFieldsMaxSize 46 //difference between allConstantFieldsSize - allVariableFieldsSize
#define trash '$' //trash char

//Declare suas structs, compartilhadas entre arquivos aqui
// typedef struct Exemple_Sruct{
//    char s[20];
//    int x;
//}ex;
typedef struct HEADER{ //header struct
    char status;
    int topo;
    int proxRRN;
    int nroRegRem;
    int nroPagDisco;
    int qttCompacta;
}Header;

typedef struct REGISTRY{ //registry struct
    char removido; //management of logically removed registry
    int encadeamento; //management of logically removed registry
    int idConecta;
    char siglaPais[2];
    int idPoPsConectado;
    char unidadeMedida;
    int velocidade;
    //theoretically these fields should have variable size, but localities hardly pass the 20 char
    char nomePoPs[varFieldsMaxSize];
    char nomePais[varFieldsMaxSize];
    
}Registry;

//Declare suas funcoes, compartilhadas entre arquivos aqui
// void exemple_function( int n);
void getHeader(Header *h, FILE *f); //getting all header fields ignoring trash

void getRegistry(Registry *r, FILE *f); //getting all fields from only one registry

void registryPrint(Registry *r); //print all not empty and not management of logically removed registry fields

int registryConteins(Registry* r, char* field, char* type); //check if registry contains requested field

#endif //UNTITLED_FERNANDOBIBLIOTECA_H
