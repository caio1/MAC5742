CC=gcc
CFLAGS  = -O3 -march=native -flto -g -Wall -pedantic
DEPS = helperFunctions.h ioFunctions.h reduction.h
LDFLAGS = -lpthread -lm
OBJ = main.o helperFunctions.o ioFunctions.o

%.o: %.cu $(DEPS)
	$(CC) -c -o $@ $< #$(CFLAGS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< #$(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f *.o main