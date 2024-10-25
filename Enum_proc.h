#pragma once

enum CMD 
{
    HLT      = -1,
    PUSH     =  1,
    POP      =  2,
    ADD      =  3,
    SUB      =  4,
    MUL      =  5,
    DIV      =  6,
    JMP      =  7,
    JA       =  8,
    JB       =  9,
    JAE      =  10,
    JBE      =  11,
    JE       =  12,
    JHE      =  13,
    OUT_     =  14,
    IN__     =  15,
    SQRT     =  16, 
    SIN      =  17,
    COS      =  18,
    DUMP     =  19,
    PUSH_REG =  20,
    POP_REG  =  21,
};
