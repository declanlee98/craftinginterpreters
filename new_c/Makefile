CC=clang

all: main

%.o: %.h %.c
	$(CC) -c $^

main: chunk.o debug.o memory.o main.c
	$(CC) -o $@ $^

clean:
	rm *.o *.h.gch main