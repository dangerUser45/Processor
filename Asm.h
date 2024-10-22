struct ASM;
struct STRING;
struct ONEGIN;

int Processing_Command (ASM* data_asm, STRING* str_data, long size);
int Dump (ASM* str_data, ONEGIN* data);
int Asm_Ctor (ASM* data_asm, long size);
int Asm_Dtor (void* pointer);

typedef double el_t;

struct ASM  
{
    const char* nm_orig_f;
    const char* nm_fnl_f;
    FILE* orig_file;
    FILE* final_file;
    size_t size_of_file;
    el_t* mem_cmd;
    long size_mem_cmd;
};

struct label
{

};




