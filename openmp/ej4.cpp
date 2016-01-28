#include <omp.h>
#include <cstdio>

#define VARIABLES 3

int main(int argc, char const *argv[])
{

	int thread_num = 4;
	
	int row, col;
	int n = VARIABLES;
	double x[VARIABLES];
	int A[VARIABLES][VARIABLES] = {{2,-3,0},{0,1,1},{0,0,-5}};
	int b[VARIABLES] = {3,1,0};


	for (row = n-1; row >= 0; row--) {
		x[row] = b[row];
		#pragma omp parallel for num_threads(thread_num)
		for (col = row+1; col < n; col++) {
			x[row] -= A[row][col]*x[col];
		}
		x[row] /= A[row][row];
	}

///////////////////////

	// for (int row = 0; row < n; ++row)
	// {
	// 	x[row] = b[row];
	// }

	// for (int col = n-1; col >= 0; --col)
	// {
	// 	x[col] /= A[col][col];
	// 	#pragma omp parallel for num_threads(thread_num)	
	// 	for (row = 0; row < col; row++)
	// 		x[row] -= A[row][col]*x[col];
	// }

	for (int i = 0; i < VARIABLES; ++i) {
		printf("%f ", x[i]);
	}
	printf("\n");

	return 0;
}

// a ) Si se puede paralelizar, x[col] comienza a partir de row+1
// 	la actualizacion de x[row] no afecta a x[col] no hay 
// 	carried loop dependence.

// b ) No es posible, la ultima operacion para calcular x[i] es
// 	x[col] /= A[col][col], cuando se realiza esa operacion
// 	x[col] ya se le debe haber restado el valor de las otras
// 	variables "-= A[row][col]*x[col]" Si se realiza primero
// 	la division el resultado es erroneo. Operaciones no 
// 	commutativas. 	

// c ) Si es posible, x[col] no depende de la actualizacion de
// 	x[row]. El orden en que se realicen las operaciones no
// 	es relevante. Aplican a espacios distintos.

