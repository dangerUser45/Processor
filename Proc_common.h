#pragma once

#include "Machine.h"

struct SPU
{
   el_t* buffer_for_code;
   size_t num_of_read_item;

   long n_cmd;

   stack_t stk = {};
   el_t* register_buffer;
};

const el_t MY_NUMBER = 13;
const size_t NUM_REGS = 8;

#define _JUMP_COMMON_(flag_cond, code_op, ... ) \
{                                       \
    if (!flag_cond)                     \
        {                               \
        Jump (code, &ip);               \
        break;                          \
        }                               \
    else                                \
        {                               \
        Stack_Pop (stk, &a);           \
        Stack_Pop (stk, &b);           \
                                        \
        if (int(b) code_op int(a)) Jump (code, &ip); \
                                        \
        break;                          \
        }                               \
}                                       
