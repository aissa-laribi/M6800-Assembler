#include "instructions.h"
#include "parser.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

/*Adressing modes
Operand ACC = {"ACC", 1};
Operand IMM = {"IMM", 2};
Operand IM3 = {"IM3", 3};
Operand DIR = {"DIR", 2};
Operand EXT = {"EXT", 3};
Operand IDX = {"IDX", 2};
Operand INH = {"INH", 1};
Operand REL = {"REL", 2};*/

/*construct_instruction(Instruction, Operand){
    switch(Instruction){
        case ABA:
            if(Operand )
    }
}*/

InstructionOpcode opcode(InstructionMnemo mnemo, InstructionMode mode){
    //In decimal
    InstructionOpcode instructionopcode[] = {
        { {"ABA", ABA}, {"ONEBYTE", ONEBYTE, 0}, 27},
        { {"LDAA", LDAA}, {"IMM", IMM}, 134 },
    };

}