CC=clang

all: main

%.o: %.h %.c
	$(CC) -c $^

main: chunk.o compiler.o debug.o memory.o scanner.o value.o vm.o main.c
	$(CC) -o $@ $^

clean:
	rm *.o *.h.gch main