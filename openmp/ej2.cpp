#include <omp.h>
#include <cstdio>
#include <cstdlib>

#define LOCAL_TOSSES 100000

int monte_carlo_partial_pi(){
	int number_in_circle = 0;
	for (int toss = 0; toss < LOCAL_TOSSES; ++toss)
	{
		float x = (rand()%200 - 100)/100.;
		float y = (rand()%200 - 100)/100.;
		float distance_squared = x*x + y*y;
		if (distance_squared <= 1)
			number_in_circle++;
	}	
	return number_in_circle;
}

int main(int argc, char *argv[])
{
	int thread_count = strtol(argv[1], NULL, 10);
	int total_in_circle = 0;

	#pragma omp parallel num_threads(thread_count) reduction(+: total_in_circle)
	{
		total_in_circle += monte_carlo_partial_pi();
	}

	printf("result: %d\n", total_in_circle);
	float result = (float)total_in_circle/thread_count/LOCAL_TOSSES*4;
	printf("result: %f\n", result);

	return 0;
}