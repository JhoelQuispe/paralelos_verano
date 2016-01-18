#include <cstdio>
#include <mpi.h>


int main(int argc, char *argv[])
{

		
	int rank, size;
	int message = 0;	
	int tag = 666;

	MPI_Status status;

	MPI_Request reqs[4];


	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);


	if (rank == 0)
	{
		printf("Sending message\n");
		for (int i = 0; i < 100000000; ++i){}
		for (int i = 0; i < 2000000000; ++i){}
		message = 5;
		MPI_Isend(&message, 1, MPI_INT, 1, tag, MPI_COMM_WORLD, &reqs[0]);
		printf("Message sended\n");
	}

	if (rank == 1)
	{
		printf("Reciving message\n");
		MPI_Irecv(&message, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &reqs[1]);
		printf("Recived message: %d\n", message);
		for (int i = 0; i < 2000000000; ++i){}
		printf("Recived message final: %d\n", message);


	}



	MPI_Finalize();

	return 0;

}