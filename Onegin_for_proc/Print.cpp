#include "General.h"
#include "Print.h"

void DBG_Print (ONEGIN* file)
{
    long fsize = file->fsize;

    printf("=============================================================================\n");
    for(int i = 0; i < fsize+1; i++)
        if (file->buffer_addr[i] == '\n')
            printf("symbol = <\\n>, addr = %llu\n", file->buffer_addr + i);
        else if(file->buffer_addr[i] == '\r')
            printf("symbol = <\\r>, addr = %llu\n", file->buffer_addr + i);
        else if(file->buffer_addr[i] == '\0')
           printf("symbol = <\\0>, addr = %llu\n", file->buffer_addr + i );
        else
        printf("Symbol = <%c>, his addr = %llu\n", file->buffer_addr[i], file->buffer_addr + i);
    printf("=============================================================================\n");
}
//=============================================================================
