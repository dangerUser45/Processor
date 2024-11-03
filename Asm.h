#pragma once 

#include "Machine.h"
#include <stdio.h>
#include <stdlib.h>

struct ASM;
struct STRING;
struct ONEGIN;
struct label;
  
int Processing_Command (ASM* data_asm, STRING* str_data, long size);
int Dump (ASM* str_data);
int Asm_Ctor (ASM* data_asm, long size);
int Asm_Dtor (void* pointer);
int Fill_Code_file (ASM* data_asm, const char* name);
int Ctor_Labels (ASM* data_asm);
int Add_Label (label* mass_label_struct, const char* name_label, int ip);
int Getting_Labels (label* mass_for_label, const char* name_of_label);
int Dump_of_label (label* mass_label_struct);
int Dtor_Labels (ASM* data_asm);

struct label    
{
  const char* name_of_label;
  int addr;
};

struct ASM_Context
{
  long line;
  long ip;
  char* current_string;

  int cnt_rd_sym= 0;
  int type_of_arg = 0;

  char temp_string [20] = "";
  el_t temp_value = 0;
};

struct ASM  
{
    const char* nm_orig_f;
    const char* nm_fnl_f;
    FILE* orig_file;
    FILE* final_file;
    size_t size_of_file;
    el_t* mem_cmd;
    long size_mem_cmd;
    long final_ip;

    label* mass_label_struct;

};

const int INIT_NUM_LABELS = 10;
