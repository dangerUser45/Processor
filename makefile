Compiler = g++
B = build_proc_asm/

#-----------------------------------------------------------------------

asm : $(B)Asm.o  $(B)Debug.o  $(B)Stack.o  $(B)Print.o  $(B)Processing.o  $(B)Debug_proc.o  $(B)TXLib.o  
	$(Compiler)  $(B)Asm.o  $(B)Debug.o  $(B)Stack.o  $(B)Print.o  $(B)Processing.o  $(B)TXLib.o -o asm.exe

proc :  $(B)Proc.o  $(B)Proc_run.o  $(B)Debug.o  $(B)Stack.o  $(B)Print.o  $(B)Processing.o  $(B)Debug_proc.o  $(B)TXLib.o
	$(Compiler)  $(B)Proc.o  $(B)Proc_run.o  $(B)Debug.o  $(B)Stack.o  $(B)Print.o  $(B)Processing.o  $(B)Debug_proc.o  $(B)TXLib.o -o proc.exe

#-----------------------------------------------------------------------

$(B)Asm.o : asm.cpp \
		Stack_for_proc/Stack_Common.h \
		Asm.h \
		Onegin_for_proc/Onegin_processing.h \
		Onegin_for_proc/Onegin_General.h \
		Onegin_for_proc/Print.h \
		Stack_for_proc/Debug.h \
		Enum_proc.h
	$(Compiler) -c asm.cpp -o $(B)asm.o
		
$(B)Proc.o : Proc.cpp \
		Machine.h Stack_for_proc/Stack_Common.h Stack_for_proc/Stack.h Stack_for_proc/Debug.h \
		Asm.h Proc_common.h Proc_run.h Onegin_for_proc/Onegin_processing.h
	$(Compiler) -c proc.cpp -o $(B)proc.o

$(B)Proc_run.o : Proc_run.cpp
	$(Compiler) -c Proc_run.cpp -o $(B)Proc_run.o

$(B)Debug.o : Stack_for_proc/Debug.cpp
	$(Compiler) -c Stack_for_proc/Debug.cpp -o $(B)Debug.o

$(B)Stack.o : Stack_for_proc/Stack.cpp
	$(Compiler) -c Stack_for_proc/Stack.cpp -o $(B)Stack.o

$(B)Print.o : Onegin_for_proc/Print.cpp
	$(Compiler) -c  Onegin_for_proc/print.cpp -o $(B)print.o

$(B)Processing.o : Onegin_for_proc/Processing.cpp
	$(Compiler) -c Onegin_for_proc/processing.cpp -o $(B)processing.o

$(B)Debug_proc.o : Debug_proc.cpp
	$(Compiler) -c debug_proc.cpp -o $(B)debug_proc.o

$(B)TXLib.o : TXLib.cpp
	$(Compiler) -c TXLib.cpp -o $(B)TXLib.o

#-----------------------------------------------------------------------

clean :
	del build_proc_asm\*.o
