#ifndef PARSER_H
#define PARSER_H
#include "instructions.h"
#include <stdbool.h>
#include <stdlib.h>

typedef enum {
    ABA, ADCA, ADCB, ADDA, ADDB, ANDA, ANDB, ASLA, ASLB, ASRA, ASRB,
    BCC, BCS, BEQ, BGE, BGT, BHI, BITA, BITB, BLE, BLS,
    BLT, BMI, BNE, BPL, BRA, BSR, BVC, BVS,
    CBA, CLC, CLI, CLRA, CLRB, CLV, CMPA, CMPB, COMA, COMB, CPX,
    DAA, DECA, DECB, DES, DEX,
    EORA, EORB,
    INCA, INCB, INS, INX, 
    JMP, JSR,   
    LDAA, LDAB, LDS, LDX, LSR, /*TEST LSRA on hippy*/
    NEG, NEGA, NEGB, NOP,
    ORAA, ORAB, /*Double check on hippy*/
    PSHA, PSHB, PULA, PULB,
    ROL, ROR, RTI, RTS, RORA, RORB,
    SBA, SBC, SEC,SEI,SEV, STAA, STAB, STS, STX, SUBA, SUBB, SWI, SBCA,
    TAB, TAP, TBA, TPA, TST, TSX, TXS, TSTA,
    WAI,
    UNKNOWN,
} InstructionEnum;

typedef struct {
    char *instruction_str;
    InstructionEnum instruction_enum;
} InstructionMnemo;

typedef enum {
    UNKNOWN_MODE,
    ONEBYTE, /*ACC or INH depending on instruction*/
    IMM, /*{"IMM", 2 OR 3} ;*/
    DIREXT, /*{"DIR", 2} OR {"EXT", 3};*/
    IDX, /*{"IDX", 2};*/
    REL, /*{"REL", 2};*/
} ModeEnum;

typedef struct {
    char *instruction_str;
    ModeEnum mode_enum;
    int operand;
} InstructionMode;

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
InstructionMnemo instruction_checker(InstructionFlags instruction_flags);
bool is_mem_address_prefix(char *operand);
InstructionMode addressing_mode_identifier(InstructionFlags instruction_flags, InstructionMnemo instruction_mnemo);
int operand_value_parser(InstructionFlags instruction_flags, InstructionMode instruction_mode);
#endif