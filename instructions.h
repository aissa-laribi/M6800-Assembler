#ifndef __INSTRUCTIONS_H
#define __INSTRUCTIONS_H


#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>


/*typedef struct {
    char mnemo[4];
    uint8_t length;
} Operand; */

typedef struct {
    uint8_t opcode;
    int operand;
    //InstructionSetPtr next;

           /* Opcode of the instruction */
    //Operand mode;       /* Addressing mode*/

} InstructionSet;

#endif