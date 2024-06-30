#ifndef PARSER_H
#define PARSER_H
#include <stdbool.h>
#include <stdlib.h>

enum Instructions{
    ABA,
    LDAA,
    LDAB,
};

enum Operands{
    ACC, /*{"ACC", 1};*/
    IMM, /*{"IMM", 2};*/
    IM3, /*{"IM3", 3};*/
    DIR, /*{"DIR", 2};*/
    EXT, /*{"EXT", 3};*/
    IDX, /*{"IDX", 2};*/
    INH, /*{"INH", 1};*/
    REL, /*{"REL", 2};*/
};

typedef struct{
    bool instruction_fetching;
    bool instruction_fetched;
    char instruction[5];
    int  enum_instruction;   
    bool operand_fetching;
    bool operand_fetched;
    char operand[8]; /*The longest operand will be like $FFFF,X*/
    int  enum_operand;  
    bool end_instruction;
    bool label;
    bool comment;
    bool error;
}InstructionFlags;

void init_instruction_flags(InstructionFlags instruction_flags);

void line_parser(char *buffer, InstructionFlags instruction_flags);
void instruction_checker(InstructionFlags instruction_flags);
#endif