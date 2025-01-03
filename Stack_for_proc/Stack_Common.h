#pragma once 

//#include <stdio.h>
#include <assert.h>

#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#define STACK_DEBUG 1   

#if  (STACK_DEBUG == 1)
    #define ONDEBUG( ... ) __VA_ARGS__
    #define STACK_CTOR(Data, capacity) Stack_Ctor (Data, capacity, #Data, __FILE__, __LINE__)
    #define CHECK(code1, code2) { int error = Verificator (Data); Decoder_error (Data, error, __LINE__, code2);  if (error != 0) {code1;}}
    #define ASSERT_ {if (Data == NULL) return BAD_POINTER;      \
                     if (Data -> buffer == NULL) return BUFFER_NULL;}
#else
    #define ONDEBUG( ... )
    #define STACK_CTOR(Data, capacity) Stack_Ctor (Data, capacity)
    #define CHECK(code1, code2)
    #define ASSERT_ 
#endif

/*#define qwe
#ifdef qwe
#define HASH(const void* ptr, size_t size)      \
({                                              \
    uint_t hash = 5381;                         \
    const char * data = (char*) ptr;            \
    for (uint_t i = 0; i < size; ++i)           \
        hash = hash * 33 ^ data[i];             \
    hash;                                       \
})                                              \
#endif
*/

#define DIE ({ assert(0); 0; })
#define OR == 0 or

enum code_error
    {
        ERROR__          =     -1,
        NO_ERROR_        = (0<<0),
        BUFFER_NULL      = (1<<0),
        BAD_SIZE         = (1<<1),
        BAD_CAPACITY     = (1<<2),
        FILE_NULL        = (1<<3),
        BAD_CANARY1_S    = (1<<4),
        BAD_CANARY2_S    = (1<<5),
        BAD_CANARY1_B    = (1<<6),
        BAD_CANARY2_B    = (1<<7),
        GENERAL_ERROR    = (1<<8),
        BAD_POINTER      = (1<<9),
        BAD_HASH_STRUCT  = (1<<10),
        BAD_HASH_BUF     = (1<<11)
    };

typedef double stack_el_t;
typedef long long unsigned int uint_t;
const stack_el_t POISON = -666;
const stack_el_t CANARY_B = -123401234;
const stack_el_t CANARY_S = 77777777;

const int MAGIC_NUM = 2;

struct stack_t
{
    ONDEBUG(stack_el_t canary1_struct;)
    ONDEBUG(const char* name;)
    ONDEBUG(const char* file;)
    ONDEBUG(int line;)
    


    stack_el_t* buffer;
    ssize_t size;
    ssize_t capacity;
    ONDEBUG(uint_t hash_struct;)
    ONDEBUG(uint_t hash_buffer;)
    ONDEBUG(stack_el_t canary2_struct;)
};

#endif
