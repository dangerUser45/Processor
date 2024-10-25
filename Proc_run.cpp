#include "Machine.h"

#include <string.h>
#include <stdio.h>

#include "Stack_for_proc\Stack_Common.h"
#include "Stack_for_proc\Stack.h"
#include "Stack_for_proc\Debug.h"


#include "Proc_common.h"
#include "Proc_run.h"


int Run (SPU* data_proc)
{
    assert (data_proc);
    stack_t* stk = &(data_proc -> stk);

    el_t* code = data_proc -> buffer_for_code;

    //Dump (stk);
    int ip = 0;
    stack_el_t a = 0;
    stack_el_t b = 0;


    while (1)
    {
        switch ((int) code[ip])
        {
            case HLT  : return NO_ERROR_;
            
            case PUSH:  Stack_Push (stk, code[ip+1]);
                        Dump_St (stk);
                        ip += 2;
                        break;

            case POP  : Stack_Pop (stk, &a);
                        Dump_St (stk);
                        ip += 1;
                        break;

            case ADD  : Stack_Pop (stk, &a);
                        Stack_Pop (stk, &b);
                        Stack_Push (stk, a + b);
                        Dump_St (stk);
                        ip += 1;
                        break;

            case SUB  : Stack_Pop (stk, &a);
                        Stack_Pop (stk, &b);
                        Stack_Push (stk, b - a);
                        Dump_St (stk);
                        ip += 1;
                        break;

            case MUL  : Stack_Pop (stk, &a);
                        Stack_Pop (stk, &b);
                        Stack_Push (stk, a * b);
                        Dump_St (stk);
                        ip += 1;
                        break;

            case DIV  : Stack_Pop (stk, &a);
                        Stack_Pop (stk, &b);
                        Stack_Push (stk, b / a);
                        Dump_St (stk);
                        ip += 1;
                        break;

            case JMP  : _JUMP_COMMON_(0, ==)

            case JA   : _JUMP_COMMON_(1, >)

            case JB   : _JUMP_COMMON_(1, <)

            case JAE  : _JUMP_COMMON_(1, >=)
            
            case JBE  : _JUMP_COMMON_(1, <=)
      
            case JE   : _JUMP_COMMON_(1, ==)
           
            case JHE  : _JUMP_COMMON_(1, !=)

            case OUT_ : Stack_Pop (stk, &a);
                        printf ("%lf\n", a);
                        ip += 1; 
                        break;  

            case IN__ : scanf ("%lf", &a);
                        Stack_Push (stk, a);
                        ip += 1;
                        break;

            case SQRT : Stack_Pop (stk, &a);
                        Stack_Push (stk, sqrt (a));
                        ip += 1;
                        break;

            case SIN :  Stack_Pop (stk, &a);
                        Stack_Push (stk, sin (a));
                        ip += 1;
                        break;

            case COS :  Stack_Pop (stk, &a);
                        Stack_Push (stk, cos (a));
                        ip += 1;
                        break;

            case DUMP : //  dump ()                                               TODO
                        break;
            
            case PUSH_REG: a = data_proc -> register_buffer [int(code[ip+1])];
                           Stack_Push (stk, a);
                           ip += 2;
                           break;

            case POP_REG : Stack_Pop (stk, &a);
                           data_proc -> register_buffer [int (code[ip+1])] = a;
                           ip += 2;
                           break;

            default   : fprintf (Log_File, "Syntax_Error: %lf\n", code[ip]);
                        return GENERAL_ERROR;  
        } 
    }

}
//==================================================================================================
int Load_code (SPU* data_proc, FILE* code_text, el_t* buffer, size_t size)
{

    char temp_buf [50] = "";
    el_t temp_value = 0;
    if (fscanf (code_text, "%s", temp_buf) != 1)             return GENERAL_ERROR;
    if (strcmp (temp_buf, "MMD"))                            return GENERAL_ERROR;
    if (fscanf (code_text, "%lf", &temp_value) != 1)         return GENERAL_ERROR;  // !!! if change type of element you need change %lf
    if ((long) temp_value != (long) MY_NUMBER)                             return GENERAL_ERROR;
    fscanf (code_text, "%lf", &temp_value);                                //fill n_cmd
    data_proc -> n_cmd = long (temp_value);

    size_t cnt = 0;
    for (; cnt < size; ++cnt)
        if (fscanf (code_text, "%lf", &buffer[cnt]) == EOF) // !!! if change type of element you need change %lf
            break;
    data_proc -> num_of_read_item = cnt;

    return NO_ERROR_;
}
//==================================================================================================
int Dump_proccessor (const SPU* data_proc)
{
    assert (data_proc);
    fprintf (Log_File, "=================================================================\n");
    fprintf (Log_File, "\t\t\t\04 THE BEST DUMP YOU'VE EVER SEEN \04\n");

    fprintf (Log_File, "\t\tSTRUCT SPU: \n");
    fprintf (Log_File, "\n\t\t\10BUFFER_FOR_CODE\n");
    fprintf (Log_File, "\tnum_of_read_item = %zu\n", data_proc -> num_of_read_item);


    //           Dump_massiv ()                          TODO
    fprintf (Log_File, "\tAddress:  \t\tValue: \n"); 
    for (size_t i = 0; i < data_proc -> num_of_read_item; ++i)
    {
        fprintf (Log_File, "\t%p\t", data_proc -> buffer_for_code + i);
        fprintf (Log_File, "%lf\n", data_proc -> buffer_for_code[i]);
    }
    
    fprintf (Log_File, "\n\t\t\10REGISTER_BUFFER\n");
    //           Dump_massiv ()                           TODO
    fprintf (Log_File, "\tAddress:  \t\tValue:\n");
    for (size_t i = 0; i < NUM_REGS; ++i)
    {
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
int Jump (el_t* code, int* ip)
{
    *ip = (int) code [*ip+1];
    return NO_ERROR_;
}
//==================================================================================================
int Ctor_for_proc (SPU* data_for_proc)
{
    assert (data_for_proc);
    el_t* buffer_for_code = (el_t*) calloc (100, sizeof (el_t));
    if (buffer_for_code != NULL)
    data_for_proc -> buffer_for_code = buffer_for_code;

    STACK_CTOR(&data_for_proc -> stk, 100);

    el_t* reg = (el_t*) calloc (NUM_REGS, sizeof (el_t));
   if (reg != NULL)
       data_for_proc -> register_buffer = reg;
    
    return NO_ERROR_;
}
//==================================================================================================
int Dtor_for_proc (SPU* data_for_proc)
{
    Stack_Dtor (&data_for_proc -> stk);
    free (data_for_proc -> buffer_for_code);
    free (data_for_proc -> register_buffer);

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