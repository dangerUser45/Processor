Compiler = g++

asm : Asm.o Debug.o Stack.o Print.o Processing.o 
	$(Compiler) Asm.o Debug.o Stack.o Print.o Processing.o -o asm

proc: 
	$(Compiler) proc.cpp proc_run.cpp Stack_for_proc\debug.cpp Onegin_for_proc\Processing.cpp  Onegin_for_proc\print.cpp Stack_for_proc\stack.cpp -o proc

Asm.o : asm.cpp
	$(Compiler) -c asm.cpp -o asm.o

Debug.o : Stack_for_proc\Debug.cpp
	$(Compiler) -c Stack_for_proc\Debug.cpp -o Debug.o

Stack.o : Stack_for_proc\Stack.cpp
	$(Compiler) -c Stack_for_proc\Stack.cpp -o Stack.o

Print.o : Onegin_for_proc\Print.cpp
	$(Compiler) -c  Onegin_for_proc\print.cpp -o print.o

Processing.o : Onegin_for_proc\Processing.cpp
	$(Compiler) -c Onegin_for_proc\processing.cpp -o processing.o
	
clean :
	del *.o
