//
// Created by Fernando
//

#include "FernandoBiblioteca.h"

//crie e escreva sua funcao compartilhada entre arquivos aqui
// void exemple_function(){
//     ...
// }
void getHeader(Header *h, FILE *f){ //getting all header fields ignoring trash
    //getting all fields
    fread(&(h->status),sizeof(char),1,f);
    fread(&(h->topo),sizeof(int),1,f);
    fread(&(h->proxRRN),sizeof(int),1,f);
    fread(&(h->nroRegRem),sizeof(int),1,f);
    fread(&(h->nroPagDisco),sizeof(int),1,f);
    fread(&(h->qttCompacta),sizeof(int),1,f);
}

void getRegistry(Registry *r, FILE *f){ //getting all fields from only one registry
    //getting status file
    strcpy(r->nomePoPs,"\0");
    strcpy(r->nomePais,"\0");
    r->idConecta=-1;
    strcpy(r->siglaPais,"\0");
    r->removido='1';
    r->velocidade=-1;
    r->idPoPsConectado=-1;
    r->unidadeMedida='\0';
    r->encadeamento=-1;
    fread(&(r->removido),sizeof(char),1,f);
    if ( r->removido == 1) {// registry logically removed
        int restSize = regSize - (int)(1 * sizeof(char)+1);
        fseek(f,restSize,SEEK_CUR);
        return;
    }

    //getting fields with constant size
    fread(&(r->encadeamento),sizeof(int),1,f);
    fread(&(r->idConecta),sizeof(int),1,f);
    fread(&(r->siglaPais),sizeof(char),2,f);
    fread(&(r->idPoPsConectado),sizeof(int),1,f);
    fread(&(r->unidadeMedida),sizeof(char),1,f);
    fread(&(r->velocidade),sizeof(int),1,f);

    //getting fields with variable size
    int allVarFieldsSize = regSize-(int)(3*sizeof(char)+4*sizeof(int)+1);
    char c[allVarFieldsSize]; //buffer to read all variable fields
    fread(c, sizeof(char), allVarFieldsSize, f);
    //filling buffer
    int selector = 0; //switch which var field will be filled in for(;;) loop
    int count = 0; //count var field filled size
    int i;
    for (i = 0; (i <allVarFieldsSize); ++i) {//coping char by char from buffer to selecter var field. Stops when char = '|'
        if ((c[i] == '|') || (count >= varFieldsMaxSize)) {
            if (selector == 0)
                r->nomePoPs[count] = '\0';
            if (selector == 1)
                r->nomePais[count] = '\0';
            count = 0;
            selector++;
            continue;
        }
        if (selector == 0)
            r->nomePoPs[count] = c[i];
        if (selector == 1)
            r->nomePais[count] = c[i];
        count++;
    }
    printf("");
}

void registryPrint(Registry *r){ //print all not empty and not management of logically removed registry fields
    if ( r->removido == 1)// registry logically removed
        return;

    //checking if registry is not empty and print it
    if (r->idConecta != -1)
        printf("Identificador do ponto: %i\n", r->idConecta);
    if (r->nomePoPs[0] != trash && r->nomePoPs[0] != '\0')
        printf("Nome do ponto: %s\n", r->nomePoPs);
    if (r->nomePais[0] != trash && r->nomePais[0] != '\0')
        printf("Pais de localizacao: %s\n", r->nomePais);
    if (r->siglaPais[0] != trash && r->siglaPais[0] != '\0')
        printf("Sigla do pais: %s\n", r->siglaPais);
    if (r->idPoPsConectado != -1)
        printf("Identificador do ponto conectado: %i\n", r->idPoPsConectado);
    if ((r->idConecta != -1) && (r->velocidade != trash) )
        printf("Velocidade de transmissao: %i %cbps\n", r->velocidade, r->unidadeMedida);
}

int registryConteins(Registry* r, char* field, char* type){ //check if registry contains requested field
    if ( r->removido == 1)// registry logically removed
        return -1;

    //1° find type field
    //2° check if fields is equal as the requested field
    //3º return
    if( r->idConecta == 78 ){}
    if (strcmp(type,"idConecta") == 0){
        if (r->idConecta == (atoi(field)))
            return 1;
    }
    if (strcmp(type,"siglaPais") == 0){
        if (strcmp(r->siglaPais,field)==0)
            return 1;
    }
    if (strcmp(type,"idPoPsConectado") == 0){
        if (r->idPoPsConectado == (atoi(field)))
            return 1;
    }
    if (strcmp(type,"unidadeMedida") == 0){
        if (r->unidadeMedida == field[0])
            return 1;
    }
    if (strcmp(type,"velocidade") == 0){
        if (r->velocidade == (atoi(field)))
            return 1;
    }
    if (strcmp(type,"nomePoPs") == 0){
        if (strcmp(r->nomePoPs,field)==0)
            return 1;
    }
    if (strcmp(type,"nomePais") == 0){
        if (strcmp(r->nomePais,field)==0)
            return 1;
    }
    return 0;
}


