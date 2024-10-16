#include <stdio.h>
#include <stdlib.h>
#include "Stack_for_proc\Stack.h"
#include "Proc_run.h"

int main (int argc, char* argv[])
{
    int buffer[100] = {};
    Load_code (argv[1], buffer, 100);
    
    Run ();
    return 0;
}