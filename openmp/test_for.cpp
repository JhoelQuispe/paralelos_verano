#include <cstdio>
#include <omp.h>
#include <cstdlib>

int main(int argc, char const *argv[])
{
	int count = 10;
	int i = 0;
	#pragma omp parallel num_threads(4) shared(count) private(i)
	for (i = 0; i < count; ++i)
	{
		printf("%d", i);
		#pragma omp for
		for (int k = 0; k < 2; ++k)
		{
			printf("-\n");
		}
		printf("\n");
		int j = i;
		// int rr = random()%10;
		int th_id = omp_get_thread_num();
		// // i += 1;
		// if (i == 3) {
		// 	printf("okk!!\n");
		// 	exit;
		// }



		// printf("%d, %d in %d\n", i, j, th_id);
	}
	return 0;
}