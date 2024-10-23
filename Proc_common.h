#pragma once

#include "Machine.h"

struct SPU
{
   el_t* buffer_for_code;
   long n_cmd;
   el_t* register_buffer;
};

const el_t MY_NUMBER = 13;

#define _JUMP_COMMON_(flag_cond, code_op, ... )     \
{                                       \
    if (!flag_cond)                     \
        {                               \
        Jump (code, &ip);               \
        break;                          \
        }                               \
    else                                \
        {                               \
        Stack_Pop (&stk, &a);           \
        Stack_Pop (&stk, &b);           \
                                        \
        if (b code_op a) Jump (code, &ip); \
                                        \
        break;                          \
        }                               \
}                                       \