// Radium

#include <cstdio>
#include <vector>
#include <cstdlib>
#include <pthread.h>
#include <iostream>

#define NUM_DATA 64

int thread_count;
int precision; 
int part;
int number_in_circle;
pthread_mutex_t mutex_p;
float result;
void* distribute_bins(void*);

float data[NUM_DATA];
int total_bin_counts[5] = {0};

using namespace std;

int main(int argc, char *argv[])
{
	thread_count = strtol(argv[1], NULL, 10);
	std::vector<pthread_t> thread_handles(thread_count);

	for (int i = 0; i < NUM_DATA; ++i)
	{
		data[i] = rand()%500/100.0;
	}
	
	clock_t begin = clock();
	
	for (long thread = 0; thread < thread_count; ++thread)
	{
		pthread_create(&thread_handles[thread], NULL, distribute_bins, (void*)thread);
	}

	for (long thread = 0; thread < thread_count; ++thread)
	{
		pthread_join(thread_handles[thread], NULL);
	}

	clock_t end = clock();

	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC / thread_count;

	 cout << elapsed_secs << endl;

	return 0;
}

void* distribute_bins(void* thread){
	
}

/*

1 6e-05

ucsp@ucsp-ThinkCentre-M73z:~/paralelos_verano/pthreads$ ./a.out 2
5.25e-05
ucsp@ucsp-ThinkCentre-M73z:~/paralelos_verano/pthreads$ ./a.out 3
0.000133667
ucsp@ucsp-ThinkCentre-M73z:~/paralelos_verano/pthreads$ ./a.out 4
7.025e-05
ucsp@ucsp-ThinkCentre-M73z:~/paralelos_verano/pthreads$ ./a.out 5
0.0001732
ucsp@ucsp-ThinkCentre-M73z:~/paralelos_verano/pthreads$ ./a.out 6
6.15e-05
ucsp@ucsp-ThinkCentre-M73z:~/paralelos_verano/pthreads$ ./a.out 7
0.000159857
ucsp@ucsp-ThinkCentre-M73z:~/paralelos_verano/pthreads$ ./a.out 8
0.00014775
ucsp@ucsp-ThinkCentre-M73z:~/paralelos_verano/pthreads$ ./a.out 9
0.000157556
ucsp@ucsp-ThinkCentre-M73z:~/paralelos_verano/pthreads$ ./a.out 10
0.0001658
ucsp@ucsp-ThinkCentre-M73z:~/paralelos_verano/pthreads$ ./a.out 16
0.00010975
ucsp@ucsp-ThinkCentre-M73z:~/paralelos_verano/pthreads$ ./a.out 32
0.000119531
ucsp@ucsp-ThinkCentre-M73z:~/paralelos_verano/pthreads$ ./a.out 54
2.83148e-05
ucsp@ucsp-ThinkCentre-M73z:~/paralelos_verano/pthreads$ ./a.out 64
0.000108797
ucsp@ucsp-ThinkCentre-M73z:~/paralelos_verano/pthreads$ ./a.out 128
0.00011168
ucsp@ucsp-ThinkCentre-M73z:~/paralelos_verano/pthreads$ ./a.out 256
9.94961e-05
ucsp@ucsp-ThinkCentre-M73z:~/paralelos_verano/pthreads$ ./a.out 512
6.20684e-05
ucsp@ucsp-ThinkCentre-M73z:~/paralelos_verano/pthreads$ ./a.out 1024
7.19072e-05



*/

