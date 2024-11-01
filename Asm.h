#pragma once 

#include "Machine.h"
#include <stdio.h>
#include <stdlib.h>

struct ASM;
struct STRING;
struct ONEGIN;

int Processing_Command (ASM* data_asm, STRING* str_data, long size);
int Dump (ASM* str_data, ONEGIN* data);
int Asm_Ctor (ASM* data_asm, long size);
int Asm_Dtor (void* pointer);
int Fill_Code_file (ASM* data_asm, const char* name);

struct label
{
  const char* name_of_label;
  int* addr; 
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
