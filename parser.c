#include "parser.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

/*enum Instructions{
    
};*/

void init_instruction_flags(InstructionFlags instruction_flags){
    instruction_flags.instruction_fetching = false;
    instruction_flags.instruction_fetched = false;
    instruction_flags.operand_fetching = false;
    instruction_flags.operand_fetched = false;
    instruction_flags.end_instruction = false;
    instruction_flags.label = false;
    instruction_flags.comment = false;
    instruction_flags.error = false;
}

void line_parser(char *buffer, long unsigned buffer_length, InstructionFlags instruction_flags){
    sscanf(buffer, "%4s %8s", instruction_flags.instruction, instruction_flags.operand);
    printf("Instruction: %s; Operand: %s\n", instruction_flags.instruction, instruction_flags.operand);
}

void instruction_checker(char *instruction_nmemo, InstructionFlags instruction_flags){

}
