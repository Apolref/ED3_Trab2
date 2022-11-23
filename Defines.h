#include <stdio.h>
#include <stdlib.h>

#define LIXO '$'
#define PagDisc 73

typedef struct IndexCabecalho{
  char  status;
  int  noRaiz;
  int  nroChavesTotal;
  int  alturaArvore;
  int  RRNproxNo;
}IndexCabecalho;

typedef struct IndexRegistro{
 char folha;
  int nroChavesNo;
  int alturaNo;
  int RRNdoNo;
  int P1;
  int C1;
  int PR1;
  int P2;
  int C2;
  int PR2;
  int P3;
  int C3;
  int PR3;
  int P4;
  int C4;
  int PR4;
  int P5;
}IndexRegistro;

typedef struct DadosCabecalho{
  char status;
  int topo;
  int proxRRN;
  int nroRegRem;
  int nroPagDisco;
  int qttCompacta;
}Cabecalho;

typedef struct DadosRegistro{
  char removido;
  int encadeamento;
  int idConecta;
  char siglaPais[2];
  int idPoPsConectado;
  char unidadeMedida;
  int  velocidade;
  char  nomePoPsPais[44];
}Registro;
