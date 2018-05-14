CC=gcc
# CFLAGS=-I.
# CFLAGS  = -march=native -flto -g -Wall -pedantic -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast
CFLAGS  = -g -Wall -pedantic
DEPS = 
LDFLAGS = -lpthread -lm
OBJ = main.o functions.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(CFLAGS)

main: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
	./main testMatrix1 testMatrix2 matrixC

.PHONY: clean
clean:
	rm -f *.o main