#include "Machine.h"
#include "Proc_common.h"
#include "Stack_for_proc\Stack_Common.h"

int Dump_proccessor (const SPU* data_proc, const char* name_calling);
int Dump_St (stack_t* stk);
const char* Dizassembler (el_t cmd, int* addr_ip);
