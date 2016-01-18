#include <cstdio>
#include <mpi.h>

#define MESSAGE_SIZE 10
#define BUFFER_SIZE 1

int main(int argc, char *argv[])
{

		
	int rank, size;
	int tag = 666;

	int message[MESSAGE_SIZE];	
	int buff[BUFFER_SIZE];
	int bsize = BUFFER_SIZE;

	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	MPI_Buffer_attach(buff, BUFFER_SIZE);

	if (rank == 0)
	{
		printf("Sending message\n");
		for (int i = 0; i < 100000000; ++i){}
		for (int i = 0; i < MESSAGE_SIZE; ++i)
		{
			message[i] = 4-i;
		}
		MPI_Bsend(&message, MESSAGE_SIZE, MPI_INT, 1, tag, MPI_COMM_WORLD);
		printf("Message sended\n");
	}

	if (rank == 1)
	{
		printf("Reciving message\n");
		for (int i = 0; i < 2000000000; ++i){}
		MPI_Recv(&message, MESSAGE_SIZE, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
		printf("Recived message: \n");
		for (int i = 0; i < MESSAGE_SIZE; ++i)
		{
			printf("%d\t", message[i]);
		}
		printf("\n");

	}

	MPI_Buffer_detach(buff, &bsize);



	MPI_Finalize();

	return 0;

}