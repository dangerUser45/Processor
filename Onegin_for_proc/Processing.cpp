#include "Onegin_General.h"
#include "Onegin_Processing.h"
#include "Print.h"

void File_Common (ONEGIN* file)
{
    assert(file);

    long fsize = file->fsize = file_size (file->name);
    dbg printf("fsize = %llu\n", fsize);
    Check_fsize (fsize);
    Read_File (file);

    Strings_Number (file);
    Address_String (file);
}
//=============================================================================
long file_size (const char* name)
{
    assert(name);

    struct stat stbuf = {};
    stat(name, &stbuf);
    return stbuf.st_size;
}
//=============================================================================
void Strings_Number (ONEGIN* file)
{
    char* buffer_addr = file-> buffer_addr;
    assert (buffer_addr);

    buffer_addr[file->fsize] = '\n';
    long fsize = file->fsize;

    long string_quantity = 0;
    for (int i = 0; i < fsize; i++)
    {
        if (*buffer_addr == '\r')
            *buffer_addr = '\0';
        if (*buffer_addr == '\n')
            string_quantity++;
        buffer_addr++;
    }
    __danya_back( DBG_Print (file);)
    file->string_quantity = string_quantity;
}
//=============================================================================
void Check_fsize (long fsize)
{
    if (fsize == 0)
    {
        fprintf(stderr, "Error: empty file");
        exit(-1);
    }
}
//=============================================================================
void Read_File (ONEGIN* file)
{
    assert(file);

    FILE* fp = fopen (file->name, "rb");
    assert(fp);

    long fsize = file->fsize;

    char* buffer_addr = file->buffer_addr = (char*) calloc(fsize + 1 , sizeof(char));

    fread(buffer_addr, sizeof(char), fsize + 1, fp);
    dbg fprintf(Log_File, "READ_file: addr buffer_adr = %llu\n", buffer_addr);

    fclose (fp);
    assert(fp);
}
//=============================================================================
void Check_argc (int argc)
{
    if (argc != 2)
    {
        fprintf (stderr, "Error: incorrect number of arguments\n");
        exit(1);
    }
}
//=============================================================================
void Address_String (ONEGIN* file)
{
    STRING* str_data = file->str_data = (STRING*)calloc ((file->string_quantity), sizeof(STRING));
    assert(str_data);

    char* buffer_addr = file->buffer_addr;
    long n_string = 1;
    long fsize = file->fsize;
    str_data[0].str_addr = buffer_addr;

    dbg fprintf(Log_File, "  ADDR_STR str_data = %llu\n", str_data);
    dbg fprintf(Log_File, "ADDR_STR: adrr begin str = %llu\n", str_data[0].str_addr);

    for (int i = 0; i < fsize - 1; i++)
    {
        if (*buffer_addr == '\n')
        {
            str_data[n_string-1].end_addr = buffer_addr;
            str_data[n_string].str_addr = buffer_addr+1;

            dbg fprintf(Log_File, "ADDR_STR: adrr end str = %llu\n", str_data[n_string-1].end_addr);
            dbg fprintf(Log_File, "ADDR_STR: adrr begin str = %llu\n", str_data[n_string].str_addr);

            n_string++;
        }
        buffer_addr++;
    }
    str_data[n_string-1].end_addr = buffer_addr;

    dbg fprintf(Log_File, "ADDR_STR: adrr end str = %llu\n", str_data[n_string-1].end_addr);
    dbg fprintf(Log_File, "addr buffer_addr = %llu\n", buffer_addr);
    dbg fprintf(Log_File, "buffer_addr[file->fsize-1] = &lt;%c&gt;\n", buffer_addr[file->fsize-1]);
    dbg fprintf(Log_File, "buffer_addr[file->fsize-1] = &lt;%c&gt;\n", buffer_addr[file->fsize-1]);
    dbg fprintf(Log_File, "file->buffer_addr[file->fsize-1] = &lt;%c&gt;\n", file->buffer_addr[file->fsize-1]);
    dbg fprintf(Log_File, "file->buffer_addr[file->fsize] = &lt%c&gt;\n",   file->buffer_addr[file->fsize]);

}
//=============================================================================
void Free (ONEGIN* file)
{
    free (file->buffer_addr);
    free (file->str_data);

    assert (file->buffer_addr);
    assert (file->str_data);
}
