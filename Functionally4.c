//
// Created by Fernando
//

#include "Functionally4.h"

void functionality_4(char *file_name)
{
    Header h;                          // readed header
    FILE *f = fopen(file_name, "rb+"); // |Q: read? write? If file doest exist?|    |A: Yes! Yes! Doesn't create new file, it returns NULL!|
    char trashStr[122] = "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$";

    // checking if fopen worked (or file existence)
    if (f == NULL)
    {
        printf("\n");
        print_non_existent_file();
        printf("\n");
        return;
    }

    // getting header
    getHeader(&h, f);

    // verify file status
    if (h.status == '0')
    {
        printf("\n");
        print_non_existent_file();
        printf("\n");
        return;
    }

    // changing file status to 0
    fseek(f, 0, SEEK_SET);
    h.status = '0';
    fwrite(&(h.status), sizeof(char), 1, f);
    fseek(f, pageSize, SEEK_SET);

    // geting count (number of searchs to be done) from input
    int count;               // number of search to be done
    getchar();               // ignoring char ' ' (blank space)
    count = getchar() - '0'; // casting

    // geting field to be searched from input
    // using two string 1d array (char 2d array) to get the all "count" search arguments
    char type[count][inputCharSize];  // type of atribute. ex: nomePoPs
    char field[count][inputCharSize]; // value of atribute. ex: Zagreb
    int n;                            // auxiliary variable
    char c;                           // auxiliary variable
    for (int i = 0; i < count; i++)
    {
        scanf("%s", type[i]); // getting type
        // getting value (or "field")
        if ((strcmp(type[i], "siglaPais") == 0) || (strcmp(type[i], "nomePoPs") == 0) || (strcmp(type[i], "nomePais") == 0)) // saving string
            scan_quote_string(field[i]);                                                                                     // getting field and saving
        else if ((strcmp(type[i], "unidadeMedida") == 0))
        {                       // casting char to string and saving
            getchar();          // ignoring char '"'
            getchar();          // ingnorin char ' ' (blank space)
            scanf("%c", &c);    // getting field
            field[i][0] = c;    // saving
            field[i][1] = '\0'; // never forget the '\0'
        }
        else
        {                    // casting int to string and saving
            getchar();       // ignoring char ' ' (blank space)
            scanf("%d", &n); // getting field
            sprintf(field[i], "%d", n);
        }
    }

    // searching and removing "count" times
    Registry r; // readed regitry
    for (int i = 0; i < count; i++)
    { //'i'  is number of seach done
        int j;
        for (j = 0; j <= (h.proxRRN - 1); j++)
        { //'j' is number of readed registry (RRN)
            getRegistry(&r, f);
            if ((r.removido == '0') && (registryConteins(&r, field[i], type[i]) == 1))
            { // checking if registry has the required attribute
                // updating primary memory
                r.encadeamento = h.topo; // update registry.encadeamento
                h.topo = j;              // update header.Topo
                r.removido = '1';        // update registry.removido
                // updating secondary memory
                fseek(f, pageSize + ((j)*regSize), SEEK_SET);
                fwrite(&(r.removido), sizeof(char), 1, f);    // update header.Topo
                fwrite(&(r.encadeamento), sizeof(int), 1, f); // update header.Topo
                // fill registry with trash
                for (int k = 0; k < regSize - 4 * sizeof(int) - 4 * sizeof(char); ++k)
                    fwrite(trashStr, sizeof(char), 1, f);
                fseek(f, pageSize + (regSize * (j + 1)), SEEK_SET);
                h.nroRegRem++;
            }
        }
        fseek(f, pageSize, SEEK_SET);
    }

    // updating header
    fseek(f, 1 * sizeof(char), SEEK_SET);
    fwrite(&(h.topo), sizeof(int), 1, f); // update header.Topo
    fseek(f, 1 * sizeof(char) + 2 * sizeof(int), SEEK_SET);
    fwrite(&(h.nroRegRem), sizeof(int), 1, f); // update header.nroRegRem

    // changing file status to 1
    fseek(f, 0, SEEK_SET);
    h.status = '1';
    fwrite(&(h.status), sizeof(char), 1, f);

    fclose(f);

    // printing BinarioNaTela
    binarioNaTela(file_name);
}