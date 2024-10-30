#pragma once

#include "Machine.h"
#include "Stack_for_proc\Stack_Common.h"

struct SPU
{
   el_t* buffer_for_code;
   size_t num_of_read_item;

   long n_cmd;
   int ip;

   stack_t stk = {};
   el_t* register_buffer;
};

const el_t MY_NUMBER = 13;
const size_t NUM_REGS = 9;

#define _JUMP_COMMON_(flag_cond, code_op, ... ) \
{                                       \
    if (!flag_cond)                     \
        {                               \
        Jump (code, &IP);               \
        break;                          \
        }                               \
    else                                \
        {                               \
        Stack_Pop (stk, &a);           \
        Stack_Pop (stk, &b);           \
                                        \
        if (int(b) code_op int(a)) Jump (code, &IP); \
                                        \
        break;                          \
        }                               \
}       

struct CMD_INFO {
       const char* name_cmd;
       bool numb_arg;
    };