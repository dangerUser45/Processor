
#include "Stack_Common.h"
#include "Stack.h"
#include "Debug.h"
                                                                                                   
int Stack_Ctor (stack_t* Data, ssize_t capacity ONDEBUG(, const char* name, const char* file, int line))
{
    if (Data == NULL) return BAD_POINTER;
    if (capacity <= 0) return BAD_CAPACITY;

    Data -> capacity = capacity;
    Data -> size = 0;
    stack_el_t* buffer = (stack_el_t*) calloc (capacity ONDEBUG(+ 2), sizeof (stack_el_t));

    if (buffer == NULL) return BUFFER_NULL;
    Data -> buffer = buffer;
    fprintf (Log_File, "data-> buffer = %p\n", Data -> buffer); // !!!
    ONDEBUG (Data -> canary1_struct = CANARY_S;)
    ONDEBUG (Data -> name = name;)
    ONDEBUG (Data -> file = file;)
    ONDEBUG (Data -> line = line;)
    ONDEBUG (Data -> canary2_struct = CANARY_S;)
    ONDEBUG (Canary (Data);)

    ONDEBUG (Fill_Poison (Data -> buffer + Data -> size + 1, Data -> capacity);)

    CHECK ( , "Stack_Ctor")

    return NO_ERROR_;
}

//==================================================================================================
int Stack_Push (stack_t* Data, stack_el_t elem)
{
    CHECK (return GENERAL_ERROR;, "Stack_Push")

    if (Data -> size >= Data -> capacity - 1)
    {
        fprintf (Log_File, "its realloc up\n");
        Stack_Realloc_Up (Data);
        ONDEBUG (Fill_Poison (Data -> buffer + Data -> size + 1, Data -> capacity);)
        ONDEBUG (Canary (Data);)
    }
    ONDEBUG (fprintf (Log_File, "\t\t\tsize = %zd\n", Data -> size);)
    ssize_t size = Data->size;
    Data -> buffer [size  ONDEBUG( + 1)] = elem;
    Data -> size += 1;

    CHECK (return GENERAL_ERROR;, "Stack_Push")

    return NO_ERROR_;
}
//==================================================================================================
int Stack_Pop (stack_t* Data, stack_el_t* pop_value)
{

    CHECK ( , "Stack_Pop")
    fprintf (Log_File, "HERE size = %zd\n", Data -> size); // !!!

    if (Data -> size <= 0) return BAD_SIZE;
    ONDEBUG (fprintf (Log_File, "RTRTRTR\n");) //!!!
    if (Data -> size < Data -> capacity / (MAGIC_NUM * MAGIC_NUM) )
    {
        fprintf (Log_File, "Its realloc_down\n"); // !!!
        Stack_Realloc_Down (Data);
        ONDEBUG (Fill_Poison (Data -> buffer + Data -> size + 1, Data -> capacity);)
        ONDEBUG (Canary (Data);)
    }

    ssize_t size = Data -> size;
    fprintf (Log_File, "size = %zd\n", size); // !!!
    fprintf(Log_File, "addr_popa = %p\n",  Data -> buffer +size ); // !!!

    *pop_value = Data -> buffer [size - 1 ONDEBUG (+1)];
    Data -> buffer [size - 1 ONDEBUG (+1)] = POISON;
    Data -> size -= 1;
    CHECK ( , "Stack_Pop")

    return NO_ERROR_;
}
//==================================================================================================
int Stack_Dtor (stack_t* Data)
{
   
    CHECK (return GENERAL_ERROR;, "Stack_Dtor")
     

    Fill_Poison (Data -> buffer ONDEBUG(+1), Data -> capacity);
    Stack_free (&Data -> buffer);

    ONDEBUG (fprintf(Log_File, "�����������\n");)

    CHECK ( , "Stack_Dtor") // noreturn because use after free () !!!

    return NO_ERROR_;
}
//==================================================================================================

#define PLEASE_NOTE_THAT_DNLX_DID_THAT(...) __VA_ARGS__

int Stack_Realloc_Up (stack_t* Data)
{
    CHECK ( , "Stack_Realloc_Up") //
    Data -> buffer = (stack_el_t*) realloc (Data -> buffer,
                                            PLEASE_NOTE_THAT_DNLX_DID_THAT ((Data -> capacity * MAGIC_NUM + 2) * sizeof (Data->capacity))); //capacity is
    Data -> capacity = Data ->capacity * MAGIC_NUM;

    CHECK ( , "Stack_Realloc_Up")
    return NO_ERROR_;
}
#undef PLEASE_NOTE_THAT_DNLX_DID_THAT

//==================================================================================================
int Stack_Realloc_Down (stack_t* Data)
{
    CHECK ( , "Stack_Realloc_Down")
    Data -> buffer = (stack_el_t*) realloc (Data -> buffer, (Data -> capacity * MAGIC_NUM + 2) * sizeof (Data->capacity));
    Data -> capacity = Data -> capacity / (MAGIC_NUM * MAGIC_NUM);
    CHECK ( , "Stack_Realloc_Down")

    return NO_ERROR_;
}
//==================================================================================================
int Stack_free (void* ptr)
{
    stack_t** Data = (stack_t**) ptr;
    if (*Data != NULL)
    {
        printf ("HERE\n");
        free (*Data);
        *Data = NULL;
    }
    return NO_ERROR_;
}
//==================================================================================================
