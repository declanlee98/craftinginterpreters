CC=clang

all: main

%.o: %.h %.c
	$(CC) -c $^

main: compiler.o scanner.o value.o chunk.o memory.o vm.o debug.o object.o main.c

clean:
	rm *.o *.h.gch main