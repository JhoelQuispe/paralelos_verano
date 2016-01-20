#include <iostream>
#include <cstdio>
#include <mpi.h>
#include <cstdlib>
#include <ctime>
#define NUM_TOSSES 10000000

using namespace std;



int main(int argc, char *argv[])
{
	srand(time(0));
	int my_rank, my_size;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &my_size);

	int global_number_in_circle;
	long long int number_of_tosses = NUM_TOSSES;
	int number_in_circle = 0;

	float total_tosses = float(NUM_TOSSES)*my_size;

	for (int toss = 0; toss < number_of_tosses; ++toss){
		float x = (rand()%200-100)/100.0;
		float y = (rand()%200-100)/100.0;
		float distance_squared = x*x + y*y;
		if (distance_squared <= 1) number_in_circle++; 
	}

	MPI_Reduce(&number_in_circle, &global_number_in_circle, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if(my_rank == 0) printf("total: %f\n", global_number_in_circle/total_tosses*4);

	MPI_Finalize();

	return 0;
}