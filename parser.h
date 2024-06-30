#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct{
    bool instruction_fetching;
    bool instruction_fetched;
    char instruction[5];
    bool operand_fetching;
    bool operand_fetched;
    char operand[8]; /*The longest operand will be like $FFFF,X*/
    bool end_instruction;
    bool label;
    bool comment;
    bool error;
}InstructionFlags;

void init_instruction_flags(InstructionFlags instruction_flags);

void line_parser(char *buffer, long unsigned buffer_length, InstructionFlags instruction_flags);
#endif