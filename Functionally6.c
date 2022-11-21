//
// Created by Luigi
//

#include "Functionally6.h"
#include "LuigiBiblioteca.h"
#include "AlexandreBiblioteca.h"
#include <string.h>

// compacta arquivo
void functionality_6(char *ArquivoASerLido)
{

  FILE *p;
  p = OpenRB(ArquivoASerLido); // abre binario para leitura

  // armazena o primeiro campo para evitar arq corrompidos
  char ifCorrompido;
  fread(&ifCorrompido, sizeof(char), 1, p);

  if (ifCorrompido == '0')
  {                                               // checa status
    printf("Falha no processamento do arquivo."); // se corrompido printa erro
    exit(0);
  }

  Cabecalho Cab; // inicia struct cabecalho

  // iniciar valores da struct cabecalho
  Cab.status = '0'; // status de corrompido
  // copia o resto do arquivo de leitura
  fread(&Cab.topo, sizeof(int), 1, p);
  fread(&Cab.proxRRN, sizeof(int), 1, p);
  fread(&Cab.nroRegRem, sizeof(int), 1, p);
  fread(&Cab.nroPagDisco, sizeof(int), 1, p);
  fread(&Cab.qttCompacta, sizeof(int), 1, p);

  if (Cab.nroRegRem == 0){                      // se nao ha removidos ja esta compacto
    CloseFile(p);                               // fecha arquivo
    p = fopen(ArquivoASerLido, "rb+");          // abre o arquivo para leitura e escrita
    Cab.qttCompacta++;                          // uma vez mais foi compactado
    fseek(p, 16, SEEK_SET);                     // posicao da qqtCompacta
    fwrite(&Cab.qttCompacta, sizeof(int), 1, p); // incrementa no cabecalho
    CloseFile(p);                               // fecha arquivo novamente
    binarioNaTela(ArquivoASerLido);
    return;
  }

  char newName[100];                // arquivo temporario
  strcpy(newName, ArquivoASerLido); // nome igual ao antigo
  newName[0]++;                     // altera a primeira letra do nome para serem arquivos diferentes ex binario = cinario

  // abre arquivo de copia para escrita
  FILE *m;
  m = OpenWB(newName);

  // escreve cabecalho no novo arquivo com status 0
  InicializaCabecalho(m, Cab);

  fseek(p, PagDisc, SEEK_SET); // ponteiro pula o cabecalho no arquivo de leitura

  int n = Cab.proxRRN; // proxRRN coincide com numero de registros
  Cab.proxRRN = 0;     // reset proximoRRN para incrementar no novo arquivo

  // le arquivo inteiro e conta o numero de registros lidos
  for (int i = 0; i < n; i++)
  {

    // Conta numero de registros e chama a funcao de leitura
    Cab.proxRRN += ReadRegister(p, m);
  }

  // retorna para o inicio do arquivo para escrever cabecalho atualizado
  fseek(m, 0, SEEK_SET);
  Cab.qttCompacta++;                      // compactado mais uma vez
  Cab.status = '1';                       // status indicando que tudo deu certo até aqui
  Cab.nroPagDisco = Cab.proxRRN / 15 + 1; // calcula paginas de disco (cabecalho + 1 para cada 15 regs)
  if (Cab.proxRRN % 15 != 0)
  { // mais uma pagina nao cheia
    Cab.nroPagDisco += 1;
  }
  Cab.topo = -1;               // topo vira -1 pois nao tem mais pilha
  Cab.nroRegRem = 0;           // nao ha mais regs removidos
  InicializaCabecalho(m, Cab); // printa cabecalho inteiro

  // fecha arquivos
  CloseFile(p);
  CloseFile(m);
  // deleta arquivo nao compactado
  remove(ArquivoASerLido);
  // renomeia arquivo compactado para nome antigo
  rename(newName, ArquivoASerLido);

  binarioNaTela(ArquivoASerLido);
  return;
}
