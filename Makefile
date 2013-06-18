all:
	gcc common_64bit/cpuidc64.c -m64 -c -o cpuidc64.o
	gcc memory.c -I./common_64bit -m64 -c -o memory.o
	gcc randmem.c -I./common_64bit -m64 -c -o randmem.o
	gcc -DBIT_VERSION_64 randmem.o cpuidc64.o memory.o -I./common_64bit -m64 -lrt -lc -lm -O3 -o randmem64.out

32bit: 
	gcc common_32bit/cpuidc.c -c -o cpuidc.o
	gcc memory.c -I./common_32bit -c -o memory.o
	gcc randmem.c -I./common_32bit -c -o randmem.o
	gcc -DBIT_VERSION_32 cpuidc.o memory.o randmem.o -lrt -lc -lm -O3 -o randmem32.out

solaris: 
	gcc common_solaris/cpuidc.c -c -o cpuidc.o
	gcc memory.c -I./common_solaris -c -o memory.o
	gcc randmem.c -I./common_solaris -c -o randmem.o
	gcc -DBIT_VERSION_SOLARIS cpuidc.o memory.o randmem.o -L/usr/lib/ -lrt -lc -lm -O3 -o randmem.out


clean:
	rm *.o *.out

