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

	int limit = 11 ;
	int part = NUM_DATA/(my_size-1);
	int value = 0;
	int value_t = 0;

	while(value < limit){
		if (my_rank == 0)
		{
			value_t = value + 1 ;
			MPI_Send(&value_t, 1, MPI_INT, 1, 100, MPI_COMM_WORLD);
			MPI_Recv(&value, 1, MPI_INT, 1, 90, MPI_COMM_WORLD, &status);
		}

		else
		{
			MPI_Recv(&value, 1, MPI_INT, 0, 100, MPI_COMM_WORLD, &status);
			value_t = value + 1 ;
			MPI_Send(&value_t, 1, MPI_INT, 0, 90, MPI_COMM_WORLD);
		}
	}

	printf("process %d got %d\n", my_rank, value);

	MPI_Finalize();

	return 0;
}
