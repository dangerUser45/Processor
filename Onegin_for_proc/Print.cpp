#include "Onegin_General.h"
#include "Print.h"

void DBG_Print (ONEGIN* file)
{
    long fsize = file->fsize;

    fprintf(Log_File, "=============================================================================\n");
    for(int i = 0; i < fsize+1; i++)
        if (file->buffer_addr[i] == '\n')
            fprintf(Log_File, "<font color=#00af8c>symbol = &lt;\\n&gt;</font>, addr = %llu\n", file->buffer_addr + i);
        else if(file->buffer_addr[i] == '\r')
            fprintf(Log_File, "symbol = &lt;\\r&gt;, addr = %llu\n", file->buffer_addr + i);
        else if(file->buffer_addr[i] == '\0')
           fprintf(Log_File, "symbol = &lt;\\0&gt;, addr = %llu\n", file->buffer_addr + i );
        else
        fprintf(Log_File, "Symbol = &lt;<font face=sans-serif>%c</font>&gt;, his addr = %llu\n", file->buffer_addr[i], file->buffer_addr + i);
    fprintf(Log_File, "=============================================================================\n");
}
//=============================================================================