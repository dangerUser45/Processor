#include "..\SuperLibs\TXLib.h"
#include "Stack_for_proc\Common.h"
#include "Asm.h"
#include "Onegin_for_proc\Onegin_processing.h"
#include "Onegin_for_proc\Onegin_General.h"
#include "Onegin_for_proc\Print.h"
#include "Stack_for_proc\Debug.h"

int main (int argc, char* argv[])
{   
    ASM data_asm = {};
    ASM_DBG data_asm_dbg = {};
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

    Close_file (Log_File);
                                                                                                 
    Processing_Command (&data_asm, onegin_data.str_data, onegin_data.string_quantity);
    return 0;
}
//==================================================================================================
int Processing_Command (ASM* data_asm, STRING* str_data, long size)
{
    char temp [20] = {};

    for (long i = 0; i < size; ++i)
        sscanf (str_data[i].str_addr, "%s", temp);

            if (strcmp (temp, "push") == 0)
            //записать в массив

        else if (strcmp (temp, "pop") == 0)
            //записать в массив

        else if (strcmp (temp, "add") == 0)
            //записать в массив

        else if (strcmp (temp, "mul") == 0)
            //записать в массив
        
        else if (strcmp (temp, "div") == 0)
            //записать в массив

        else if (strcmp (temp, "hlt") == 0)
            //записать в массив

        else if (strcmp (temp, "jmp") == 0)
            //записать в массив

        else if (strcmp (temp, "ja") == 0)
            //записать в массив

        else if (strcmp (temp, "jb") == 0)
            //записать в массив

        else if (strcmp (temp, "jae") == 0)
            //записать в массив

        else if (strcmp (temp, "jbe") == 0)
            //записать в массив

        else if (strcmp (temp, "je") == 0)
            //записать в массив

        else if (strcmp (temp, "jhe") == 0)
            //записать в массив

    return NO_ERROR_; 
}
//==================================================================================================
int Asm_Ctor (ASM*)
{
    //el_t* mem_cmd = (el_t*) calloc ();
    //mem_cmd =  
}
//==================================================================================================
int Asm_Dtor ()
{

}
//==================================================================================================
int Dump (ASM* str_data)
{
    

    return NO_ERROR_;
}