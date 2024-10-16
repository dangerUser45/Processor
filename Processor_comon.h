#include "Stack_for_proc\Common.h"
enum CMD {
    hlt  = -1,
    push =  1,
    pop  =  2,
    add  =  3,
    mul  =  4,
    div  =  5

};

struct ASM  
{
    FILE* orig_file;
    FILE* final_file;
    size_t size_of_file;
};