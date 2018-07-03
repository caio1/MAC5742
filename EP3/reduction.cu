// #include <stdlib.h>
extern "C" {
	#include "reduction.h"
}

__device__ int gpu_min(int x, int y){
	return y ^ ((x ^ y) & -(x < y));
}

// __device__ double randomSampleGPU(double min, double max)
// {
// 	double range = (max - min);
// 	double div = RAND_MAX / range;
// 	return min + (rand() / div);
// }

__global__ void create_f_array(double* f_array, double* f_squared_array, double* samples, int64_t n){
	int id = blockIdx.x * blockDim.x + threadIdx.x;
	if (id < n){
		double sample = samples[id];
		f_array[id] = sample;
		f_squared_array[id] = sample; 
	}
}

__global__ void reductionGPU(double* f_array, double* f_squared_array, int64_t totalAmount){

	int id = blockIdx.x * blockDim.x + threadIdx.x;
	if (id < (totalAmount/2)){
		f_array[id] = f_array[id] + f_array[id + (totalAmount/2)];
		f_squared_array[id] = f_squared_array[id] + f_squared_array[id + (totalAmount/2)];
	}

}

double integral(double a, double b, double sig)
{
	return (b - a) * (f + sig * sqrt((fsquared - pow(f, 2)) / N));
}


void reduceOnGPU(){
	int64_t totalAmount = nextPowerOfTwo(N);
	double *d_f_array;
	double *d_f_squared_array;
	double *d_samples;


	dim3 grid, block;
	block.x = 1024;
	grid.x = (totalAmount + block.x - 1) / block.x;

    cudaSetDevice(1);

	cudaMalloc((void**)&d_samples, N*sizeof(double));
	cudaMalloc((void**)&d_f_array, totalAmount*sizeof(double));
	cudaMalloc((void**)&d_f_squared_array, totalAmount*sizeof(double));

	cudaMemset(d_f_array, 0, totalAmount*sizeof(double));
	cudaMemset(d_f_squared_array, 0, totalAmount*sizeof(double));
	cudaMemcpy(d_samples, samples, N*sizeof(double), cudaMemcpyHostToDevice);


	create_f_array<<<grid, block>>>(d_f_array, d_f_squared_array, d_samples, N);

	while(totalAmount > 1){

		reductionGPU<<<grid, block>>>(d_f_array, d_f_squared_array, totalAmount);
		cudaDeviceSynchronize();

		totalAmount /= 2;
		grid.x = (totalAmount + block.x - 1) / block.x;
	}
	cudaMemcpy(&f, d_f_array, sizeof(double), cudaMemcpyDeviceToHost);
	cudaMemcpy(&fsquared, d_f_array, sizeof(double), cudaMemcpyDeviceToHost);

	cudaFree(d_f_array);
	cudaFree(d_f_squared_array);

	printf("f = %lf\n", f);
	printf("f_squared = %lf\n", fsquared);

	printf("GPU\n");
	double integral_plus = 2 * integral(ZERO, 0.5, 1);
	double integral_minus = 2 * integral(ZERO, 0.5, -1);
	printf("Integrais: \nSoma: %lf\nSubracao: %lf\n", integral_plus, integral_minus);
	// printMatrix(output, MATRIX_WIDTH, MATRIX_WIDTH);

}