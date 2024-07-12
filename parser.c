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
    sscanf(buffer, "%4s %8s", instruction_flags.instruction, instruction_flags.operand);
    printf("Instruction: %s Operand: %s\n", instruction_flags.instruction, instruction_flags.operand);
    InstructionMnemo instruction_mnemo = instruction_checker(instruction_flags);
    printf("Instruction nmemo: %s and %d\n", instruction_mnemo.instruction_str, instruction_mnemo.instruction_enum );
    InstructionMode instruction_mode = addressing_mode_identifier(instruction_flags);
    printf("Instruction MODE: %s and %d\n", instruction_mode.instruction_str, instruction_mode.mode_enum );
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
        {"CLR", CLR},
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
    for(int i = 0; i < 2; i++){
        if(strcmp(instructionmnemo[i].instruction_str, instruction_flags.instruction) == 0){
            printf("Instruction list: %s and %d\n", instructionmnemo[i].instruction_str, instructionmnemo[i].instruction_enum );
            return instructionmnemo[i];
        }
    }
    return instructionmnemo[0];
}

InstructionMode addressing_mode_identifier(InstructionFlags instruction_flags){
    InstructionMode instructionmode[] = {
        {"UNKNOWN MODE", UNKNOWN_MODE},
        {"ONEBYTE", ONEBYTE},
        {"ACC", ACC},
        {"IMM", IMM},
        {"DIR", DIR},
        {"EXT", EXT},
        {"IDX", IDX},
        {"INH", INH},
        {"REL", REL},
    };
    
    if(strlen(instruction_flags.operand) == 0){
        return instructionmode[1];
    }
    return instructionmode[0];
}