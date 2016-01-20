#include <iostream>
#include <cstdio>
#include <mpi.h>
#include <cstdlib>
#define NUM_DATA 64

using namespace std;



int main(int argc, char *argv[])
{
	int my_rank, my_size;
	int bins = 5;
	int bin_counts[5] = {0};
	int total_bin_counts[5] = {0};

	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &my_size);

	int part = NUM_DATA/(my_size-1);

	if (my_rank == 0)
	{
		float data [NUM_DATA];
		for (int i = 0; i < NUM_DATA; ++i)
		{
			data[i] = rand()%500/100.0;
		}

		// for (int i = 0; i < NUM_DATA; ++i)
		// {
		// 	printf("%f\n", data[i]);
		// }


		for (int i = 1; i < my_size; ++i)
		{
			MPI_Send(&data[0], part, MPI_FLOAT, i, 100, MPI_COMM_WORLD);
		}

		for (int i = 1; i < my_size; ++i)
		{
			MPI_Recv(&bin_counts, bins, MPI_INT, i, 90, MPI_COMM_WORLD, &status);
			for (int j = 0; j < bins; ++j)
			{
				total_bin_counts[j] += bin_counts[j];
			}
		}

		for (int i = 0; i < bins; ++i)
		{
			printf("%d ", total_bin_counts[i]);
		}
		printf("\n");

	}

	else
	{
		float recv[part];
		MPI_Recv(&recv, part, MPI_FLOAT, 0, 100, MPI_COMM_WORLD, &status);


		for (int i = 0; i < part; ++i)
		{
			// cout << "rank " << my_rank <<", d " << recv[i] << endl;
			bin_counts[(int)recv[i]] += 1;
		}

		MPI_Send(&bin_counts, bins, MPI_INT, 0, 90, MPI_COMM_WORLD);

	}

	MPI_Finalize();

	return 0;
}