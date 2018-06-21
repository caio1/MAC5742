CC=nvcc
CFLAGS  = -O3 -march=native -flto -g -Wall -pedantic -fopenmp
DEPS = helperFunctions.h ioFunctions.h reduction.h
LDFLAGS = -lpthread -lm
OBJ = main.o helperFunctions.o ioFunctions.o reduction.o

%.o: %.cu $(DEPS)
	$(CC) -c -o $@ $< #$(CFLAGS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< #$(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ #$(CFLAGS) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f *.o main