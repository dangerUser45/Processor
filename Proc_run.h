#pragma once

extern FILE* Log_File;

int Load_code (SPU* data_proc, FILE* code_text, el_t* buffer, size_t size);
int Dump_proccessor (const SPU* data_proc);
int Run (SPU* data_for_proc);
int Jump (el_t* code, int* ip);
int Ctor_for_proc (SPU* data_for_proc);
int Dtor_for_proc (SPU* data_for_proc);
int Dump_St (stack_t* stk);

