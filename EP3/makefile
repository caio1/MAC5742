CC=mpicc
CFLAGS  = -O3 -march=native -flto -g -Wall -pedantic
CUDAFLAGS  = -O3 -Xptxas --opt-level=3
DEPS = helperFunctions.h CPUImplementations.h
LDFLAGS = -lpthread -lm -I/usr/local/cuda-9.1/include -L/usr/local/cuda-9.1/lib64 -lcudart
OBJ = main.o helperFunctions.o CPUImplementations.o GPUImplementation.o

%.o: %.cu $(DEPS) GPUImplementation.h
	nvcc -c -o $@ $< $(CUDAFLAGS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f *.o main