#include "parser.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

void init_instruction_flags(InstructionFlags instruction_flags){
    instruction_flags.opcode_fetching = false;
    instruction_flags.opcode_fetched = false;
    instruction_flags.operand_fetching = false;
    instruction_flags.operand_fetched = false;
    instruction_flags.end_instruction = false;
    instruction_flags.label = false;
    instruction_flags.comment = false;
    instruction_flags.error = false;
}

void line_parser(char *buffer, long unsigned buffer_length, InstructionFlags instruction_flags){

}    
