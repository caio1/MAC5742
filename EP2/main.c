#include "helperFunctions.h"
#include "reduction.h"
#include "ioFunctions.h"

int *reduceSequential(int *matrixList, int matrixAmount)
{
	printf("matrixAmount = %d\n", matrixAmount);
	int *output = malloc(MATRIX_SIZE * sizeof(int));
	int totalAmount = nextPowerOfTwo(matrixAmount);

	printf("totalAmount = %d\n", totalAmount);

	while (totalAmount > 1)
	{
		for (int l = 0; l < totalAmount / 2; l++)
		{
			for (int i = 0; i < MATRIX_SIZE; i++)
			{
				matrixList[MATRIX_SIZE * l + i] = min(matrixList[MATRIX_SIZE * l + i], matrixList[MATRIX_SIZE * ((totalAmount / 2) + l) + i]);
			}
		}
		totalAmount /= 2;
	}

	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		output[i] = matrixList[i];
	}

	printMatrix(output, MATRIX_WIDTH, MATRIX_WIDTH);

	return output;
}

int *reduceSequential2(int *matrixList, int matrixAmount)
{
	int totalAmount = nextPowerOfTwo(matrixAmount);

	int *output = malloc(MATRIX_SIZE * sizeof(int));
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		output[i] = INT_MAX;
	}

	for (int l = 0; l < totalAmount * MATRIX_SIZE; l += MATRIX_SIZE)
	{
		for (int i = 0; i < MATRIX_SIZE; i++)
		{
			output[i] = min(output[i], matrixList[l + i]);
		}
	}

	printMatrix(output, MATRIX_WIDTH, MATRIX_WIDTH);

	return output;
}

int main(int argc, char *argv[])
{

	if (argc != 2)
	{
#ifdef DEBUG
		if (argc = 4)
		{
			generateRandomInputFile(atoi(argv[2]), argv[3]);
			return 0;
		}
#endif
		printf("Usage: %s <caminho_lista_matrizes>\n", argv[0]);
		return 3;
	}

	int *matrixList;
	int matrixAmount;

	matrixList = readMatrices(&matrixAmount, argv[1]);

	struct timeval begin, end;

	gettimeofday(&begin, NULL);
	int *gpu_output = reduceOnGPU(matrixList, matrixAmount);
	gettimeofday(&end, NULL);

#ifdef DEBUG
	int *sequential_output = reduceSequential(matrixList, matrixAmount);

	if (compareResults(sequential_output, gpu_output))
	{
		printf("Test passed: The sequential implementation outputs the same result");
	}
	else
	{
		printf("Test failed");
	}

	float gpuTime = 1000000 * (float)(end.tv_sec - begin.tv_sec);
	gpuTime += (float)(end.tv_usec - begin.tv_usec);
	printf("\nExecution Time (microseconds): %9.2f\n\n", gpuTime);
#endif

	free(matrixList);

	return 0;
}
