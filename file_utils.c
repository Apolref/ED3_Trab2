#include <stdio.h>
#include <stdlib.h>
#include "file_utils.h"

FILE *OpenWB(char name[]) { return fopen(name, "wb"); }

FILE *OpenRB(char name[]) { 
  FILE *p;
  p = fopen(name, "rb");
  if(p == NULL){
    printf("Falha no processamento do arquivo");
    exit(0);
  }
  return p; 
}

void CloseFile(FILE *p) { fclose(p); }