#pragma once

#include <stdio.h>

#include "Stack_Common.h"

int Create_file (const char*);
int Close_file (FILE* );
int Dump (stack_t* Data);
int Canary (stack_t* Data);
int Fill_Poison (stack_el_t* begin, uint_t quantity);
int Decoder_error (stack_t* Data, int error, int line, const char* name_func);
int Verificator (stack_t* Data);
uint_t Hash (const void* ptr, size_t size);

extern FILE* Log_File;
