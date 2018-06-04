CC=gcc-8
# CFLAGS=-I.
# CFLAGS  = -march=native -flto -g -Wall -pedantic -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast
CFLAGS  = -g -Wall -pedantic -fopenmp
DEPS = functions.h iofunctions.h
LDFLAGS = -lpthread -lm 
OBJ = main.o functions.o iofunctions.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	gcc-8 -o $@ $^ $(CFLAGS) $(LDFLAGS)
	./main 1000x1000 1000x1000 matrixC

.PHONY: clean
clean:
	rm -f *.o main