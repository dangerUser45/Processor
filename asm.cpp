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

    Dump (&data_asm);
    Dump_of_label (data_asm.mass_label_struct);

    Fill_Code_file (&data_asm, "OUT_ASM.txt");

    Close_file (Log_File);

    Ctor_Labels (&data_asm);
    Asm_Dtor (&data_asm.mem_cmd);
    return 0;
}
//==================================================================================================
int Processing_Command (ASM* data_asm, STRING* str_data, long size)
{
    el_t* mem_cmd = data_asm -> mem_cmd;
    ASM_Context ctx = {};
    
    while (ctx.line < size)
    {   
        /*int cnt_rd_sym= 0;
        int type_of_arg = 0;

        char temp_string [20] = "";
        char string_for_type [20] = "";
        el_t temp_value = 0;*/
        sscanf (str_data[ctx.line].str_addr, "%s%n", ctx.temp_string, &ctx.cnt_rd_sym);

        if (strchr(ctx.temp_string, ':')  != NULL)
            {
                Add_Label (data_asm -> mass_label_struct, str_data[ctx.line].str_addr, ctx.ip); 
                ++ctx.line;
                continue;
            }    
        /*else if (sscanf (str_data[line].str_addr + cnt_rd_sym, "%s", string_for_type) == 1)
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

        else if (printf ("??? string_for_type = /%s/\n", string_for_type),
                 printf ("str_data[line].str_addr + cnt_rd_sym = /%s/\n ", str_data[line].str_addr + cnt_rd_sym),
                 sscanf ($($(str_data[line].str_addr) + $(cnt_rd_sym)), "%s", string_for_type) == 1){
            mem_cmd[ip++] = Getting_Labels (data_asm ->mass_label_struct, string_for_type);
            printf ("!!! string_for_type = /%s/\n", string_for_type);
        }
            
        ++line;

        fprintf (Log_File, "%ld)Temp_string = %s\n",line, temp_string);
        fprintf (Log_File, "Temp_value = %lf\n", temp_value);

        if (strcmp (temp_string, "hlt") == 0)
        {
            mem_cmd[ ip++] = (el_t) HLT;
        }*/

        else if (strcmp (ctx.temp_string, "push") == 0)
        {
            if (ctx.type_of_arg == 1){
                mem_cmd[ctx.ip++] = (el_t) PUSH;
                Compile_Arg (data_asm, &ctx);
                mem_cmd[ctx.ip++] = (el_t) ctx.temp_value;}

            if (ctx.type_of_arg == 2){
                mem_cmd[ctx.ip++] = (el_t) PUSH_REG;
                Compile_Arg (data_asm, &ctx);
                mem_cmd[ctx.ip++] = (el_t) ctx.temp_value;}
        }

        else if (strcmp (ctx.temp_string, "pop") == 0)
        {
            if (ctx.type_of_arg == 1){
                mem_cmd[ctx.ip++] = (el_t) POP;
                Compile_Arg (data_asm, &ctx);
                mem_cmd[ctx.ip++] = (el_t) ctx.temp_value;}

            if (ctx.type_of_arg == 2){
                mem_cmd[ctx.ip++] = (el_t) POP_REG;
                Compile_Arg (data_asm, &ctx);
                mem_cmd[ctx.ip++] = (el_t) ctx.temp_value;}
        }

        else if (strcmp (ctx.temp_string, "add") == 0)
        {
            mem_cmd[ ctx.ip++] = (el_t) ADD;
        }

        else if (strcmp (ctx.temp_string, "sub") == 0)
        {
            mem_cmd[ctx.ip++] = (el_t) SUB;
        }

        else if (strcmp (ctx.temp_string, "mul") == 0)
        {
            mem_cmd[ ctx.ip++] = (el_t) MUL;   
        }

        else if (strcmp (ctx.temp_string, "sqrt") == 0)
        {
            mem_cmd[ ctx.ip++] = (el_t) SQRT;   
        }

        else if (strcmp (ctx.temp_string, "in") == 0)
        {
            mem_cmd[ ctx.ip++] = (el_t) IN__;   
        }

        else if (strcmp (ctx.temp_string, "sin") == 0)
        {
            mem_cmd[ ctx.ip++] = (el_t) SIN;   
        }

        else if (strcmp (ctx.temp_string, "cos") == 0)
        {
            mem_cmd[ ctx.ip++] = (el_t) COS;   
        }

        else if (strcmp (ctx.temp_string, "dump") == 0)
        {
            mem_cmd[ ctx.ip++] = (el_t) DUMP;   
        }
        
        else if (strcmp (ctx.temp_string, "div") == 0)
        {
            mem_cmd[ ctx.ip++] = (el_t) DIV;   
        }

        else if (strcmp (ctx.temp_string, "call") == 0)                                                                                                                                
        {
            mem_cmd[ ctx.ip++] = (el_t) CALL;
            Compile_Arg (data_asm, &ctx);
            mem_cmd[ ctx.ip++] = (el_t) ctx.temp_value;
        }

        else if (strcmp (ctx.temp_string, "ret") == 0)                                                                                                                                      
        {
            mem_cmd[ ctx.ip++] = (el_t) RET;
        }

        else if (strcmp (ctx.temp_string, "jmp") == 0)                                                                           
        {
            mem_cmd[ ctx.ip++] = (el_t) JMP;
            Compile_Arg (data_asm, &ctx);
            mem_cmd[ ctx.ip++] = (el_t) ctx.temp_value;
        }

        else if (strcmp (ctx.temp_string, "ja") == 0)
        {
            mem_cmd[ ctx.ip++] = (el_t) JA;
            Compile_Arg (data_asm, &ctx);
            mem_cmd[ ctx.ip++] = (el_t) ctx.temp_value;
        }

        else if (strcmp (ctx.temp_string, "jb") == 0)
        {
            mem_cmd[ ctx.ip++] = (el_t) JB;
            Compile_Arg (data_asm, &ctx);
            mem_cmd[ ctx.ip++]  = (el_t) ctx.temp_value;
             
            //записать в массив
        }

        else if (strcmp (ctx.temp_string, "jae") == 0)
        {
            mem_cmd[ ctx.ip++] = (el_t) JAE;
            Compile_Arg (data_asm, &ctx);
            mem_cmd[ ctx.ip++] = (el_t) ctx.temp_value;
             
            //записать в массив
        }

        else if (strcmp (ctx.temp_string, "jbe") == 0)
        {
            mem_cmd[ctx.ip++] = (el_t) JBE;
            Compile_Arg (data_asm, &ctx);
            mem_cmd[ctx.ip++ ] = (el_t) ctx.temp_value;
             
            //записать в массив
        }

        else if (strcmp (ctx.temp_string, "je") == 0)
        {
            mem_cmd[ctx.ip++] = (el_t) JE;
            Compile_Arg (data_asm, &ctx);
            mem_cmd[ctx.ip++] = (el_t) ctx.temp_value;
             
            //записать в массив
        }

       else if (strcmp (ctx.temp_string, "jhe") == 0)
        {
            mem_cmd[ctx.ip++] = (el_t) JHE;
            Compile_Arg (data_asm, &ctx);
            mem_cmd[ctx.ip++] = (el_t) ctx.temp_value;
        }

        else if (strcmp (ctx.temp_string, "out") == 0)
        {
            mem_cmd[ctx.ip++] = (el_t) OUT_;
        }

        else
        {   
            fprintf (Log_File, "SYNTAX ERROR !: %s", ctx.temp_string);
            return GENERAL_ERROR;
        }
    }
    data_asm -> final_ip  = ctx.ip;

    return NO_ERROR_; 
}
//==================================================================================================
int Asm_Ctor (ASM* data_asm, long size)
{
    Ctor_Labels (data_asm);

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

#define GREEN(text) "<font color =#0D881E>" text "</font>"
#define GREEN_L(text) "<font color =#00e11f>" text "</font>"

#define RED(text) "<font color =#FF0000>"   text "</font>"
#define BOLD(text)  "<b>"                   text "</b>"

int Dump (ASM* str_data)
{
    fprintf (Log_File, "======================================================================================\n");
    fprintf (Log_File, BOLD (GREEN ("NUMBER  ")));
    for (int i = 0; i < str_data -> size_mem_cmd; ++i)
        fprintf (Log_File,  GREEN_L("%06d  "), i);
    
    fprintf (Log_File, BOLD (RED ("\nVALUE   ")));
    for (int i = 0; i < str_data -> size_mem_cmd; ++i)
    {
        fprintf (Log_File,"%06.2lf  ", str_data -> mem_cmd[i]);
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
int Ctor_Labels (ASM* data_asm)
{
    assert (data_asm);
    label* label_ptr = (label*) calloc (INIT_NUM_LABELS, sizeof (label));

    for (int i = 0; i < INIT_NUM_LABELS; ++i)
        label_ptr[i].addr = -1;

    data_asm -> mass_label_struct = label_ptr;

    return NO_ERROR_;
}
//==================================================================================================
int Add_Label (label* mass_label_struct, const char* name_label, int ip)
{
    assert(mass_label_struct);
    assert (name_label);

    static int i = 0;
    mass_label_struct[i].name_of_label = name_label;
    mass_label_struct[i].addr = ip - 1; 
    ++i;
    
    return NO_ERROR_;
}
//==================================================================================================
int Getting_Labels (label* mass_for_label, const char* name_of_label)
{
    printf ("Gett.lab. ():  name of label = /%s/\n", name_of_label);
    for (int i = 0; i < INIT_NUM_LABELS; ++i){
        if (strcmp (name_of_label, mass_for_label[i].name_of_label))
            return mass_for_label[i].addr;
        else 
        printf ("ERROR in line: %d  Getting_Label()\n", __LINE__ - 2);
    }
    return ERROR__;       
}
//==================================================================================================
int Dtor_Labels (ASM* data_asm)
{
    assert (data_asm);

    if (data_asm -> mass_label_struct)                                                                                                                                                                                                          
    free (data_asm -> mass_label_struct);

    return NO_ERROR_;
}
//==================================================================================================
int Dump_of_label (label* mass_label_struct)
{
    assert(mass_label_struct);
    fprintf (Log_File, "<b><font color =#EC4399>_________________________________________________________________\n</font>");
    fprintf (Log_File, "\t\t <span style=\"background:#EC4399\"><font color =#FFFFFF>LABELS</font></span>\n");
    fprintf (Log_File, "\t<font color=#2a00ff>Name</font>:  \t\t<font color=#ff0000>Value</font>:</b>\n");
    for (int i = 0; i < INIT_NUM_LABELS; ++i)
    {
        fprintf (Log_File, "   %3d) %-14s", i, mass_label_struct[i].name_of_label);
        fprintf (Log_File, "  %d\n", mass_label_struct[i].addr);
        printf ("mass_label_struct[i].name_of_label = %s\n", mass_label_struct[i].name_of_label);
    }                                                                                                                                                                                                                                                 

    fprintf (Log_File, "<b><font color =#EC4399>_________________________________________________________________\n</font>");

    return NO_ERROR_;
}
//==================================================================================================
int Compile_Arg (ASM* data_asm, ASM_Context* ctx)
{
    assert (ctx);

    if (sscanf ((ctx -> current_string) + (ctx -> cnt_rd_sym), "%lf", &ctx -> temp_value) == 1)
        ctx -> type_of_arg = 1;

    else if (sscanf (ctx -> current_string  + ctx -> cnt_rd_sym, "%s", ctx -> temp_string) == 1)
        {
            if (strcmp (ctx -> temp_string, "zx") == 0) ctx -> temp_value = ZERO_RG;
            if (strcmp (ctx -> temp_string, "ax") == 0) ctx -> temp_value = FRST_RG;
            if (strcmp (ctx -> temp_string, "bx") == 0) ctx -> temp_value = SCND_RG;
            if (strcmp (ctx -> temp_string, "cx") == 0) ctx -> temp_value = THRD_RG;
            if (strcmp (ctx -> temp_string, "dx") == 0) ctx -> temp_value = FRTH_RG;
            if (strcmp (ctx -> temp_string, "ex") == 0) ctx -> temp_value = FFTH_RG;
            if (strcmp (ctx -> temp_string, "fx") == 0) ctx -> temp_value = SXTH_RG;
            if (strcmp (ctx -> temp_string, "gx") == 0) ctx -> temp_value = SVNTH_RG;
            if (strcmp (ctx -> temp_string, "hx") == 0) ctx -> temp_value = EGHTH_RG;

            ctx -> type_of_arg = 2;
        }

    else 
        {
        data_asm -> mem_cmd[] (data_asm -> mass_label_struct, ctx -> temp_string);
    return NO_ERROR_;
}



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

        else if (printf ("??? string_for_type = /%s/\n", string_for_type),
                 printf ("str_data[line].str_addr + cnt_rd_sym = /%s/\n ", str_data[line].str_addr + cnt_rd_sym),
                 sscanf ($($(str_data[line].str_addr) + $(cnt_rd_sym)), "%s", string_for_type) == 1){
            mem_cmd[ip++] = Getting_Labels (data_asm ->mass_label_struct, string_for_type);
            printf ("!!! string_for_type = /%s/\n", string_for_type);
        }
            
        ++line;

        fprintf (Log_File, "%ld)Temp_string = %s\n",line, temp_string);
        fprintf (Log_File, "Temp_value = %lf\n", temp_value);