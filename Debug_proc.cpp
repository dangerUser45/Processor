#include "Machine.h"

#include "Proc_common.h"
#include "..\Stack_for_proc\Stack_Common.h"

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
int Dump_proccessor (const SPU* data_proc)
{
    assert (data_proc);

    int ip = data_proc -> ip; 

    fprintf (Log_File, "=================================================================\n");
    fprintf (Log_File, "\t\t\t\04 THE BEST DUMP YOU'VE EVER SEEN \04\n");

    fprintf (Log_File, "\t\tSTRUCT SPU: \n");
    fprintf (Log_File, "\n\t\t\10BUFFER_FOR_CODE\n");
    fprintf (Log_File, "\tnum_of_read_item = %zu\n", data_proc -> num_of_read_item);


    //           Dump_massiv ()                          TODO
    fprintf (Log_File, "\tAddress:  \t\tValue:  \t\tDizasm\n"); 
    for (size_t i = 0; i < data_proc -> num_of_read_item; ++i)
    {
        fprintf (Log_File, "%d)     %p\t", i + 1, data_proc -> buffer_for_code + i);
        fprintf (Log_File, "%0.7lf\n", data_proc -> buffer_for_code[i]);
        fprintf (Log_File, "%s", Dizassembler (data_proc -> buffer_for_code[i], &ip));
  
    }
    
    fprintf (Log_File, "\n\t\t\10REGISTER_BUFFER\n");
    //           Dump_massiv ()                           TODO
    fprintf (Log_File, "\tAddress:  \t\tValue:\n");
    for (size_t i = 0; i < NUM_REGS; ++i)
    {

        fprintf (Log_File, "     %cX", int(i) ?  int(i) +  'A' - 1 : 'Z');
        fprintf (Log_File, "\t%p", data_proc -> register_buffer + i);
        fprintf (Log_File, "\t%lf\n", data_proc -> register_buffer[i]);
    }
    fprintf (Log_File, "\n\t\t\10STK\n");
    //           Dump_massiv ()                           TODO
    //Dump (&data_proc -> stk);
 

      //Dump (&data_proc -> stk);
     for (int i = 0; i < data_proc -> n_cmd; ++i)
    fprintf (Log_File, "\t%lf\n", data_proc -> stk.buffer[i]);
 
    fprintf (Log_File, "=================================================================\n");

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
const char* Dizassembler (el_t cmd, el_t* addr_ip )
{
    if (cmd < -1 && cmd == 0 &&  cmd > NUMB_CMD - 1){
        fprintf (Log_File, "DIZASSSEMBLER: SYNTAX ERROR !\n");
        abort ();}

    return info[(int)cmd].name_cmd;
}