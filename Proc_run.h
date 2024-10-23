#pragma once

extern FILE* Log_File;

int Load_code (SPU* data_proc, FILE* code_text, el_t* buffer, size_t size);
int Dump_proccessor (SPU* data_proc);
void Run ();