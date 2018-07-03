// #include <stdlib.h>
extern "C" {
	#include "reduction.h"
}

__device__ int gpu_min(int x, int y){
	return y ^ ((x ^ y) & -(x < y));
}

__global__ void reductionGPU(int* d_matrixList, int matrix_size, int totalAmount){

	int id = blockIdx.x * blockDim.x + threadIdx.x;
	if (id < (totalAmount/2)){
		d_matrixList[id] = gpu_min(d_matrixList[id], d_matrixList[id + (totalAmount/2)]);
	}

}


int* reduceOnGPU(int *matrixList, int matrixAmount){
	int totalAmount = nextPowerOfTwo(matrixAmount);
	int *d_matrixList;

	totalAmount = totalAmount*MATRIX_SIZE;

	dim3 grid, block;
	block.x = 1024;
	grid.x = (totalAmount + block.x - 1) / block.x;

	int *output = (int*)malloc(MATRIX_SIZE * sizeof(int));

    cudaSetDevice(1);

	cudaMalloc((void**)&d_matrixList, totalAmount*sizeof(int));

	cudaMemcpy(d_matrixList, matrixList, totalAmount*sizeof(int), cudaMemcpyHostToDevice);
	while(totalAmount > MATRIX_SIZE){

		reductionGPU<<<grid, block>>>(d_matrixList, MATRIX_SIZE, totalAmount);
		cudaDeviceSynchronize();

		totalAmount /= 2;
		grid.x = (totalAmount + block.x - 1) / block.x;
	}
	cudaMemcpy(output, d_matrixList, MATRIX_SIZE*sizeof(int), cudaMemcpyDeviceToHost);

	cudaFree(matrixList);

	printMatrix(output, MATRIX_WIDTH, MATRIX_WIDTH);

	return output;
}