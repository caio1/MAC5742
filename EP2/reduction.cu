// #include <stdlib.h>
extern "C" { 
	#include "reduction.h"
}

__global__ void reductionGPU(int* d_matrixList, int matrix_size, int totalAmount){

	int id = blockIdx.x * blockDim.x + threadIdx.x;
	if (id < totalAmount*matrix_size){
		printf("totalAmount = %d\n", totalAmount);
		// printf("(%d, %d)\n",id, id + matrix_size*(totalAmount/2));
		printf("%d, %d, : min (%d, %d) \n", id, id + matrix_size*(totalAmount/2),  d_matrixList[id], d_matrixList[id + matrix_size*(totalAmount/2)]);
		d_matrixList[id] = min(d_matrixList[id], d_matrixList[id + matrix_size*(totalAmount/2)]);
	}

}


void reduceOnGPU(int *matrixList, int matrixAmount){
	int totalAmount = nextPowerOfTwo(matrixAmount);
	int *d_matrixList;

	dim3 grid, block;
	block.x = 1024;
	grid.x = (totalAmount + block.x - 1) / block.x;

	int *output = (int*)malloc(9 * sizeof(int));

    cudaSetDevice(0);


	cudaMalloc( (void**)&d_matrixList, totalAmount*sizeof(int) );

	cudaMemcpy( d_matrixList, matrixList, totalAmount*sizeof(int), cudaMemcpyHostToDevice );
	while(totalAmount > 1){

		reductionGPU<<<grid, block>>>(d_matrixList, MATRIX_SIZE, totalAmount);
		cudaDeviceSynchronize();
		// for (int l = 0; l < totalAmount; l++)
		// {
		// 	for (int i = 0; i < MATRIX_SIZE; i++)
		// 	{
		// 		matrixList[MATRIX_SIZE * l + i] = min(matrixList[MATRIX_SIZE * l + i], matrixList[MATRIX_SIZE * ((totalAmount/2) + l) + i]);
		// 	}
		// }
		totalAmount /= 2;
		grid.x = (totalAmount + block.x - 1) / block.x;
	}
	cudaMemcpy( output, d_matrixList, MATRIX_SIZE*sizeof(int), cudaMemcpyDeviceToHost );


	printMatrix(output, MATRIX_WIDTH, MATRIX_WIDTH);
}