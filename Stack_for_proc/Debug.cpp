#include "Common.h"
#include "Debug.h"

FILE* Log_File = 0;

int Create_file ()
{
    const char* StackLogFile = "StackLog.txt";

    if ((Log_File = fopen(StackLogFile, "w+")) == NULL)
    {
        fprintf (stdout, "Не удается открыть файл %s\n", StackLogFile) ;
        return 0;
    }
    setvbuf (Log_File, 0, 0, _IONBF);
    
    return NO_ERROR;/* code_error */
}

int Close_file ()
{
    fclose (Log_File);
    Log_File = NULL;
    return NO_ERROR;
}
//==================================================================================================
int Dump (stack_t* Data)
{

    FILE* fp = Log_File;
    assert (fp);
    fprintf (fp, "//================================================================================================\n");

    fprintf (fp, "\tSTRUCT:\n");

    if (Data == NULL)
    {
        fprintf (Log_File, "Data = NULL\n");
        return BAD_POINTER;
    }


    ONDEBUG(fprintf (fp, "  canary1_struct = %d\n", Data -> canary1_struct);)
    ONDEBUG(fprintf (fp, "  name of struct = %s\n", Data -> name);)
    fprintf (fp, "  buffer = %p\n", Data -> buffer);
    fprintf (fp, "  size = %zd\n", Data -> size);
    fprintf (fp, "  capacity = %zd\n", Data -> capacity);
    ONDEBUG(fprintf (fp, "  canary2_struct = %d\n", Data -> canary2_struct);)

    if (Data -> buffer == NULL) 
    {
        fprintf (fp,"//================================================================================================\n");
        return BUFFER_NULL;
    }

    fprintf (fp, "\t\t\t\tSTACK:\n");
    ONDEBUG(fprintf (fp, "\tcanary1_buf) <%016d> --- address: %p\n", Data -> buffer[0], Data -> buffer);)
    for (ssize_t i = 0 ONDEBUG(+ 1); i < Data -> capacity ONDEBUG(+ 1); ++i)
        fprintf (fp, "\t\t  %zd) <%016d> --- address: %p\n", i, Data -> buffer[i], Data -> buffer + i);
    ONDEBUG(fprintf (fp, "\tcanary2_buf) <%016d> --- address: %p\n", Data -> buffer[Data -> capacity + 1], Data -> buffer + Data -> capacity + 1);)
    fprintf (fp, "\n");
    fprintf (fp,"//================================================================================================\n");
    return 0;
}
//==================================================================================================
int Canary (stack_t* Data)
{
    Data -> buffer[0] = CANARY_B;
    Data -> buffer[Data -> capacity + 1] = CANARY_B;

    return 0;
}
//==================================================================================================
int Fill_Poison (stack_el_t* begin, uint_t quantity)
{
    for (uint_t i = 0; i < quantity; ++i)
        begin[i] = POISON;

    return 0;
}
//==================================================================================================
int Verificator (stack_t* Data)
{
    int error = 0;
    if (Data == NULL)
    {
        error = error | BAD_POINTER;
        return error;
    }

    if (Data->buffer == NULL)               // 1111'1111
        error = error | BUFFER_NULL;     // 1 csb
    else
    {
        if (Data -> buffer[0] != CANARY_B)
            error = error | BAD_CANARY1_B;

        if (Data -> buffer[Data -> capacity + 1] != CANARY_B)
            error = error | BAD_CANARY2_B;
        if (Data->size < 0)
            error = error | BAD_SIZE;     // 2

        /*uint_t hash_struct = Hash (Data, sizeof (stack_t));
        uint_t hash_buffer = Hash (Data -> buffer, Data -> (capacity + 2) * sizeof (stack_el_t));

        if (Data -> hash_struct != ???)//!!!
            error = error | BAD_HASH_STRUCT;

        if (Data -> hash_bufer != hash_buffer)//!!!
            error = error | BAD_HASH_BUF;*/      //!!! finish it

    }

    if (Data ->capacity < 0)
        error = error | BAD_CAPACITY;     // 3

    if (Log_File == NULL)
        error = error | FILE_NULL;     // 4

    ONDEBUG(if (Data -> canary1_struct != CANARY_S)
        error = error | BAD_CANARY1_S;)     // 5

    ONDEBUG(if (Data -> canary2_struct != CANARY_S)
        error = error | BAD_CANARY2_S;)     // 6

    return error;
}
//==================================================================================================
int Decoder_error (stack_t* Data, int error, int line, const char* name_func)
{
    ASSERT_
    fprintf (Log_File, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    fprintf (Log_File, "\tERRORS  in  line: %d\n\tFunction: %s\n", line, name_func);

    if (error & BUFFER_NULL)
        fprintf (Log_File, "Buffer is BAD: buffer = %p\n", Data -> buffer);

    if (error & BAD_SIZE)
        fprintf (Log_File, "Size is BAD: size = %zd\n", Data -> size);

    if (error & BAD_CAPACITY)
        fprintf (Log_File, "Capacity is BAD: capacity = %zd\n",Data -> capacity);

    if (error & FILE_NULL)
        fprintf (Log_File, "File pointer = NULL: file pointer = %p\n", Log_File);

    ONDEBUG(if (error & BAD_CANARY1_S)
        fprintf (Log_File, "Canary1_struct is BAD: canary1_struct = %d\n", Data -> canary1_struct);)

    ONDEBUG(if (error & BAD_CANARY2_S)
        fprintf (Log_File, "Canary2_struct is BAD: canary2_struct = %d\n", Data -> canary2_struct);)

    ONDEBUG(if (error & BAD_CANARY1_B)
        fprintf (Log_File, "Canary1_buf is BAD: canary1_buf = %d\n", Data -> buffer[0]);)

    ONDEBUG(if (error & BAD_CANARY2_B)
        fprintf (Log_File, "Canary2_buf is BAD: canary2_buf = %d\n", Data -> buffer[Data -> capacity + 1]);)

    ONDEBUG(if (error & BAD_HASH_STRUCT)
         fprintf (Log_File, "Hash_struct is BAD: hash_struct = %llu\n", Data -> hash_struct);)

    ONDEBUG(if (error & BAD_HASH_BUF)
         fprintf (Log_File, "Hash_buf is BAD: hash_buf = %llu\n", Data -> hash_buffer);)

    if (error == 0)
        fprintf (Log_File, "All it is OK\n");

    fprintf (Log_File, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    return error;
}
//==================================================================================================
uint_t Hash (const void* ptr, size_t size)
{
    uint_t hash = 5381;
    const char* data = (const char*) ptr;
    for (uint_t i = 0; i < size; ++i)
        hash = hash * 33 ^ data[i];
    return hash;
}
//==================================================================================================
