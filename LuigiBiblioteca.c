//
// Created by Luigi.
//

#include "LuigiBiblioteca.h"

// crie e escreva sua funcao compartilhada entre arquivos aqui
//  void exemple_function(){
//      ...
//  }
//#include "Lib.h"

// abre arquivo binario para escrita
FILE *OpenWB(char name[]) { return fopen(name, "wb"); }

// abre arquivo binario para leitura
FILE *OpenRB(char name[])
{
  FILE *p;
  p = fopen(name, "rb");

  // caso falha ao encontrar arquivo print mensagem de erro
  if (!p)
  {
    printf("Falha no processamento do arquivo.");
    exit(0);
  }

  return p;
}

// abre arquivo para leitura
FILE *OpenR(char name[])
{
  FILE *p;
  p = fopen(name, "r");

  // caso falha ao encontrar arquivo print mensagem de erro
  if (!p)
  {
    printf("Falha no processamento do arquivo.");
    exit(0);
  }

  return p;
}

// fecha arquivo
void CloseFile(FILE *p) { fclose(p); }

// Printa uma struct cabecalho em um arquivo
void InicializaCabecalho(FILE *m, Cabecalho Cab)
{
  // Escreve os campos do cabecalho em ordem
  fwrite(&Cab.status, sizeof(char), 1, m);
  fwrite(&Cab.topo, sizeof(int), 1, m);
  fwrite(&Cab.proxRRN, sizeof(int), 1, m);
  fwrite(&Cab.nroRegRem, sizeof(int), 1, m);
  fwrite(&Cab.nroPagDisco, sizeof(int), 1, m);
  fwrite(&Cab.qttCompacta, sizeof(int), 1, m);

  char aux = LIXO; // auxilia a impressao de lixo no arquivo

  // preenche o resto da pagina de disco com lixo
  for (int i = 21; i < PagDisc; i++)
  {
    fwrite(&aux, sizeof(char), 1, m);
  }
}

// le inteiro em formato de char (ate encontrar virgula) e converte para int
int CopiarInt(FILE *p, int *FimDoArq)
{
  char Charlido = ' ';                  // quando for virgula parara a leitura
  int aux = 0;                          // inteiro auxiliar para armazenar valor lido
  fread(&Charlido, sizeof(char), 1, p); // le um char

  // Contador para o fim do arquivo
  //(decremento para dizer que mais um byte foi lido)
  *FimDoArq -= 1;

  // enquanto o campo nao acabar (, ou \n indicando fim)
  // ou o arquivo não terminar Fimdoarquivo==0
  while (Charlido != ',' && Charlido != '\n' && *FimDoArq != 0)
  {
    if (Charlido > 47 && Charlido < 58)
    { // Se for um inteiro
      // já que um numero foi lido como char ele é transformado em um inteiro ('0' = 48 ACCI)
      aux += Charlido - 48;

      // leitura e decremento do tamanho do arquivo
      fread(&Charlido, sizeof(char), 1, p);
      *FimDoArq -= 1;

      aux *= 10; // Translação para ler a proxima casa decimal
    }
    else
    {
      // se nao for um intiero le ate achar um evitando campos corrompidos e cabecalho csv
      while (Charlido < '0' || Charlido > '9')
      {
        // leitura e decremento do tamanho do arquivo
        fread(&Charlido, sizeof(char), 1, p);
        *FimDoArq -= 1;
      }
    }
  }

  if (aux == 0)
  {            // caso nao leia nenhum inteiro
    return -1; // retorna campo vazio
  }
  // como foi multiplicado por 10 uma vez a mais retorna dividido
  return aux / 10;
}

// le um char
char CopiarChar(FILE *p, int *FimDoArq)
{
  char aux; // auxilia leitura de char

  // leitura e decremento do tamanho do arquivo
  fread(&aux, sizeof(char), 1, p);
  *FimDoArq -= 1;
  // retorna char lido
  return aux;
}

// le char de uma string e retorna '|' caso ','
char CopiarString(FILE *p, int *FimDoArq)
{
  char aux; // auxilia leitura

  // leitura e decremento do tamanho do arquivo
  fread(&aux, sizeof(char), 1, p);
  *FimDoArq -= 1;

  if (aux == ',')
  { // caso ',' retorna '|'
    aux = '|';
  }
  return aux;
}

// escreve uma struct registro inteira no arquivo campo a campo
void EscreveRegistro(RegistroDeCopia auxiliar1, FILE *m)
{
  // char removido
  fwrite(&auxiliar1.removido, sizeof(char), 1, m);

  // int encadeamento
  fwrite(&auxiliar1.encadeamento, sizeof(int), 1, m);

  // int idConecta
  fwrite(&auxiliar1.idConecta, sizeof(int), 1, m);

  // char siglaPais[2]
  fwrite(&auxiliar1.siglaPais[0], sizeof(char), 1, m);
  fwrite(&auxiliar1.siglaPais[1], sizeof(char), 1, m);

  // int idPoPsConectado
  fwrite(&auxiliar1.idPoPsConectado, sizeof(int), 1, m);

  // char unidadeMedida
  fwrite(&auxiliar1.unidadeMedida, sizeof(char), 1, m);

  // int velocidade
  fwrite(&auxiliar1.velocidade, sizeof(int), 1, m);

  // char nomePoPsPais[44]
  for (int i = 0; i < 44; i++)
  {
    fwrite(&auxiliar1.nomePoPsPais[i], sizeof(char), 1, m);
  }
  return;
}

// Le registro e chama funcao de escrever registro
int ReadRegister(FILE *p, FILE *m)
{
  RegistroDeCopia RegisAtual; // inicia um registro

  fread(&RegisAtual.removido, sizeof(char), 1, p); // le se o registro foi removido

  if (RegisAtual.removido == '0')
  { // caso o registro nao esteja removido

    fread(&RegisAtual.encadeamento, sizeof(int), 1, p); // le o encademamento se foi removido

    fread(&RegisAtual.idConecta, sizeof(int), 1, p); // armazena a idconecta do registro atual

    fread(&RegisAtual.siglaPais[0], sizeof(char), 1, p); // armazena a siglaPais do registro atual
    fread(&RegisAtual.siglaPais[1], sizeof(char), 1, p); // armazena a siglaPais do registro atual

    fread(&RegisAtual.idPoPsConectado, sizeof(int), 1, p); // armazena a idPoPsConectado do registro atual

    fread(&RegisAtual.unidadeMedida, sizeof(char), 1, p); // armazena a unidadeMedida do registro atual

    fread(&RegisAtual.velocidade, sizeof(int), 1, p); // armazena a velocidade do registro atual

    for (int i = 0; i < 44; i++)
    {
      fread(&RegisAtual.nomePoPsPais[i], sizeof(char), 1, p); // armazena os dois campos variaveis na struct
    }

    // escreve o registro no arquivo
    EscreveRegistro(RegisAtual, m);

    // retorna 1 pois um arquivo foi escrito
    return 1;
  }
  else
  { // caso registro removido pula para o proximo
    fseek(p, 63, SEEK_CUR);

    // retorna 0 pois nenhum registro foi esccrito
    return 0;
  }
}