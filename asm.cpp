#include <stdio.h>
#include <stdlib.h>
#include "Stack_for_proc\Common.h"
#include "asm.h"

int main (int argc, char* argv[])
{
    ASM data_asm = {};

    Check_argc (argc);
    data_asm.nm_orig_f = argv[1];
 
    Open_file (data_asm.nm_orig_f);


    Close_file (data_asm.orig_file);
    return 0;
}
//==================================================================================================
int Open_file (const char* name)
{
    FILE* fp = fopen (name, "rw+");
    if (fp == NULL)
    {
        fprintf (stderr, "Didn't  open the file \"%s\"\n", name);
        return FILE_NULL;
    }
}
//==================================================================================================
int Close_file (FILE* orig_file)
{
    fclose (orig_file);
    return NO_ERROR_;
}
//==================================================================================================
void Check_argc (int argc)
{
    if (argc != 2)
    {
        fprintf (stderr, "Error: the file name was not received");
        exit(1);
    }
}
//==================================================================================================
in