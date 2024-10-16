#include "Proc_run.h"
#include "Stack_for_proc\Common.h"
#include "Stack_for_proc\Stack.h"

void Run ()
{


}
//==================================================================================================
int Load_code (const char* name, int* buffer, size_t size)
{
    FILE* code_text = fopen (argv[1], "r");
    for (int i =0; i < size; ++i)
        fscanf (code_text, "%d", &buffer[i]);
    return NO_ERROR_;
}