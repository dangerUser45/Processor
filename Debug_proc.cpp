#include "Machine.h"

#include "Proc_common.h"
#include "Stack_for_proc\Stack_Common.h"
#include "Stack_for_proc\Debug.h"
#include "Debug_proc.h"


const CMD_INFO info[22] =
    {{"hlt",     0},
     {"push",    1},
     {"pop",     1},
     {"add",     0},
     {"sub",     0},
     {"mul",     0},
     {"div",     0},
     {"jmp",     1},
     {"ja",      1},
     {"jb",      1},
     {"jae",     1},
     {"jbe",     1},
     {"je",      1},
     {"jhe",     1}, 
     {"out",     0},
     {"in",      0},
     {"sqrt",    0},
     {"sin",     0},
     {"cos",     0},
     {"dump",    0},
     {"push_reg",1},
     {"pop_reg", 1}
    };

//==================================================================================================
int Dump_proccessor (const SPU* data_proc, const char* name_calling)
{
    assert (data_proc);

    int ip = data_proc -> ip; 

    fprintf (Log_File, "=================================================================\n");
    fprintf (Log_File, "\t\t\t<font color=#2f7d60>  THE BEST DUMP YOU'VE EVER SEEN </font>\n");

    fprintf (Log_File, "\tCalling from: <font color=#ff7c00>%s\n</font>", name_calling);
    fprintf (Log_File, "\t\t<font size = \"4\"> \nSTRUCT SPU:</font>\n");


    fprintf (Log_File, "\n\t\tBUFFER_FOR_CODE\n");
    fprintf (Log_File, "\tnum_of_read_item = %zu\n", data_proc -> num_of_read_item);
    //           Dump_massiv ()                          TODO
    fprintf (Log_File, "\t<b><font color=#2a00ff>Address</font>:  \t\t<font color=#ff0000>Value</font>:  \t<font color=#277a0a>Dizasm</font>:</b> \n"); 
    for (size_t i = 0; i < data_proc -> num_of_read_item; ++i)
    {
        fprintf (Log_File, "    %2zu) %p\t", i + 1, data_proc -> buffer_for_code + i);
        fprintf (Log_File, "%0.7lf\n", data_proc -> buffer_for_code[i]);
        //fprintf (Log_File, "\t%s\n", Dizassembler (data_proc -> buffer_for_code[i], &ip));
    
    }
    
    fprintf (Log_File, "\n\t\tREGISTER_BUFFER\n");
    //           Dump_massiv ()                           TODO
    fprintf (Log_File, "\t<b><font color=#2a00ff>Address</font>:  \t\t<font color=#ff0000>Value</font>:</b>\n");
    for (size_t i = 0; i < NUM_REGS; ++i)
    {

        fprintf (Log_File, "     %cX", int(i) ?  int(i) +  'A' - 1 : 'Z');
        fprintf (Log_File, "\t%p", data_proc -> register_buffer + i);
        fprintf (Log_File, "\t%lf\n", data_proc -> register_buffer[i]);
    }
                                        //STACK
    Dump (& data_proc -> stk);


     for (int i = 0; i < data_proc -> n_cmd; ++i)
    fprintf (Log_File, "    %3d) %lf\n", i ,data_proc -> stk.buffer[i]);


    /*
    fprintf (Log_File, "\t<b><font color=#2a00ff>Address</font>:  \t\t<font color=#ff0000>Value</font>:</b>\n"); 
    for (size_t i = 0; i < INIT_NUM_EL + 2; ++i)
    {
        fprintf (Log_File, "    %3zu) %p", i ,data_proc -> stk.buffer + i);
        fprintf (Log_File, "\t%07lf\n", data_proc -> stk.buffer[i]);
    }
    fprintf (Log_File, "=================================================================\n");
    */

    return NO_ERROR_;
}
//==================================================================================================
int Dump_St (stack_t* stk)
{
    assert(stk);
    fprintf (stderr, "Sz = %lld, ",stk ->size);
    fprintf (stderr, "cp = %lld\n",stk -> capacity);

    if (stk -> buffer != NULL)
    for (int i = 0; i < stk->size; ++i) 
        fprintf (stderr, "[%d]%lf ", i,  stk -> buffer [i]);
    fprintf (stderr, "\n");

    return NO_ERROR_;
}
//==================================================================================================
    const char* Dizassembler (el_t cmd_wrong_t, int* addr_ip)
{
    const int CONTINUE__ = 1;
    const int SKIP__ = -1;
    static int CONTEXT__ = 0;

    int cmd = (int) cmd_wrong_t;
    if (CONTEXT__ < 0) {
        CONTEXT__ = CONTINUE__;
        return " ";}

    if (cmd < -1 || cmd == 0 ||  cmd > NUMB_CMD - 1){
        fprintf (Log_File, "\nDIZASSSEMBLER: SYNTAX ERROR !\n");
        abort ();}
    
    *addr_ip += info[cmd].numb_arg + 1;
    CONTEXT__ = SKIP__;
    return info[(int)cmd].name_cmd;
}   