/*
    |   NOME DO ALUNO                               |   NUSP        |   PARTICIPACAO    |
    |   Alexandre Lopes Ferreira Dias dos Santos    |   11801199    |   100%            |
    |   Luigi Quaglio                               |   11800563    |   100%            |
    |   Fernando Rosalini Calaza                    |   11231965    |   100%            |
*/

#include <stdio.h>
#include "Functionally1.h"
#include "Functionally2.h"
#include "Functionally3.h"
#include "Functionally4.h"
#include "Functionally5.h"
#include "Functionally6.h"
#define cmd_size 20


int main() {
    int command;
    char file_name[cmd_size+1];//+1 to '\0'

    //geting input
    scanf("%d", &command);
    scanf("%s",file_name);
    //choosing between functionalities
    switch(command){
        case 1:
            //functionality 1 by Luigi
            char file_nameW[cmd_size+1];//+1 to '\0'

            //geting input
            scanf("%s",file_nameW);
            functionality_1(file_name, file_nameW);
            break;

        case 2:
            //functionality 2 by Alexandre
            functionality_2(file_name);
            break;

        case 3:
            // functionality 3 by Fernando
            functionality_3(file_name);
            break;
        case 4:
            //functionality 4 by Fernando
            functionality_4(file_name);
            break;

        case 5:
            //functionality 5 by Alexandre
            functionality_5(file_name);
            break;

        case 6:
            //functionality 6 by Luigi
            functionality_6(file_name);
            break;

        default:
            return (127);//error code to "command not found"
    }

    return 0;//code to "program executed successfully"
}
