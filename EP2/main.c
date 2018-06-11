#include "helperFunctions.h"
#include "ioFunctions.h"

void reduceSequential(int **matrixList, int matrixAmount){
	int output[3][3] = {
		{INT32_MAX, INT32_MAX, INT32_MAX},
		{INT32_MAX, INT32_MAX, INT32_MAX},
		{INT32_MAX, INT32_MAX, INT32_MAX}
	};

	for (int i = 0; i < 3; i++)
	{
		printf("[");
		for (int j = 0; j < 3; j++)
		{
			for (int l = 0; l < matrixAmount; l++)
			{
				output[i][j] = min(output[i][j], matrixList[l][3 * i + j]);
					// printf("%02d, ", matrixList[l][3 * i + j]);
			}
			printf("%02d ,", output[i][j]);
		}
		printf("]\n");
	}
}

int main(int argc, char* argv[]) {

	struct timeval start, stop;
	
	if (argc != 2)
	{
		printf("Usage: %s <caminho_lista_matrizes>\n", argv[0]);
		return 3;
	}

	int **matrixList;
	int matrixAmount;

	matrixList = readMatrices(&matrixAmount, "in1");

	for (int l = 0; l < matrixAmount; l++)
	{
		for (int i = 0; i < 3; i++)
		{
			printf("[");
			for (int j = 0; j < 3; j++)
			{
				printf("%02d, ", matrixList[l][3*i + j]);
			}
			printf("]\n");
		}
		printf("***\n");
	}
	// saveMatrix(matrixList, matrixAmount, "out1");

	generateRandomInputFile(5);
	

	// printMatrix(generateRandomMatrix(3, 3),3, 3);

	// reduceSequential(matrixList, matrixAmount);

	return 0;
}
