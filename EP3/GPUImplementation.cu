// #include <stdlib.h>
extern "C" {
	#include "GPUImplementation.h"
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

__device__ double fun_gpu(double x, int64_t M, int64_t k)
{
	double result = (sin((2 * M + 1) * M_PI * x) * cos(2 * M_PI * k * x)) / sin(M_PI * x);
	return result;
}

__global__ void create_f_array(double* f_array, double* f_squared_array, double* samples, int64_t n, int64_t M, int64_t k){
	int id = blockIdx.x * blockDim.x + threadIdx.x;
	if (id < n){
		double f_xi = fun_gpu(samples[id], M, k);
		f_array[id] = f_xi ;
		f_squared_array[id] = f_xi * f_xi ;
	}
}

__global__ void reductionGPU(double* f_array, double* f_squared_array, int64_t totalAmount){

	int id = blockIdx.x * blockDim.x + threadIdx.x;
	if (id < (totalAmount/2)){
		f_array[id] = f_array[id] + f_array[id + (totalAmount/2)];
		f_squared_array[id] = f_squared_array[id] + f_squared_array[id + (totalAmount/2)];
	}

}


void calculate_f_GPU(){
	int64_t totalAmount = nextPowerOfTwo(N);
	double *d_f_array;
	double *d_f_squared_array;
	double *d_samples;

	struct timespec begin, end;

	dim3 grid, block;
	block.x = 1024;
	grid.x = (totalAmount + block.x - 1) / block.x;

    cudaSetDevice(1);

	cudaMalloc((void**)&d_samples, N*sizeof(double));
	cudaMalloc((void**)&d_f_array, totalAmount*sizeof(double));
	cudaMalloc((void**)&d_f_squared_array, totalAmount*sizeof(double));

	cudaMemset(d_f_array, 0, totalAmount*sizeof(double));
	cudaMemset(d_f_squared_array, 0, totalAmount*sizeof(double));

	printf("Time spent copying data");
	clock_gettime(CLOCK_REALTIME, &begin);
	cudaMemcpy(d_samples, samples, N*sizeof(double), cudaMemcpyHostToDevice);
	clock_gettime(CLOCK_REALTIME, &end);
	printTimeElapsed(begin, end);



	create_f_array<<<grid, block>>>(d_f_array, d_f_squared_array, d_samples, N, M, k);

	while(totalAmount > 1){

		reductionGPU<<<grid, block>>>(d_f_array, d_f_squared_array, totalAmount);
		cudaDeviceSynchronize();

		totalAmount /= 2;
		grid.x = (totalAmount + block.x - 1) / block.x;
	}
	cudaMemcpy(&f, d_f_array, sizeof(double), cudaMemcpyDeviceToHost);
	cudaMemcpy(&fsquared, d_f_squared_array, sizeof(double), cudaMemcpyDeviceToHost);

	cudaFree(d_f_array);
	cudaFree(d_f_squared_array);

	f = f/N;
	fsquared = fsquared/N;

}