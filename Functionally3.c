//
// Created by Fernando
//

#include "Functionally3.h"

void functionality_3(char* file_name){
    Header h; //readed header
    Registry r; //readed regitry

    //geting count (number of searchs to be done) from input
    int count;//number of search to be done
    getchar();// ignoring char ' ' (blank space)
    count = getchar()-'0';//casting

    //geting field to be searched from input
    //using two string 1d array (char 2d array) to get the all "count" search arguments
    char type[count][inputCharSize];// type of atribute. ex: nomePoPs
    char field[count][inputCharSize];// value of atribute. ex: Zagreb
    int n; // auxiliary variable
    char c; // auxiliary variable
    for(int i=0; i<count; i++) {
        scanf("%s", type[i]);//getting type
        //getting value (or "field")
        if( (strcmp(type[i],"siglaPais")==0) || (strcmp(type[i],"nomePoPs")==0) || (strcmp(type[i],"nomePais")==0) )//saving string
            scan_quote_string(field[i]);//getting field and saving
        else if( (strcmp(type[i],"unidadeMedida")==0) ){//casting char to string and saving
            getchar();// ignoring char '"'
            getchar();// ingnorin char ' ' (blank space)
            scanf("%c", &c);//getting field
            field[i][0]=c;//saving
            field[i][1]='\0';// never forget the '\0'
        }else {//casting int to string and saving
            getchar();// ignoring char ' ' (blank space)
            scanf("%d", &n);//getting field
            //itoa (n,field[i],10);//saving
            sprintf(field[i],"%d",n);
        }
    }

    FILE* f = fopen(file_name, "rb");// |Q: read? write? If file doest exist?|    |A: Yes! No! Doesn't create new file, it returns NULL!|
    //checking if fopen worked (or file existence)
    if( f==NULL ){
        printf("\n");
        print_non_existent_file();
        printf("\n");
        return;
    }

    //getting header
    getHeader(&h, f);

    //verify file status
    if( h.status == '0' ){
        printf("Falha no processamento do arquivo.\n"); 
        return;
    }

    //changing file status to 0
    fseek(f, 0, SEEK_SET);
    h.status='0';
    fwrite(&(h.status) , sizeof(char) , 1 , f);
    fseek(f, pageSize, SEEK_SET);

    //searching "count" times
    int flag = 0;// used to print "registry atributes" or "registry missing"
    int j;
    for(int i=0; i<count; i++) {//'i'  is number of seach done
        printf("Busca %i\n", i+1);
        //((h.nroPagDisco-1) * pageSize/regSize)
        for ( j= 0; j <= (h.proxRRN-1); j++) {//'j' is number of readed regitry (RRN)
            getRegistry(&r, f);
            if ( (r.removido == '0') && (registryConteins(&r, field[i], type[i]) == 1) ) {//checking if registry has the required attribute
                registryPrint(&r);
                printf("\n");
                flag = 1;
            }
        }
        if ( flag == 0 ){ // registry missing (none registry satisfied the search)
            print_no_registry_meets_the_requirement();
            printf("\n\n");
        }
        flag = 0;
        fseek(f, pageSize, SEEK_SET);
        if((j*regSize)%pageSize == 0)
            printf("Numero de paginas de disco: %d\n\n", 1+((j*regSize)/pageSize));//counting extra page, page is not full
        else
            printf("Numero de paginas de disco: %d\n\n", 2+((j*regSize)/pageSize));//counting normally, page is full
    }

    //changing file status to 1
    fseek(f, 0, SEEK_SET);
    h.status='1';
    fwrite(&(h.status) , sizeof(char) , 1 , f);

    fclose(f);
}
