#include "..\SuperLibs\TXLib.h"
#include "Stack_for_proc\Common.h"
#include "Asm.h"
#include "Onegin_for_proc\Processing.h"
#include "Onegin_for_proc\General.h"
#include "Onegin_for_proc\Print.h"

int main (int argc, char* argv[])
{   
    ASM data_asm = {};
    ONEGIN str_data = {};

    Check_argc (argc);
    str_data.name = argv[1];
    str_data.fsize = file_size (argv[1]);
    Check_fsize (str_data.fsize);

    data_asm.nm_orig_f = argv[1];

    Read_File (&str_data); 
    DBG_Print (&str_data);
                                                                                                    
    //Processing_Command (&data_asm);
    return 0;
}
//==================================================================================================
/*int Asm_Ctor (ASM*)
{
    //el_t* mem_cmd = (el_t*) calloc ();
    //mem_cmd =  
}
//==================================================================================================
int Processing_Command (ASM* data_asm)
{
    
}
//==================================================================================================
int Asm_Dtor ()
{

}
//==================================================================================================
*/
int Dump ()
{


    return NO_ERROR_;
}