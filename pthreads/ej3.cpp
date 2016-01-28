// Trapezoidal Rule

#include <cstdio>
#include <vector>
#include <pthread.h>
#include <iostream>
#include <cstdlib>

int thread_count;
pthread_mutex_t mutex_p;
double result;
int local_n;
double h, a, b;

void* trapezoidal(void*);
double f(double);

using namespace std;

int main(int argc, char *argv[])
{
	thread_count = strtol(argv[1], NULL, 10);
	std::vector<pthread_t> thread_handles(thread_count);
	pthread_mutex_init(&mutex_p, NULL);

	int n;
	result = 0;

	cin>>a>>b>>n;

	local_n = n/thread_count;
	h = (b-a)/n;
	
	for (long thread = 0; thread < thread_count; ++thread)
	{
		pthread_create(&thread_handles[thread], NULL, trapezoidal, (void*)thread);
	}

	for (long thread = 0; thread < thread_count; ++thread)
	{
		pthread_join(thread_handles[thread], NULL);
	}

	printf("result: %f\n", result);
	pthread_mutex_destroy(&mutex_p);

	return 0;
}

void* trapezoidal(void* thread){
	
	int th_id = (long) thread;
	double local_a = a + local_n*th_id*h;
	double local_b = local_a + local_n*h;
	double my_result =  (f(local_a) + f(local_b)) / 2.;

	for (int i = 1; i < local_n; ++i) 
	{
		my_result += f(local_a + i*h);
	}
	my_result *= h;

	pthread_mutex_lock(&mutex_p);
	result += my_result;
	pthread_mutex_unlock(&mutex_p);
}

double f(double v){
	return v*v;
}
