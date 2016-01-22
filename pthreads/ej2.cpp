#include <cstdio>
#include <vector>
#include <cstdlib>
#include <pthread.h>
#define LOCAL_TOSSES 100000
int thread_count;
double linear_pi(int);
int precision; 
int part;
int number_in_circle;
pthread_mutex_t mutex_p;
float result;
void* calculate_pi(void*);

int main(int argc, char *argv[])
{
	thread_count = strtol(argv[1], NULL, 10);
	std::vector<pthread_t> thread_handles(thread_count);
	pthread_mutex_init(&mutex_p, NULL);

	part = precision / thread_count;
	number_in_circle = 0;

	
	for (long thread = 0; thread < thread_count; ++thread)
	{
		pthread_create(&thread_handles[thread], NULL, calculate_pi, (void*)thread);
	}

	for (long thread = 0; thread < thread_count; ++thread)
	{
		pthread_join(thread_handles[thread], NULL);
	}

	// total *= 4;
	printf("result: %d\n", number_in_circle);
	result = (float)number_in_circle/thread_count/LOCAL_TOSSES*4;

	printf("result: %f\n", result);
	pthread_mutex_destroy(&mutex_p);

	return 0;
}

void* calculate_pi(void*){

	int local_tosses = LOCAL_TOSSES;
	int local_n_in_circle = 0;
	for (int toss = 0; toss < local_tosses; ++toss)
	{
		float x = (rand()%200 - 100)/100.;
		float y = (rand()%200 - 100)/100.;
		float distance_squared = x*x + y*y;
		if (distance_squared <= 1) local_n_in_circle++;
	}
	pthread_mutex_lock(&mutex_p);
	number_in_circle += local_n_in_circle;
	pthread_mutex_unlock(&mutex_p);
}


