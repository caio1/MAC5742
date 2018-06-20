#include "helperFunctions.h"
#include "ioFunctions.h"

void reduceSequential(int *matrixList, int matrixAmount){
	int output[3][3] = {
		{INT_MAX, INT_MAX, INT_MAX},
		{INT_MAX, INT_MAX, INT_MAX},
		{INT_MAX, INT_MAX, INT_MAX}
	};

	for (int i = 0; i < 3; i++)
	{
		printf("[");
		for (int j = 0; j < 3; j++)
		{
			for (int l = 0; l < matrixAmount; l++)
			{
				output[i][j] = min(output[i][j], matrixList[l*9 + 3*i + j]);
			}
			printf("%02d ,", output[i][j]);
		}
		printf("]\n");
	}
}

int main(int argc, char* argv[]) {

	// struct timeval start, stop;
	
	if (argc != 2)
	{
		printf("Usage: %s <caminho_lista_matrizes>\n", argv[0]);
		return 3;
	}

	int *matrixList;
	int matrixAmount;

	matrixList = readMatrices(&matrixAmount, "in1");

	for (int l = 0; l < nextPowerOfTwo(matrixAmount); l++)
	{
		printMatrix(&matrixList[9*l], 3, 3);
		printf("***\n");
	}
	// saveMatrix(matrixList, matrixAmount, "out1");

	// generateRandomInputFile(5);
	

	// printMatrix(generateRandomMatrix(3, 3),3, 3);

	// reduceSequential(matrixList, matrixAmount);

	return 0;
}
