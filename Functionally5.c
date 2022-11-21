//
// Created by Alexandre
//

#include "Functionally5.h"

void LerCabecalho(FILE *fd, Cabecalho *Cab)
{
  // Escreve os campos do cabecalho

  fread(&Cab->status, sizeof(char), 1, fd);
  fread(&Cab->topo, sizeof(int), 1, fd);
  fread(&Cab->proxRRN, sizeof(int), 1, fd);
  fread(&Cab->nroRegRem, sizeof(int), 1, fd);
  fread(&Cab->nroPagDisco, sizeof(int), 1, fd);
  fread(&Cab->qttCompacta, sizeof(int), 1, fd);
}

void WriteChar(FILE *p, Registro *RegisAtual)
{
  char aux = 'c'; // inicializacao generica para um char
  int i = 0, j = 0;

  if (strcmp(RegisAtual->nomePoPs, "") != 0)
  {
    while (aux != '|')
    { // armazena a informação atual no vetor campo[]
      aux = RegisAtual->nomePoPs[i];
      if ((aux < 'A' || aux > 'z') && aux != ' ')
      {
        aux = '|';
      }
      fwrite(&aux, sizeof(char), 1, p);
      i++;
    }
    aux = 'c';
  }
  else
  {
    RegisAtual->nomePoPs[0] = '|';
    fwrite(&RegisAtual->nomePoPs[0], sizeof(char), 1, p);
    i++;
  }
  if (strcmp(RegisAtual->nomePais, "") != 0)
  {
    while (aux != '|')
    { // armazena a informação atual no vetor campo[]
      aux = RegisAtual->nomePais[j];
      if ((aux < 'A' || aux > 'z') && aux != ' ')
      {
        aux = '|';
      }
      fwrite(&aux, sizeof(char), 1, p);
      j++;
    }
  }
  else
  {
    RegisAtual->nomePais[0] = '|';
    fwrite(&RegisAtual->nomePais[0], sizeof(char), 1, p);
    j++;
  }

  aux = LIXO;
  for (int z = 0; z < (44-i-j); i++){
    fwrite(&aux, sizeof(char), 1, p);
  }
}

int ConvertePraInt(char a[])
{
  int aux = 0;
  int i = 0; // inteiro auxiliar para armazenar valor lido
  // enquanto o campo nao acabar (\0 ou \n indicando fim)
  // ou o arquivo não terminar Fim do arquivo==0
  if (a[0] == 'N' || a[0] == 'n')
  {
    return -1;
  }
  while (a[i] != '\0' && a[i] != '\n')
  {
    if (a[i] > 47 && a[i] < 58)
    { // Se não for um inteiro
      // já que um numero foi lido como char ele é transformado em um inteiro ('0' = 48 ACCI)
      aux += a[i] - 48;
      aux *= 10;
      i++;
    }
  }
  return aux / 10;
}

void InserirNoFinal(FILE *fd){
  Registro RegisAtual;
  int auxIntNulos = -1;
  char auxConversor[44];
  char aux2 = '0';
  char lixo = LIXO;

  // scanf nas entradas
  scanf("%s", auxConversor);
  RegisAtual.idConecta = ConvertePraInt(auxConversor);
  scan_quote_string(RegisAtual.nomePoPs);
  scan_quote_string(RegisAtual.nomePais);
  scan_quote_string(RegisAtual.siglaPais);
  scanf("%s", auxConversor);
  RegisAtual.idPoPsConectado = ConvertePraInt(auxConversor);
  scan_quote_string(RegisAtual.unidadeMedida);
  scanf("%s", auxConversor);
  getchar();
  RegisAtual.velocidade = ConvertePraInt(auxConversor);

  // fwrite
  fwrite(&aux2, sizeof(char), 1, fd);                // escreve o campo 'removido'
  fwrite(&auxIntNulos, sizeof(int), 1, fd);                 // escreve o campo 'encadeamento'
  fwrite(&RegisAtual.idConecta, sizeof(int), 1, fd); // escreve o campo 'idconecta'
  if (strcmp(RegisAtual.siglaPais, "") != 0){ // confere se a string passada é NULA
    fwrite(&RegisAtual.siglaPais[0], sizeof(char), 1, fd); // escreve o campo 'siglapais'
    fwrite(&RegisAtual.siglaPais[1], sizeof(char), 1, fd); // escreve o campo 'siglapais'
  } else{
    fwrite(&lixo, sizeof(char), 1, fd); // coloca lixo se for nulo
    fwrite(&lixo, sizeof(char), 1, fd); // coloca lixo se for nulo
  }

  fwrite(&RegisAtual.idPoPsConectado, sizeof(int), 1, fd); // escreve o campo 'idPoPsConectado'
  if (strcmp(RegisAtual.unidadeMedida, "") != 0){ // confere se a string passada é NULA
    fwrite(&RegisAtual.unidadeMedida[0], sizeof(char), 1, fd); // escreve o campo 'unidade medida'
  } else{
    fwrite(&lixo, sizeof(char), 1, fd); // coloca lixo se for nulo
  }
  fwrite(&RegisAtual.velocidade, sizeof(int), 1, fd); // escreve o campo 'velocidade'

  WriteChar(fd, &RegisAtual); // escreve os campos de tamanho variavel
}

void InserirNaPilha(FILE *fd, Cabecalho *Cab){
  Registro RegisAtual;
  int novoTopo; // variavel auxiliar que armazena o novo topo
  int auxIntNulos = -1; // variavel auxiliar para inteiros nulos
  char aux2 = '0'; // variavel axuliar para primeiro campo "removido"
  char lixo = LIXO; // '$'
  char auxConversor[44];

  // scanf nas entradas
  scanf("%s", auxConversor); //le o inteiro como string e o converte depois
  RegisAtual.idConecta = ConvertePraInt(auxConversor);
  scan_quote_string(RegisAtual.nomePoPs);
  scan_quote_string(RegisAtual.nomePais);
  scan_quote_string(RegisAtual.siglaPais);
  scanf("%s", auxConversor); //le o inteiro como string e o converte depois
  RegisAtual.idPoPsConectado = ConvertePraInt(auxConversor);
  scan_quote_string(RegisAtual.unidadeMedida);
  scanf("%s", auxConversor); //le o inteiro como string e o converte depois
  getchar(); // pega o \n no fim da velocidade
  RegisAtual.velocidade = ConvertePraInt(auxConversor);

  // FWRITES
  fwrite(&aux2, sizeof(char), 1, fd);   // escreve o campo 'removido'
  fread(&novoTopo, sizeof(int), 1, fd); // novoTopo recebe o encadeamento
  fseek(fd, -4, SEEK_CUR); // volta os espaços lidos do int
  fwrite(&auxIntNulos, sizeof(int), 1, fd);                 // escreve o campo 'encadeamento'
  fwrite(&RegisAtual.idConecta, sizeof(int), 1, fd); // escreve o campo 'idconecta'

  if (strcmp(RegisAtual.siglaPais, "") != 0){ // confere se a string passada é NULA
    fwrite(&RegisAtual.siglaPais[0], sizeof(char), 1, fd); // escreve o campo 'siglapais'
    fwrite(&RegisAtual.siglaPais[1], sizeof(char), 1, fd); // escreve o campo 'siglapais'
  } else{
    fwrite(&lixo, sizeof(char), 1, fd); // coloca lixo se for nulo
    fwrite(&lixo, sizeof(char), 1, fd); // coloca lixo se for nulo
  }

  fwrite(&RegisAtual.idPoPsConectado, sizeof(int), 1, fd); // escreve o campo 'idPoPsConectado'

  if (strcmp(RegisAtual.unidadeMedida, "") != 0){ // confere se a string passada é NULA
    fwrite(&RegisAtual.unidadeMedida[0], sizeof(char), 1, fd); // escreve o campo 'unidade medida'
  } else{
    fwrite(&lixo, sizeof(char), 1, fd); // coloca lixo se for nulo
  }

  fwrite(&RegisAtual.velocidade, sizeof(int), 1, fd); // escreve o campo 'velocidade'
  WriteChar(fd, &RegisAtual);                         // escreve os campos de tamanho variavel

  // atualiza o topo
  Cab->topo = novoTopo;
}

void functionality_5(char *file){
  int n; // quantos registros serão inserido
  FILE *fd; 
  Cabecalho Cab; // inicialização struct cabecalho
  scanf("%d", &n); // le o numero de inserções
  getchar(); // tira o \n da entrada

  fd = fopen(file, "rb+"); // abre o arquivo para leitura e escrita

  if (fd == NULL)  { // erro ao abrir o arquivo
    printf("Falha no processamento do arquivo.");
    exit(0);
  }

  LerCabecalho(fd, &Cab); // le o cabecalho atual do arquivo e o armazena na struct Cabecalho

  if (Cab.status == '0'){ // checa status
    printf("Falha no processamento do arquivo.");
    exit(0);
  }

  Cab.status = '0'; // arquivo corrompido pois esta em uso
  fseek(fd, 0, SEEK_SET); // volta pro inicio para escrever status 0
  fwrite(&Cab.status, sizeof(char), 1, fd);

  for (int i = 0; i < n; i++){
    if (Cab.topo == -1){// Nenhum registro removido
      fseek(fd, (Cab.proxRRN * 64) + 960, SEEK_SET); // offset da origem ate o final do ultimo registro
      InserirNoFinal(fd);
      Cab.proxRRN++; // + 1 para o prox rrn
    }else{// topo != -1
      fseek(fd, (Cab.topo * 64) + 960, SEEK_SET); // vai pro topo da pilha
      InserirNaPilha(fd, &Cab);
      Cab.nroRegRem--; // numero de registro removido diminui 1 a cada um inserido
    }
  }

  Cab.status = '1';
  Cab.nroPagDisco = Cab.proxRRN / 15 + 1; // calcula paginas de disco (cabecalho + 1 para cada 15 regs)
  if (Cab.proxRRN % 15 != 0){ // mais uma pagina nao cheia
    Cab.nroPagDisco += 1;
  }

  fseek(fd, 0, SEEK_SET);
  InicializaCabecalho(fd, Cab); // atualiza cabeçalho ao fim da execução
  fclose(fd);

  binarioNaTela(file);
}