#include "helperFunctions.h"
#include "reduction.h"
#include "ioFunctions.h"

void reduceSequential(int *matrixList, int matrixAmount)
{
	int output[MATRIX_WIDTH][MATRIX_WIDTH];
	int totalAmount = nextPowerOfTwo(matrixAmount);

	while (totalAmount > 1)
	{
		for (int l = 0; l < totalAmount; l++)
		{
			for (int i = 0; i < MATRIX_SIZE; i++)
			{
				matrixList[MATRIX_SIZE * l + i] = min(matrixList[MATRIX_SIZE * l + i], matrixList[MATRIX_SIZE * ((totalAmount / 2) + l) + i]);
			}
		}
		totalAmount /= 2;
	}

	printMatrix(matrixList, MATRIX_WIDTH, MATRIX_WIDTH);
}

int main(int argc, char *argv[])
{

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
		printMatrix(&matrixList[MATRIX_SIZE * l], MATRIX_WIDTH, MATRIX_WIDTH);
		printf("***\n");
	}
	// saveMatrix(matrixList, matrixAmount, "out1");

	// generateRandomInputFile(5);

	// printMatrix(generateRandomMatrix(3, 3),3, 3);

	// reduceSequential(matrixList, matrixAmount);
	reduceOnGPU(matrixList, matrixAmount);

	return 0;
}
