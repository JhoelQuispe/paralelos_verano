// Radium

#include <cstdio>
#include <vector>
#include <cstdlib>
#include <pthread.h>
#define NUM_DATA 64

int thread_count;
int part;
pthread_mutex_t mutex_p;
float result;
void* distribute_bins(void*);

float data[NUM_DATA];
int total_bin_counts[5] = {0};

int main(int argc, char *argv[])
{
	thread_count = strtol(argv[1], NULL, 10);
	std::vector<pthread_t> thread_handles(thread_count);
	pthread_mutex_init(&mutex_p, NULL);

	for (int i = 0; i < NUM_DATA; ++i)
	{
		data[i] = rand()%500/100.0;
	}

	
	for (long thread = 0; thread < thread_count; ++thread)
	{
		pthread_create(&thread_handles[thread], NULL, distribute_bins, (void*)thread);
	}

	for (long thread = 0; thread < thread_count; ++thread)
	{
		pthread_join(thread_handles[thread], NULL);
	}

	for (int i = 0; i < 5; ++i)
	{
		printf("%d\t\n", total_bin_counts[i]);
	}

	pthread_mutex_destroy(&mutex_p);

	return 0;
}

void* distribute_bins(void* thread){

	long th_id = (long) thread;
	int part = NUM_DATA/thread_count;
	int begin = part*th_id;
	int end = part*(th_id+1);

	for (int i = begin; i < end; ++i)
	{
	
		pthread_mutex_lock(&mutex_p);
		total_bin_counts[(int)data[i]] += 1;
		pthread_mutex_unlock(&mutex_p);
		
	}
}


