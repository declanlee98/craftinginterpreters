CC=clang

all: main

%.o: %.h %.c
	$(CC) -c $^

main: compiler.o scanner.o value.o chunk.o table.o memory.o vm.o debug.o object.o main.c
	$(CC) -o $@ $^

clean:
	rm *.o *.h.gch main