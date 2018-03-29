CC=gcc
CFLAGS=-I.
DEPS = miniEP1.h
OBJ = miniEP1.o sumMatrices.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

miniEP1: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
