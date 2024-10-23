#include "Machine.h"

#include <string.h>
#include <stdio.h>

#include "Stack_for_proc\Stack_Common.h"

#include "Proc_common.h"
#include "Proc_run.h"


void Run ()
{


}
//==================================================================================================
int Load_code (SPU* data_proc, FILE* code_text, el_t* buffer, size_t size)
{

    char temp_buf [50] = "";
    el_t temp_value = 0;
    if (fscanf (code_text, "%s", temp_buf) != 1)             return GENERAL_ERROR;
    if (strcmp (temp_buf, "MMD"))                            return GENERAL_ERROR;
    if (fscanf (code_text, "%lf", &temp_value) != 1)         return GENERAL_ERROR;  // !!! if change type of element you need change %lf
    if ((long) temp_value != (long) MY_NUMBER)                             return GENERAL_ERROR;
    fscanf (code_text, "%lf", &temp_value);                                //fill n_cmd
    data_proc -> n_cmd = long (temp_value);

    for (size_t i =0; i < size; ++i) 
        if (fscanf (code_text, "%lf", &buffer[i]) == EOF) // !!! if change type of element you need change %lf
            break;
    return NO_ERROR_;
}
//==================================================================================================
int Dump_proccessor (SPU* data_proc)
{
    for (int i = 0; i < data_proc -> n_cmd; ++i)
    fprintf (Log_File, "%lf", data_proc -> buffer_for_code [i]);

    return NO_ERROR_;
}