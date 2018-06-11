CC=gcc
CFLAGS  = -O3 -march=native -flto -g -Wall -pedantic -fopenmp
DEPS = helperFunctions.h ioFunctions.h
LDFLAGS = -lpthread -lm 
OBJ = main.o helperFunctions.o ioFunctions.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f *.o main