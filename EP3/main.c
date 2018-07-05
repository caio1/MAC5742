#include "helperFunctions.h"
#include "CPUImplementations.h"
#include "GPUImplementation.h"

void drawSamples()
{
	int64_t i;
	for (i = 0; i < N; i++)
	{
		samples[i] = randomSample(ZERO, 1);
	}
}

double calculateIntegral(double a, double b, double sig)
{
	return (b - a) * (f + sig * sqrt((fsquared - pow(f, 2)) / N));
}

void calculate_integral_sequential()
{
	struct timespec begin, end;

	clock_gettime(CLOCK_REALTIME, &begin);
	printf("\nExecutando sequencialmente\n");
	calculate_f_sequential();
	double integral_plus = 2 * calculateIntegral(ZERO, 0.5, 1);
	double integral_minus = 2 * calculateIntegral(ZERO, 0.5, -1);
	printf("Soma: %lf\nSubracao: %lf\n", integral_plus, integral_minus);
	clock_gettime(CLOCK_REALTIME, &end);
	printTimeElapsed(begin, end);
}

void calculate_integral_pthreads()
{
	struct timespec begin, end;

	clock_gettime(CLOCK_REALTIME, &begin);
	printf("\nExecutando com pthreads\n");
	calculate_f_CPU();
	double integral_plus = 2 * calculateIntegral(ZERO, 0.5, 1);
	double integral_minus = 2 * calculateIntegral(ZERO, 0.5, -1);
	printf("Soma: %lf\nSubracao: %lf\n", integral_plus, integral_minus);
	clock_gettime(CLOCK_REALTIME, &end);

	printTimeElapsed(begin, end);
}

void calculate_integral_gpu()
{
	struct timespec begin, end;

	clock_gettime(CLOCK_REALTIME, &begin);
	printf("\nGPU\n");
	calculate_f_GPU();
	double integral_plus = 2 * calculateIntegral(ZERO, 0.5, 1);
	double integral_minus = 2 * calculateIntegral(ZERO, 0.5, -1);
	printf("Soma: %lf\nSubracao: %lf\n", integral_plus, integral_minus);
	clock_gettime(CLOCK_REALTIME, &end);
	printTimeElapsed(begin, end);
}

void process_zero()
{
	if (N < 100)
	{
		calculate_integral_sequential();
	}
	else if (N < 100000)
	{
		calculate_integral_pthreads();
	}
	else
	{
		calculate_integral_gpu();
	}
}

void process_one()
{
}

int main(int argc, char *argv[])
{
	// struct timespec begin, end;
	if (argc < 4)
	{
		printf("Usage: %s <numero_de_amostras> <parametro_k> <parametro_M>\n", argv[0]);
		return 3;
	}
	srand(time(NULL));

	// printf("This system has %d processors configured and "
	// 	   "%d processors available.\n",
	// 	   get_nprocs_conf(), get_nprocs());

	MPI_Init(NULL, NULL);

	int rank, size;

	// Get MPI rank and size
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	printf("HELLO! I'M PROCESS NUMBER %d!!\n", rank);

	N = strtoll(argv[1], NULL, 10);
	k = strtoll(argv[2], NULL, 10);
	M = strtoll(argv[3], NULL, 10);
	samples = malloc(N * sizeof(double));

	drawSamples();

	if (rank == 0)
	{
		process_zero()
	}
	else if (rank == 1)
	{
		process_one()
	}

	calculate_integral_sequential();
	calculate_integral_pthreads();
	calculate_integral_gpu();

	free(samples); //haha

	MPI_Finalize();

	return 0;
}
