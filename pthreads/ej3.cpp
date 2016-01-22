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

void* trap(void*){

	
	double h, x, my_result;
	double local_a, local_b;

	int local_n;


	h = (b-a)/n;
	local_n = n/thread_count;
	local_a = a + my_rank*local_n*h;
	local_b = local_a + local_n*h;

	my_result = (f(local_a) + f(local_b))/2.0;
	for(int i = 1; i <= local_n-1; ++i){
		x = local_a + i*h;
		my_result += f(x);
	}

	my_result = my_result*h;

	*global_result_p += my_result;


}


