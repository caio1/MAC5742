CC=gcc
CFLAGS=-I.
DEPS = desafio1.h
OBJ = desafio1.o functions.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

desafio1: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
