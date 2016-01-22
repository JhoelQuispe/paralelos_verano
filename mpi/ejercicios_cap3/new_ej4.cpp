#include <iostream>
#include <cstdio>
#include <mpi.h>
#include <cstdlib>
#include <math.h>
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
	int value = my_rank;
	int other_value;

	int iterations = log2(my_size);

	for(int iteration = 1; iteration <= iterations; ++iteration) {
		//cout <<" iteration " << my_rank << endl;
		int difference = pow(2, iteration-1);
		if((my_rank/difference) % 2 == 0){
			MPI_Send(&value, 1, MPI_INT, my_rank + difference, 100, MPI_COMM_WORLD);
			MPI_Recv(&other_value, 1, MPI_INT, my_rank + difference, 90, MPI_COMM_WORLD, &status);
					
		}
		else {
			MPI_Recv(&other_value, 1, MPI_INT, my_rank - difference, 100, MPI_COMM_WORLD, &status);			
			MPI_Send(&value, 1, MPI_INT, my_rank - difference, 90, MPI_COMM_WORLD);			
		}
		value += other_value;	
		MPI_Barrier(MPI_COMM_WORLD);

	}

	
	

	printf("process %d -> %d\n", my_rank, value);	
	
	

	return 0;
}
