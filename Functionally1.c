//
// Created by Luigi
#include "Functionally1.h"
#include "funcoesFornecidas.h"
#include "LuigiBiblioteca.h"

void functionality_1(char *ArquivoASerLido, char *ArquivoASerEscrito)
{
  // Abre arquivo de leitura
  FILE *p;
  p = OpenRB(ArquivoASerLido);

  // Abre arquivo binario para escrita
  FILE *m;
  m = OpenWB(ArquivoASerEscrito);

  Cabecalho Cab;            // inicia struct de cabecalho
  RegistroDeCopia auxiliar; // inicia struct de registro
  char RecebeChar = ',';    // auxilia a leitura de chars do arquivo
  int flagpalavra = 0;      // flag para ver se uma palavra inteira foi lida
  int tamanhoArquivo;       // Contador que decrementa ate zero indicando fim do arquivo

  // iniciar struct cabecalho
  Cab.status = '0'; // inicia-se com '0' para indicar caso erro
  Cab.topo = -1;
  Cab.proxRRN = 0;
  Cab.nroRegRem = 0;
  Cab.nroPagDisco = 0;
  Cab.qttCompacta = 0;

  InicializaCabecalho(m, Cab); // escreve a struct cabecalho no arquivo
  Cab.nroPagDisco += 1;        // o cabecalho ocupa uma pag de disco

  // inicia a struct registro
  // char removido;
  auxiliar.removido = '0'; // inicia com '0', pois nao ha removidos

  // int encadeamento;
  auxiliar.encadeamento = -1; //-1 pois nao ha removidos

  // decobrir tamanho do arquivo de leitura
  fseek(p, 0, SEEK_END);
  tamanhoArquivo = ftell(p);

  fseek(p, 0, SEEK_SET); // retorna o ponteiro para o inicio do arquivo

  //Caso nao haja dados no csv
  if(tamanhoArquivo > 85){
    while (tamanhoArquivo > 0)
    { // enquanto arquivo nao acabar

      // leitura dos campos da struct registro
      // int idConecta;
      auxiliar.idConecta = CopiarInt(p, &tamanhoArquivo); // retorna um inteiro lido

      // char  nomePoPsPais[44];
      for (int j = 0; j < 44; j++)
      { // tamanho de 44 caracteres
        if (flagpalavra == 2)
        {

          // se ler duas virgulas completa com lixo
          RecebeChar = LIXO;
        }
        else
        {
          RecebeChar = CopiarString(p, &tamanhoArquivo); // retorna um char (caso ',' retorna '|')
          if (RecebeChar == '|')
          {
            // se le pipe = terminou uma palavra
            flagpalavra++;

            if (auxiliar.nomePoPsPais[j - 1] == ' ')
            {

              // retira um espaco extra que apareca no fim de uma string
              j--; // ao decrementar o pipe e escrito no lugar do espaco
            }
          }
        }

        auxiliar.nomePoPsPais[j] = RecebeChar;
      }
      // reinicia contador de palavras
      flagpalavra = 0;

      // char siglaPais[2];
      RecebeChar = CopiarChar(p, &tamanhoArquivo); // retorna um char

      if (RecebeChar == ',')
      {
        // se virgula - campo vazio preenchido com lixo
        auxiliar.siglaPais[0] = LIXO;
        auxiliar.siglaPais[1] = LIXO;
      }
      else
      {
        // se nao char lido vai para a posicao 0 e le-se a segunda letra da sigla
        auxiliar.siglaPais[0] = RecebeChar;
        auxiliar.siglaPais[1] = CopiarChar(p, &tamanhoArquivo);

        // le virgula no final da sigla
        fread(&RecebeChar, sizeof(char), 1, p);
        tamanhoArquivo--; // decrementa o contador para indicar fim do arquivo
      }

      // int idPoPsConectado;
      auxiliar.idPoPsConectado = CopiarInt(p, &tamanhoArquivo); // le intiero no arquivo

      // char unidadeMedida
      RecebeChar = CopiarChar(p, &tamanhoArquivo); // le um char

      if (RecebeChar == ',')
      {
        // caso campo vazio preenche com lixo
        auxiliar.unidadeMedida = LIXO;
      }
      else
      {
        auxiliar.unidadeMedida = RecebeChar;
        // le virgula
        fread(&RecebeChar, sizeof(char), 1, p);
        tamanhoArquivo--; // contador de fim
      }
      // int  velocidade;
      auxiliar.velocidade = CopiarInt(p, &tamanhoArquivo); // le inteiro

      // escreve o registro inteiro no arquivo de escrita
      EscreveRegistro(auxiliar, m);
      Cab.proxRRN += 1; // um registro foi lido entao o proximo RRN aumenta
    }
  }

  // atualiza cabecalho
  Cab.status = '1';                    // arquivo nao corrompido se chegar ate aqui
  Cab.nroPagDisco += Cab.proxRRN / 15; // 1 pag de disco = 15 regs e o proximo RRN e = ao numero de regs

  if (Cab.proxRRN % 15 != 0)
  { // pag de disco adicional nao cheia
    Cab.nroPagDisco += 1;
  }

  fseek(m, 0, SEEK_SET);       // retorna ponteiro do arquivo de escrita para inicio
  InicializaCabecalho(m, Cab); // escreve o cabecalho atualizado

  // fechamento dos arquivos
  CloseFile(p);
  CloseFile(m);

  binarioNaTela(ArquivoASerEscrito);
}