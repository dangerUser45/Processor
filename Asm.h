struct ASM;
int Processing_Command (ASM* data_asm);
int Dump (ASM* str_data);

struct ASM  
{
    const char* nm_orig_f;
    const char* nm_fnl_f;
    FILE* orig_file;
    FILE* final_file;
    size_t size_of_file;

};

struct label
{

};

struct ASM_DBG
{
    const char* name_log_file;
};

typedef int el_t;


