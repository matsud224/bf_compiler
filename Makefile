CFLAGS := -Wall -O2

bf_compiler: main.o
	g++ -o bf_compiler main.o

clean:
	$(RM) *.o
	$(RM) bf_compiler

