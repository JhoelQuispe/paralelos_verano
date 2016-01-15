#include <iostream>
#include <ctime>
#include <cstdlib>
#define MAX 33000

using namespace std;

int main(){

	cout <<"It needs ~2GB RAM" << endl;

    short **A = new short*[MAX];
    short x[MAX] = {1};
    short y[MAX] = {1};
    
    for (int i = 0; i < MAX; ++i)
    {
        A[i] = new short[MAX];
        for(int j = 0; j < MAX; j++)
        {
            A[i][j] = rand()%20;
        }
    }

    clock_t begin = clock();

    // for (int i = 0; i < MAX; ++i)
    // {
    //     for (int j = 0; j < MAX; ++j)
    //     {
    //         y[i] += A[i][j]*x[j];
    //     }
    // }


    for (int j = 0; j < MAX; ++j)
    {
        for (int i = 0; i < MAX; ++i)
        {
            y[i] += A[i][j]*x[j];
        }
    }

    clock_t end = clock();

    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    cout << elapsed_secs << endl;

    return 0;
}
