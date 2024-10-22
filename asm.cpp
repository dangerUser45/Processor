#include "..\SuperLibs\TXLib.h"
#include "Stack_for_proc\Common.h"
#include "Asm.h"
#include "Onegin_for_proc\Onegin_processing.h"
#include "Onegin_for_proc\Onegin_General.h"
#include "Onegin_for_proc\Print.h"
#include "Stack_for_proc\Debug.h"
#include "Processor_common.h"

int main (int argc, char* argv[])
{   
    ASM data_asm = {};
    ONEGIN onegin_data = {};

    Create_file ("ASM_LOG.txt");    //создал log_file
    Check_argc (argc);

    onegin_data.name = argv[1];
    onegin_data.fsize = file_size (argv[1]);
    Check_fsize (onegin_data.fsize);

    data_asm.nm_orig_f = argv[1];

    Read_File (&onegin_data); 
    DBG_Print (&onegin_data);

    Strings_Number (&onegin_data);
    Address_String (&onegin_data);

    DBG_Print (&onegin_data);

    Asm_Ctor (&data_asm, onegin_data.string_quantity);                                                                                            
    Processing_Command (&data_asm, onegin_data.str_data, onegin_data.string_quantity);
    Dump (&data_asm, &onegin_data);

    Close_file (Log_File);
    Asm_Dtor (&data_asm.mem_cmd);
    return 0;
}
//==================================================================================================
int Processing_Command (ASM* data_asm, STRING* str_data, long size)
{
    el_t* mem_cmd = data_asm -> mem_cmd;
    char temp_string [20] = {};
    el_t temp_value = 0;

    long i = 0;
    long line = 0;
    
    while (line < size)
    {   
        int cnt_rd_sym= 0;

        sscanf (str_data[line].str_addr, "%s%n", temp_string, &cnt_rd_sym);
        sscanf (str_data[line].str_addr + cnt_rd_sym, "%lf", &temp_value);
        ++line;

        fprintf (Log_File, "%ld)Temp_string = %s\n",line, temp_string);
        fprintf (Log_File, "Temp_value = %lf\n", temp_value);

        if (strcmp (temp_string, "hlt") == 0)
        {
            mem_cmd[i++] = (el_t) HLT;
        }

        if (strcmp (temp_string, "push") == 0)
        {
            mem_cmd[i++] = (el_t) PUSH;
            mem_cmd[i++ ] = (el_t) temp_value;
        }

        if (strcmp (temp_string, "pop") == 0)
        {
            mem_cmd[i++] = (el_t) POP;
            mem_cmd[i++] = (el_t) temp_value;
        }

        if (strcmp (temp_string, "add") == 0)
        {
            mem_cmd[i++] = (el_t) ADD;
            //записать в массив
        }

        if (strcmp (temp_string, "mul") == 0)
        {
            mem_cmd[i++] = (el_t) MUL;   
            //записать в массив
        }
        
        if (strcmp (temp_string, "div") == 0)
        {
            mem_cmd[i++] = (el_t) DIV;   
            //записать в массив
        }
        if (strcmp (temp_string, "jmp") == 0)
        {
            mem_cmd[i++] = (el_t) JMP;
            mem_cmd[i++] = (el_t) temp_value;
             
        }

        if (strcmp (temp_string, "ja") == 0)
        {
            mem_cmd[i++] = (el_t) JA;
            mem_cmd[i++] = (el_t) temp_value;
             
            //записать в массив
        }

        if (strcmp (temp_string, "jb") == 0)
        {
            mem_cmd[i++] = (el_t) JB;
            mem_cmd[i++]  = (el_t) temp_value;
             
            //записать в массив
        }

        if (strcmp (temp_string, "jae") == 0)
        {
            mem_cmd[i++] = (el_t) JAE;
            mem_cmd[i++] = (el_t) temp_value;
             
            //записать в массив
        }

        if (strcmp (temp_string, "jbe") == 0)
        {
            mem_cmd[i++] = (el_t) JBE;
            mem_cmd[i++ ] = (el_t) temp_value;
             
            //записать в массив
        }

        if (strcmp (temp_string, "je") == 0)
        {
            mem_cmd[i++] = (el_t) JE;
            mem_cmd[i++] = (el_t) temp_value;
             
            //записать в массив
        }

        if (strcmp (temp_string, "jhe") == 0)
        {
            mem_cmd[i++] = (el_t) JHE;
            mem_cmd[i++] = (el_t) temp_value;
        }
    }
    return NO_ERROR_; 
}
//==================================================================================================
int Asm_Ctor (ASM* data_asm, long size)
{
    long size_mem_cmd = 4 * size;
    el_t* mem_cmd = (el_t*) calloc (size_mem_cmd, sizeof (el_t));

    if (mem_cmd == NULL) 
    return 0;

    data_asm -> mem_cmd = mem_cmd;
    data_asm -> size_mem_cmd = size_mem_cmd;

    return NO_ERROR_; 
}
//==================================================================================================
int Asm_Dtor (void* pointer)
{
    el_t** ptr_for_free = (el_t**) pointer;
    if (*ptr_for_free != NULL)
    free (*ptr_for_free);
    *ptr_for_free = NULL;

    return NO_ERROR_;
}
//==================================================================================================
int Dump (ASM* str_data, ONEGIN* data)
{
    fprintf (Log_File, "======================================================================================\n");
    fprintf (Log_File, "Number  ");
    for (int i = 0; i < str_data -> size_mem_cmd; ++i)
        fprintf (Log_File, "%05d  ", i);
    
    fprintf (Log_File, "\nValue   ");
    for (int i = 0; i < str_data -> size_mem_cmd; ++i)
    {
        fprintf (Log_File, "%05.2lf  ", str_data -> mem_cmd[i]);
    }
    fprintf (Log_File, "\n======================================================================================\n");

    return NO_ERROR_;
}