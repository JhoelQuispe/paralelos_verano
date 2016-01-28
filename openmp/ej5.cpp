#include <iostream>
#include <cmath>
#include <vector>
#include <omp.h>

using namespace std;

int thread_num;

void print(vector< vector<double> > A) {
    int n = A.size();
    for (int i=0; i<n; i++) {
        for (int j=0; j<n+1; j++) {
            cout << A[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void Gauss(vector< vector<double> > &A) {
    int n = A.size();

    for (int i=0; i<n; i++) {
    	#pragma omp parallel for num_threads(thread_num)
        for (int k=i+1; k<n; k++) {
            double c = -A[k][i]/A[i][i];
            for (int j=i; j<n+1; j++) {
                A[k][j] += c * A[i][j];
            }

          	print(A);
        }

    }

}

int main() {
    int n;

    cin >> thread_num;

    cin >> n;

    vector<double> line(n+1,0);
    vector< vector<double> > A(n,line);

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            cin >> A[i][j];
        }
    }

    for (int i=0; i<n; i++) {
        cin >> A[i][n];
    }

    print(A);
    Gauss(A);
    print(A);

    cout << endl;
}




// row : 2
// 	x[2] = 0;
// 	x[2] /= A[2][2] = 0;
// row : 1
// 	x[1] = 1;
// 		col: 2
// 			x[1] -= A[1][2]*x[2]
// 			x[1] -= 1*0;
// 			x[1] = 1;
// 	x[1] /= A[1][1] = 1;

// row: 0
// 	x[0] = 3;
// 		col: 1
// 			x[0] -= A[0][1]*x[1]
// 			x[0] -= -3 = 6
// 		col: 2  
// 			x[0] -= A[0][2]*x[2] = 6
// 	x[0] /= A[0][0] = 3

// //

// row: 0
// 	x[0] = 3

// row: 1
// 	x[1] = 1

// row: 2
// 	x[2] = 0

// col: 2
// 	x[2] /= A[2][2]
// 	x[2] /= -5 = 0
// 	row: 0
// 		x[0] -= A[0][2] = 3
// 	row: 1
// 		x[1] -= A[1][2]*x[2] = 1

// col: 1
// 	x[1] = 1
// 	row: 0
// 		x[0] -= A[0][1]*1 = 6

// col: 0
// 	x[0] = 2
