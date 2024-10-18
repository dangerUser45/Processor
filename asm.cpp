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
    
    while (i < size)
    {
        sscanf (str_data[i].str_addr, "%s", temp_string);
        sscanf (str_data[i].str_addr, "%lf", &temp_value);

        fprintf (Log_File, "Temp_string = %s\n", temp_string);
        fprintf (Log_File, "Temp_value = %lf\n", temp_value);

        if (strcmp (temp_string, "hlt") == 0)
        {
            mem_cmd[i] = (el_t) HLT;
            mem_cmd[i+1] = (el_t) temp_value;
            //записать в массив
        }

        else if (strcmp (temp_string, "push") == 0)
        {
            mem_cmd[i] = (el_t) PUSH;
            mem_cmd[i+1] = (el_t) temp_value;
            //записать в массив
        }

        else if (strcmp (temp_string, "pop") == 0)
        {
            mem_cmd[i] = (el_t) POP;
            mem_cmd[i+1] = (el_t) temp_value;
            //записать в массив
        }

        else if (strcmp (temp_string, "add") == 0)
        {
            mem_cmd[i] = (el_t) ADD;
            mem_cmd[i+1] = (el_t) temp_value;
            //записать в массив
        }

        else if (strcmp (temp_string, "mul") == 0)
        {
            mem_cmd[i] = (el_t) MUL;
            mem_cmd[i+1] = (el_t) temp_value;
            //записать в массив
        }
        
        else if (strcmp (temp_string, "div") == 0)
        {
            mem_cmd[i] = (el_t) DIV;
            mem_cmd[i+1] = (el_t) temp_value;
            //записать в массив
        }
        else if (strcmp (temp_string, "jmp") == 0)
        {
            mem_cmd[i] = (el_t) JMP;
            mem_cmd[i+1] = (el_t) temp_value;
        }

        else if (strcmp (temp_string, "ja") == 0)
        {
            mem_cmd[i] = (el_t) JA;
            mem_cmd[i+1] = (el_t) temp_value;
            //записать в массив
        }

        else if (strcmp (temp_string, "jb") == 0)
        {
            mem_cmd[i] = (el_t) JB;
            mem_cmd[i+1] = (el_t) temp_value;
            //записать в массив
        }

        else if (strcmp (temp_string, "jae") == 0)
        {
            mem_cmd[i] = (el_t) JAE;
            mem_cmd[i+1] = (el_t) temp_value;
            //записать в массив
        }

        else if (strcmp (temp_string, "jbe") == 0)
        {
            mem_cmd[i] = (el_t) JBE;
            mem_cmd[i+1] = (el_t) temp_value;
            //записать в массив
        }

        else if (strcmp (temp_string, "je") == 0)
        {
            mem_cmd[i] = (el_t) JE;
            mem_cmd[i+1] = (el_t) temp_value;
            //записать в массив
        }

        else if (strcmp (temp_string, "jhe") == 0)
        {
            mem_cmd[i] = (el_t) JHE;
            mem_cmd[i+1] = (el_t) temp_value;
            //записать в масси
        }

        fprintf (Log_File, "mem_cmd[i] = %lf", mem_cmd[i]);
    }
    return NO_ERROR_; 
}
//==================================================================================================
int Asm_Ctor (ASM* data_asm, long size)
{
    el_t* mem_cmd = (el_t*) calloc (2* size, sizeof (el_t));

    if (mem_cmd == NULL) 
    return 0;

    data_asm -> mem_cmd = mem_cmd;

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
int Dump (ASM* str_data)
{
    

    return NO_ERROR_;
}