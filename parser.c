#include <ctype.h>
#include "instructions.h"
#include "parser.h"
#include <stdbool.h>
#include <stdint.h>
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
    sscanf(buffer, "%5s %8s", instruction_flags.instruction, instruction_flags.operand);
    if(instruction_flags.instruction[strlen(instruction_flags.instruction) - 1] == ';'){
        instruction_flags.instruction[strlen(instruction_flags.instruction) - 1] = '\0';
    }
    InstructionMnemo instruction_mnemo = instruction_checker(instruction_flags);
    //printf("Instruction nmemo: %s and %d\n", instruction_mnemo.instruction_str, instruction_mnemo.instruction_enum );
    InstructionMode instruction_mode = addressing_mode_identifier(instruction_flags, instruction_mnemo);
    if(instruction_mode.mode_enum != ONEBYTE){
        instruction_mode.operand = operand_value_parser(instruction_flags, instruction_mode);
    }
    printf("Instruction %s MODE: %s and operand: %d\n", instruction_mnemo.instruction_str  ,instruction_mode.instruction_str, instruction_mode.operand);
    //InstructionOpcode instruction_opcode = opcode(instruction_mnemo, instruction_mode);
}

InstructionMnemo instruction_checker(InstructionFlags instruction_flags){
    InstructionMnemo instructionmnemo[] = {
        {"UNKNOWN", UNKNOWN},
        {"ABA", ABA},
        {"ADCA", ADCA},
        {"ADCB", ADCB},
        {"ADDA", ADDA},
        {"ADDB", ADDB},
        {"ANDA", ANDA},
        {"ANDB", ANDB},
        {"ASLA", ASLA},
        {"ASLB", ASLB},
        {"ASRA", ASRA},
        {"ASRB", ASRB},
        {"BCC", BCC},
        {"BCS", BCS},
        {"BEQ", BGE},
        {"BGE", BGT},
        {"BHI", BHI},
        {"BITA", BITA},
        {"BITB", BITB},
        {"BLE", BLE},
        {"BLS", BLS},
        {"BLT", BLT},
        {"BMI", BMI},
        {"BNE", BNE},
        {"BPL", BPL},
        {"BRA", BRA},
        {"BSR", BSR},
        {"BVC", BVC},
        {"BVS", BVS},
        {"CBA", CBA},
        {"CLC", CLC},
        {"CLI", CLI},
        {"CLRA", CLRA},
        {"CLRB", CLRB},
        {"CLV", CLV},
        {"CMPA", CMPA},
        {"COMA", COMA},
        {"COMB", COMB},
        {"CPX", CPX},
        {"DAA", DAA},
        {"DECA", DECA},
        {"DECB", DECB},
        {"DES", DES},
        {"DEX", DEX},
        {"EORA", EORA},
        {"EORB", EORB},
        {"INCA", INCA},
        {"INCB", INCB},
        {"INS", INS},
        {"INX", INX},
        {"JMP", JMP},
        {"JSR", JSR},
        {"LDAA", LDAA},
        {"LDAB", LDAB},
        {"LDS", LDS},
        {"LDX", LDX},
        {"LSR", LSR},
        {"NEG", NEG},
        {"NEGA", NEGA},
        {"NEGB", NEGB},
        {"NOP", NOP},
        {"ORAA", ORAA},
        {"ORAB", ORAB},
        {"PSHA", PSHA},
        {"PSHB", PSHB},
        {"PULA", PULA},
        {"PULB", PULB},
        {"ROL", ROL},
        {"ROR", ROR},
        {"RORA", RORA},
        {"RORB", RORB},
        {"SBA", SBA},
        {"SBC", SBC},
        {"SEC", SEC},
        {"SEI", SEI},
        {"SEV", SEV},
        {"STAA", STAA},
        {"STAB", STAB},
        {"STX", STX},
        {"SUBA", SUBA},
        {"SUBB", SUBB},
        {"SWI", SWI},
        {"SBCA", SBCA},
        {"TAB", TAP},
        {"TAP", TAP},
        {"TBA", TBA},
        {"TPA", TPA},
        {"TST", TST},
        {"TSX", TSX},
        {"TXS", TXS},
        {"TSTA", TSTA},
        {"WAI", WAI},
    };
    for(int i = 0; i < 92; i++){
        if(strcmp(instructionmnemo[i].instruction_str, instruction_flags.instruction) == 0){
            return instructionmnemo[i];
        }
    }
    return instructionmnemo[0];
}

InstructionMode addressing_mode_identifier(InstructionFlags instruction_flags, InstructionMnemo instruction_mnemo){
    InstructionMode instructionmode[] = {
        {"UNKNOWN MODE", UNKNOWN_MODE, 0},
        {"ONEBYTE", ONEBYTE, 0},
        {"IMM", IMM, 0},
        {"IDX", IDX, 0},
        {"DIREXT", DIREXT, 0},
        {"REL", REL, 0},
    };
    
    if(strlen(instruction_flags.operand) <= 1){ /*1 if semi-colon separated with a whitespace*/
        return instructionmode[1];
    } else {
        /*Check if the operand contains a comma or X*/
        bool idx = false;
        char* instruction_flagsoperandPtr = instruction_flags.operand;
        while((instruction_flagsoperandPtr = strchr(instruction_flagsoperandPtr, ',')) != NULL ){
            idx = true;
            ++instruction_flagsoperandPtr;
        }
        if(instruction_flags.operand[0] == '#'){
            return instructionmode[2];
        } else if(idx){
            return instructionmode[3];
        } else if(instruction_flags.operand[0] == '$'){
            return instructionmode[4];
        } else if( isxdigit(instruction_flags.operand[0]) && instruction_flags.operand[0] == 'B' && instruction_mnemo.instruction_enum != BITA && instruction_mnemo.instruction_enum != BITB) {
            return instructionmode[5];
        } else if( isdigit(instruction_flags.operand[0]) ){
            return instructionmode[5];
        } else {
            printf("Invalid Operand\n");
        }
    }
    return instructionmode[0];
}
int operand_value_parser(InstructionFlags instruction_flags, InstructionMode instruction_mode){
    int operand_value = 0;
    switch((int) instruction_mode.mode_enum){
        case IMM:
            if(instruction_flags.operand[1] == '$'){
                //HEX
                int bytes = 1;
                if(  ( isxdigit(instruction_flags.operand[2]) && isxdigit(instruction_flags.operand[3] ) )  && ( (!isxdigit(instruction_flags.operand[4]) && !isxdigit(instruction_flags.operand[5]) ) )){
                    bytes = 1;
                    char value[3] = "00";
                    value[0] = instruction_flags.operand[2];
                    value[1] = instruction_flags.operand[3]; 
                    value[2] = '\0';                
                    operand_value = strtol(value, NULL, 16);
                    return operand_value;
                    break;
                } else if(  ( isxdigit(instruction_flags.operand[2]) && isxdigit(instruction_flags.operand[3] ) )  && ( (isxdigit(instruction_flags.operand[4]) && isxdigit(instruction_flags.operand[5]) ) )){
                    bytes = 2;
                    char value[5] = "0000";
                    value[0] = instruction_flags.operand[2];
                    value[1] = instruction_flags.operand[3]; 
                    value[2] = instruction_flags.operand[4];
                    value[3] = instruction_flags.operand[5];
                    value[4] = '\0';
                    operand_value = strtol(value, NULL, 16);
                    return operand_value;
                    break;
                } 
            } else if(isdigit(instruction_flags.operand[1])){
                //DEC
                operand_value = atoi(instruction_flags.operand + 1); // +1 Skip the '#' character
                printf("MODE IMM AND OPERAND VALUE is %i\n", operand_value);
                return operand_value;
                break;
            } else {
                printf("Invalid operand\n");
                break;
            }
        case DIREXT:
            if(instruction_flags.operand[0] == '$'){
                int bytes = 1;
                if(  ( isxdigit(instruction_flags.operand[1]) && isxdigit(instruction_flags.operand[2] ) )  && ( (!isxdigit(instruction_flags.operand[3]) && !isxdigit(instruction_flags.operand[4]) ) )){
                    bytes = 1;
                    char value[3] = "00";
                    value[0] = instruction_flags.operand[1];
                    value[1] = instruction_flags.operand[2]; 
                    value[2] = '\0';                
                    operand_value = strtol(value, NULL, 16);
                    return operand_value;
                    break;
                } else if(  ( isxdigit(instruction_flags.operand[1]) && isxdigit(instruction_flags.operand[2] ) )  && ( (isxdigit(instruction_flags.operand[3]) && isxdigit(instruction_flags.operand[4]) ) )){
                    bytes = 2;
                    char value[5] = "0000";
                    value[0] = instruction_flags.operand[1];
                    value[1] = instruction_flags.operand[2]; 
                    value[2] = instruction_flags.operand[3];
                    value[3] = instruction_flags.operand[4];
                    value[4] = '\0';
                    operand_value = strtol(value, NULL, 16);
                    return operand_value;
                    break;
                }
            } else if(isdigit(instruction_flags.operand[0])){
                operand_value = atoi(instruction_flags.operand);
                return operand_value;
                break;
            } else {
                printf("ERROR INVALID OPERAND\n");
                break;
                }        
    }
    return operand_value;

} 

