#include <omp.h>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <ctime>
#include <chrono>


#define VEC_SIZE 131072

int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

class Timer
{
public:
    Timer() : beg_(clock_::now()) {}
    void reset() { beg_ = clock_::now(); }
    double elapsed() const { 
        return std::chrono::duration_cast<second_>
            (clock_::now() - beg_).count(); }

private:
    typedef std::chrono::high_resolution_clock clock_;
    typedef std::chrono::duration<double, std::ratio<1> > second_;
    std::chrono::time_point<clock_> beg_;
};

/////////////////////////////////////

void init_vec_random(int vec[]){
	for (int i = 0; i < VEC_SIZE; ++i)
	{
		vec[i] = rand()%10000000;
	}
}

void print_vec(int vec[]){
	for (int i = 0; i < VEC_SIZE; ++i)
	{
		printf("%d ", vec[i]);
	}
	printf("\n");
}

void Count_sort(int vec[]){
	int i, j, count;
	int temp[VEC_SIZE];

	for (i = 0; i < VEC_SIZE; ++i)
	{
		count = 0;
		for (j = 0; j < VEC_SIZE; ++j)
		{
			if(vec[j] < vec[i]) count++;
			else if (vec[j] == vec[i] && j < i)
				count++;
		}
		temp[count] = vec[i];
	}

	memcpy(vec, temp, VEC_SIZE*sizeof(int));
}

int main(int argc, char const *argv[])
{
	int thread_count = strtol(argv[1], NULL, 10);

	int vec[VEC_SIZE];
	init_vec_random(vec);
	// print_vec(vec);

	// a)  private(i, j, count) shared(vec, temp)
	
	Timer tmr;
	
	// int i, j, count;
	// int temp[VEC_SIZE];

	// #pragma omp parallel for num_threads(thread_count) default(none) \
	// private(i, j, count) shared(vec, temp)
	// for (int i = 0; i < VEC_SIZE; ++i)
	// {
	// 	count = 0;
	// 	for (int j = 0; j < VEC_SIZE; ++j)
	// 	{
	// 		if(vec[j] < vec[i]) count++;
	// 		else if (vec[j] == vec[i] && j < i)
	// 			count++;
	// 	}
	// 	temp[count] = vec[i];
	// }
	// memcpy(vec, temp, VEC_SIZE*sizeof(int));
	// #pragma omp parallel for num_threads(thread_count)
	// for (int i = 0; i < VEC_SIZE; ++i)
	// {
	// 	vec[i] = temp[i];
	// }

	qsort(vec, VEC_SIZE, sizeof(int), cmpfunc);


	double elapsed_secs = tmr.elapsed(); 

    printf("%f\n", elapsed_secs);


	
	// b) No hay loop-carried dependence. Los elementos que se
	//		asignan a temp[] no dependen de otra iteracion.

	// c) memcpy se llama despues de terminar de ordenar, si se
	//		llama en cada iteracion solo se perdera tiempo
	//    




	// print_vec(vec);
	return 0;
}

//////
/*			
			 32768		65536		131072	

4threads	2.844423	11.807003	47.243020	
secuenc		5.644590	22.718944	89.345295
qsort		0.004478	0.009217	0.019869

*/