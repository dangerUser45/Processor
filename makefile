Compiler = g++

asm : Asm.o Debug.o Stack.o Print.o Processing.o Debug_proc.o
	$(Compiler) Asm.o Debug.o Stack.o Print.o Processing.o -o asm

proc : Proc.o Proc_run.o Debug.o Stack.o Print.o Processing.o Debug_proc.o
	$(Compiler) Proc.o Proc_run.o Debug.o Stack.o Print.o Processing.o Debug_proc.o -o proc


Asm.o : asm.cpp
	$(Compiler) -c asm.cpp -o asm.o
		
Proc.o : Proc.cpp
	$(Compiler) -c proc.cpp -o proc.o

Proc_run.o : Proc_run.cpp
	$(Compiler) -c Proc_run.cpp -o Proc_run.o

Debug.o : Stack_for_proc\Debug.cpp
	$(Compiler) -c Stack_for_proc\Debug.cpp -o Debug.o

Stack.o : Stack_for_proc\Stack.cpp
	$(Compiler) -c Stack_for_proc\Stack.cpp -o Stack.o

Print.o : Onegin_for_proc\Print.cpp
	$(Compiler) -c  Onegin_for_proc\print.cpp -o print.o

Processing.o : Onegin_for_proc\Processing.cpp
	$(Compiler) -c Onegin_for_proc\processing.cpp -o processing.o

Debug_proc.o : Debug_proc.cpp
	$(Compiler) -c debug_proc.cpp -o debug_proc.o


clean :
	del *.o
