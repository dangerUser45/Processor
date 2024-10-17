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
    ASM_DBG data_asm_dbg= {};
    ONEGIN onegin_data = {};

    Create_file ("ASM_LOG.txt");    //создал log_file


    Check_argc (argc);
    onegin_data.name = argv[1];
    onegin_data.fsize = file_size (argv[1]);
    Check_fsize (onegin_data.fsize);

    data_asm.nm_orig_f = argv[1];

    Read_File (&onegin_data); 

    Strings_Number (&onegin_data);

    DBG_Print (&onegin_data);

    Close_file (Log_File);
                                                                                                 
    Processing_Command (&data_asm);
    return 0;
}
//==================================================================================================
int Processing_Command (ASM* data_asm)
{
    while (1)
    //if (strcmp ());
    return NO_ERROR_; 
}
//==================================================================================================
/*int Asm_Ctor (ASM*)
{
    //el_t* mem_cmd = (el_t*) calloc ();
    //mem_cmd =  
}
//==================================================================================================
int Asm_Dtor ()
{

}*/
//==================================================================================================
int Dump (ASM* str_data)
{
    

    return NO_ERROR_;
}