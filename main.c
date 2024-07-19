/*************************************************************************************************************
 * TODOS:                                                                                                    *
 *        #Improve IDX operand type parsing                                                                  *                                                                             *                                                                                                                                                         
 *        #Continue operand value parsing for LDX, REL addressing modes                                      *
 *        #ERROR HANDLING(Wrong syntax, operand exceedings bytes capacity of addressing modes)               *                                   
 *************************************************************************************************************/

#include "instructions.h"
#include "parser.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

    
int main(int args, char **argv){
    printf("Enter assembly file\n");
    char filename[20];
    scanf("%s", filename);
    static char buffer[120];

    static InstructionFlags current_instruction_flag;
    init_instruction_flags(current_instruction_flag);

    FILE *file;

    if((file = fopen(filename, "r+")) == NULL){
        printf("Cannot open  %s\n", filename);
    } else {
        printf("%s successfully opened\n", filename);
        while(!feof(file)){
            //memset(&current_instruction_flag, 0, sizeof(current_instruction_flag));
            if(current_instruction_flag.error){
                fclose(file);
                break;
            }

            if( fgets(buffer, sizeof(buffer), file) != NULL  ){
                line_parser(buffer, current_instruction_flag);
            }
            //Process the line
        }
        fclose(file);
    }
    if(current_instruction_flag.error){
        return 1;
    } else {
        return 0;
    }
}
