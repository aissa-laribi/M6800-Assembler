#include "parser.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

void init_instruction_flags(InstructionFlags instruction_flags){

    instruction_flags.instruction_fetched = false;
    instruction_flags.operand_fetching = false;
    instruction_flags.operand_fetched = false;
    instruction_flags.end_instruction = false;
    instruction_flags.label = false;
    instruction_flags.comment = false;
    instruction_flags.error = false;
}

void line_parser(char *buffer, InstructionFlags instruction_flags){
    sscanf(buffer, "%4s %8s", instruction_flags.instruction, instruction_flags.operand);
    printf("Instruction: %s; Operand: %s\n", instruction_flags.instruction, instruction_flags.operand);
    instruction_checker(instruction_flags);
}

void instruction_checker(InstructionFlags instruction_flags){
    if(strcmp("LDAA", instruction_flags.instruction) == 0){
        instruction_flags.enum_instruction = LDAA;
        printf("Enum Instruction: %d\n", instruction_flags.enum_instruction);
    } else if(strcmp("LDAB", instruction_flags.instruction) == 0){
        instruction_flags.enum_instruction = LDAB;
        printf("Enum Instruction: %d\n", instruction_flags.enum_instruction);
    } else {
        printf("Unknown instruction %s\n", instruction_flags.instruction);
    }
}

void addressing_identifier(){

}
