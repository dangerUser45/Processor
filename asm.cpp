#define TX_COMPILED
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
    Ctor_Labels (&data_asm);

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
    Processing_Command (&data_asm, onegin_data.str_data, onegin_data.string_quantity) OR DIE;


    Dump (&data_asm);
    Dump_of_label (data_asm.mass_label_struct);

    Fill_Code_file (&data_asm, "OUT_ASM.txt");

    Close_file (Log_File);

    Ctor_Labels (&data_asm);
    Asm_Dtor (&data_asm.mem_cmd);

    txDisableAutoPause ();

    return 0;
}
//==================================================================================================;