#include "instructions.h"
#include "parser.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

/*Addresing modes:
    ACC-Accumulator: ex: ABA 1-byte
    IMM: ex: LDAA #$25 loads 25 TO acc A 2-bytes
    DIR: ex: LDAA $25 loads content of mem address 25 2-bytes
    EXT: ex: LDAA $1000 loads content of mem address 1000 3-bytes(1 opcode, 2 for operand)
    IDX: ex: LDAA $10,X loads content of address 1010 after LDX #$1000 loads address 1000 to IR, 
    INH: No Operand needed ex: INCA or DECB
    REL: ex: BRA OFH jumps 0F offset of current address*/
    
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
