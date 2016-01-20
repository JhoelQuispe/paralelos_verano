#include <iostream>
#include <cstdio>
#include <mpi.h>
#include <cstdlib>
#include <ctime>

using namespace std;



int main(int argc, char *argv[])
{
	int my_rank, my_size;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &my_size);

	int global_sum;
	int x = my_rank;

	MPI_Reduce(&x, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if(my_rank == 0) printf("total: %d\n", global_sum);

	MPI_Finalize();

	return 0;
}