#include <omp.h>
#include <cstdio>
#include <cstdlib>

using namespace std;

int thread_count;
int data_count = 50000;
float min_meas;
float max_meas;

void init_random(float* data, int data_count){
	for (int i = 0; i < data_count; ++i)
	{
		data[i] = rand()%1000/1000.*10;
	}
}

void print_data(float* data, int data_count){
	for (int i = 0; i < data_count; ++i)
	{
		printf("%.2f ", data[i]);
	}
	printf("\n");
}

int Find_bin(float data_i, float* bin_maxes, int bin_count, float min_meas){
	if(bin_maxes[bin_count-1] <= data_i)
		return bin_count;
	for (int i = bin_count-1; i > 0; --i)
	{
		if(bin_maxes[i-1] <= data_i){
			return i;
		}
	}
	if (min_meas <= data_i)
		return 0;
	else
		return bin_count;
}

int main(int argc, char* argv[]){

	thread_count = strtol(argv[1], NULL, 10);
	
	float data[data_count];
	int bin_count;

	init_random(data, data_count);
	// print_data(data, data_count);

	printf("type min_meas and max_meas and bin_count\n");
	scanf("%f%f%d", &min_meas, &max_meas, &bin_count);

	int bins[bin_count+1] = {0};

	int bin = 0;

	float bin_width = (max_meas - min_meas) / bin_count;
	float bin_maxes[bin_count];

	for (int b = 0; b < bin_count; ++b)
	{
		bin_maxes[b] = min_meas + bin_width*(b+1);
	}

	# pragma omp parallel for num_threads(thread_count)
	for(int i = 0; i < data_count; ++i)
	{
		bin = Find_bin(data[i], bin_maxes, bin_count, min_meas);
		#pragma omp critical
		bins[bin]++; 
	}

	for (int i = 0; i < bin_count; ++i)
	{
		printf("bin %d: bin_max: %f, elements: %d\n", i, bin_maxes[i], bins[i]);
	}





	return 0;
}