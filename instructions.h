#ifndef __INSTRUCTIONS_H
#define __INSTRUCTIONS_H

#include "parser.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>


/*typedef struct {
    char mnemo[4];
    uint8_t length;
} Operand; */
typedef struct{
    InstructionMnemo mnemo;
    InstructionMode mode;
    int result;
} InstructionOpcode; 

InstructionOpcode opcode(InstructionMnemo mnemo, InstructionMode mode);

#endif