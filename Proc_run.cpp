#include "Machine.h"

#include <string.h>
#include <stdio.h>

#include "Stack_for_proc\Stack_Common.h"
#include "Stack_for_proc\Stack.h"


#include "Proc_common.h"
#include "Proc_run.h"


void Run (el_t* code, long n_cmd)
{
    stack_t stk = {};
    STACK_CTOR (&stk, 1);
    int ip = 0;
    stack_el_t a = 0;
    stack_el_t b = 0;


    while (1)
    {
        switch ((int) code[ip])
        {
            case HLT  : break;
            
            case PUSH: Stack_Push (&stk, code[ip+1]);
                       ip += 2;
                break;
            case POP  : Stack_Pop (&stk, &a);
                        ip += 1;
                break;
            case ADD  : Stack_Pop (&stk, &a);
                        Stack_Pop (&stk, &b);
                        Stack_Push (&stk, a + b);
                        ip += 1;
                        break;

            case MUL  : Stack_Pop (&stk, &a);
                        Stack_Pop (&stk, &b);
                        Stack_Push (&stk, a * b);
                        ip += 1;
                        break;

            case DIV  : Stack_Pop (&stk, &a);
                        Stack_Pop (&stk, &b);
                        Stack_Push (&stk, b / a);
                        ip += 1;
                        break;

            case JMP  : _JUMP_COMMON_(0, ==)

            case JA   : _JUMP_COMMON_(1, >)

            case JB   : _JUMP_COMMON_(1, <)

            case JAE  : _JUMP_COMMON_(1, >=)
            
            case JBE  : _JUMP_COMMON_(1, <=)
      
            case JE   : Stack_Pop (&stk, &a);
                        Stack_Pop (&stk, &b);
                        if (b = a) Jump (code, &ip);
                        break;
           
            case JHE  : Stack_Pop (&stk, &a);
                        Stack_Pop (&stk, &b);
                        if (b != a) Jump (code, &ip);
                        break;

            case OUT_ : Stack_Pop (&stk, &a);
                        fprintf (Log_File, "%lf", a) 
                        break;

            case IN__ : scanf ("%lf", &a)
                        Stack_Push (&stk, a * b);
                        break;

            default   : fprintf (Log_File, "Syntax_Error\n");

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

    for (size_t i =0; i < size; ++i) 
        if (fscanf (code_text, "%lf", &buffer[i]) == EOF) // !!! if change type of element you need change %lf
            break;
    return NO_ERROR_;
}
//==================================================================================================
int Dump_proccessor (SPU* data_proc)
{
    for (int i = 0; i < data_proc -> n_cmd; ++i)
    fprintf (Log_File, "%lf", data_proc -> buffer_for_code [i]);

    return NO_ERROR_;
}
//==================================================================================================
int Jump (el_t* code, int* ip)
{
    *ip = code [*ip+1];
    return NO_ERROR_;
}
//==================================================================================================
