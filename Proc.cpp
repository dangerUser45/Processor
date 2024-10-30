#include "Machine.h"
#include "Stack_for_proc\Stack_Common.h"
#include "Stack_for_proc\Stack.h"
#include "Stack_for_proc\Debug.h"
#include "Asm.h"
#include "Proc_common.h"
#include "Proc_run.h"
#include "Onegin_for_proc\Onegin_processing.h"


int main (int argc, char* argv[])
{   
   Check_argc (argc);
   Create_file ("PROC_LOG.txt");    //создал log_file

    SPU data_proc = {};  
   Ctor_for_proc (&data_proc);                              //create buffer_for_code and registers  

    FILE* code_text = fopen (argv[1], "r");
    
    int res = Load_code (&data_proc, code_text, data_proc.buffer_for_code, 100); 
    fclose (code_text);
    if (res) abort ();

    Dump_proccessor (&data_proc, "main (): Begining dump");

    Run (&data_proc) OR DIE;
    Dump_proccessor (&data_proc, "main (): Last dump");

    Close_file (Log_File);

    Dtor_for_proc (&data_proc);
    return 0;
}
