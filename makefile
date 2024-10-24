Target = asm
Compiler = g++

$(Target) : Asm.o Debug.o Stack.o Print.o Processing.o 
	$(Compiler) Main.o Debug.o -o $(Target)

Asm.o : asm.cpp
	$(Compiler) -c asm.cpp -o asm.o

Debug.o : Debug.cpp
	$(Compiler) -c Stack_for_proc\Debug.cpp -o Debug.o

Stack.o : Stack.cpp
	$(Compiler) -c Stack_for_proc\Stack.cpp -o Stack.o

Print.o : Print.cpp
	$(Compiler) -c  Onegin_for_proc\print.cpp -o print.o

Processing.o : Processing.cpp
	$(Compiler) -c Onegin_for_proc\processing.cpp -o processing.o
	
clean :
	del *.o



g++ asm.cpp Stack_for_proc\Debug.cpp Stack_for_proc\Stack.cpp Onegin_for_proc\print.cpp Onegin_for_proc\Processing.cpp