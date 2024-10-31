#include "..\SuperLibs\TXLib.h"
#include "Stack_for_proc\Stack_Common.h"
#include "Asm.h"
#include "Onegin_for_proc\Onegin_processing.h"
#include "Onegin_for_proc\Onegin_General.h"
#include "Onegin_for_proc\Print.h"
#include "Stack_for_proc\Debug.h"
#include "Enum_proc.h"

int main (int argc, char* argv[])
{   
    ASM data_asm = {};
    ONEGIN onegin_data = {};

    Create_file ("ASM_LOG.html");    //создал log_file
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
    Processing_Command (&data_asm, onegin_data.str_data, onegin_data.string_quantity) OR DIE;
    Dump (&data_asm, &onegin_data);

    Fill_Code_file (&data_asm, "OUT_ASM.txt");

    Close_file (Log_File);
    Asm_Dtor (&data_asm.mem_cmd);
    return 0;
}
//==================================================================================================
int Processing_Command (ASM* data_asm, STRING* str_data, long size)
{
    el_t* mem_cmd = data_asm -> mem_cmd;
    char temp_string [20] = {};
    char string_for_type [20] = {};
    el_t temp_value = 0;

    long  ip = 0;
    long line = 0;
    
    while (line < size)
    {   
        int cnt_rd_sym= 0;
        int type_of_arg = 0;

        sscanf (str_data[line].str_addr, "%s%n", temp_string, &cnt_rd_sym);

        if (sscanf (str_data[line].str_addr + cnt_rd_sym, "%lf", &temp_value) == 1)
            type_of_arg = 1;

        else if (sscanf (str_data[line].str_addr + cnt_rd_sym, "%s", string_for_type) == 1)
        {
            if (strcmp (string_for_type, "zx") == 0) temp_value = ZERO_RG;
            if (strcmp (string_for_type, "ax") == 0) temp_value = FRST_RG;
            if (strcmp (string_for_type, "bx") == 0) temp_value = SCND_RG;
            if (strcmp (string_for_type, "cx") == 0) temp_value = THRD_RG;
            if (strcmp (string_for_type, "dx") == 0) temp_value = FRTH_RG;
            if (strcmp (string_for_type, "ex") == 0) temp_value = FFTH_RG;
            if (strcmp (string_for_type, "fx") == 0) temp_value = SXTH_RG;
            if (strcmp (string_for_type, "gx") == 0) temp_value = SVNTH_RG;
            if (strcmp (string_for_type, "hx") == 0) temp_value = EGHTH_RG;

            type_of_arg = 2;
        }
        ++line;

        fprintf (Log_File, "%ld)Temp_string = %s\n",line, temp_string);
        fprintf (Log_File, "Temp_value = %lf\n", temp_value);

        if (strcmp (temp_string, "hlt") == 0)
        {
            mem_cmd[ ip++] = (el_t) HLT;
        }

        else if (strcmp (temp_string, "push") == 0)
        {
            if (type_of_arg == 1){
                mem_cmd[ip++] = (el_t) PUSH;
                mem_cmd[ip++] = (el_t) temp_value;}

            if (type_of_arg == 2){
                mem_cmd[ip++] = (el_t) PUSH_REG;
                mem_cmd[ip++] = (el_t) temp_value;}
        }

        else if (strcmp (temp_string, "pop") == 0)
        {
            if (type_of_arg == 1){
                mem_cmd[ip++] = (el_t) POP;
                mem_cmd[ip++] = (el_t) temp_value;}

            if (type_of_arg == 2){
                mem_cmd[ip++] = (el_t) POP_REG;
                mem_cmd[ip++] = (el_t) temp_value;}
        }

        else if (strcmp (temp_string, "add") == 0)
        {
            mem_cmd[ ip++] = (el_t) ADD;
        }

        else if (strcmp (temp_string, "sub") == 0)
        {
            mem_cmd[ip++] = (el_t) SUB;
        }

        else if (strcmp (temp_string, "mul") == 0)
        {
            mem_cmd[ ip++] = (el_t) MUL;   
            //записать в массив
        }

        else if (strcmp (temp_string, "sqrt") == 0)
        {
            mem_cmd[ ip++] = (el_t) SQRT;   
            //записать в массив
        }

        else if (strcmp (temp_string, "in") == 0)
        {
            mem_cmd[ ip++] = (el_t) IN__;   
            //записать в массив
        }

        else if (strcmp (temp_string, "sin") == 0)
        {
            mem_cmd[ ip++] = (el_t) SIN;   
            //записать в массив
        }

        else if (strcmp (temp_string, "cos") == 0)
        {
            mem_cmd[ ip++] = (el_t) COS;   
            //записать в массив
        }

        else if (strcmp (temp_string, "dump") == 0)
        {
            mem_cmd[ ip++] = (el_t) DUMP;   
            //записать в массив
        }
        
        /*else if (strcmp (temp_string, "push_reg") == 0)
        {
            mem_cmd[ ip++] = (el_t) PUSH_REG;   
            //записать в массив                                    TODO
        }

        else if (strcmp (temp_string, "pop_reg") == 0)
        {
            mem_cmd[ ip++] = (el_t) POP_REG;   
            //записать в массив
        }*/
        else  if (strcmp (temp_string, "div") == 0)
        {
            mem_cmd[ ip++] = (el_t) DIV;   
            //записать в массив
        }
        else if (strcmp (temp_string, "jmp") == 0)
        {
            mem_cmd[ ip++] = (el_t) JMP;
            mem_cmd[ ip++] = (el_t) temp_value;
             
        }

        else if (strcmp (temp_string, "ja") == 0)
        {
            mem_cmd[ ip++] = (el_t) JA;
            mem_cmd[ ip++] = (el_t) temp_value;
             
            //записать в массив
        }

        else if (strcmp (temp_string, "jb") == 0)
        {
            mem_cmd[ ip++] = (el_t) JB;
            mem_cmd[ ip++]  = (el_t) temp_value;
             
            //записать в массив
        }

        else if (strcmp (temp_string, "jae") == 0)
        {
            mem_cmd[ ip++] = (el_t) JAE;
            mem_cmd[ ip++] = (el_t) temp_value;
             
            //записать в массив
        }

        else if (strcmp (temp_string, "jbe") == 0)
        {
            mem_cmd[ip++] = (el_t) JBE;
            mem_cmd[ip++ ] = (el_t) temp_value;
             
            //записать в массив
        }

        else if (strcmp (temp_string, "je") == 0)
        {
            mem_cmd[ip++] = (el_t) JE;
            mem_cmd[ip++] = (el_t) temp_value;
             
            //записать в массив
        }

       else if (strcmp (temp_string, "jhe") == 0)
        {
            mem_cmd[ip++] = (el_t) JHE;
            mem_cmd[ip++] = (el_t) temp_value;
        }
        else if (strcmp (temp_string, "out") == 0)
        {
            mem_cmd[ip++] = (el_t) OUT_;
        }
        else
        {   
            fprintf (Log_File, "SYNTAX ERROR !: %s", temp_string);
            return GENERAL_ERROR;
        }
    }
    data_asm -> final_ip  = ip; 
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
//==================================================================================================
int Fill_Code_file (ASM* data_asm, const char* name)
{
    FILE* output_file = fopen (name, "w");

    if ((output_file) == NULL)
    {
        fprintf (stdout, "Не удается открыть файл %s\n", name);
        return 0;
    }

    fprintf (output_file, "%s %d %ld ", "MMD", 13, data_asm -> final_ip);
    for (int i = 0; i < data_asm -> final_ip; ++i)
        fprintf (output_file, "%lf ", data_asm -> mem_cmd [i]);
    
    fclose (output_file);
    return NO_ERROR_;
}
//==================================================================================================
int Ctor_Labels ()
{
    
    return NO_ERROR_;
}