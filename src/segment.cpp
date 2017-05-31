#include <omp.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char * argv[]) {
	int n = atoi(argv[1]);
	int threads = atoi(argv[2]);

	n = 10;

	//aufeinanderfolgende zahlen: 94, 14, ...
	int a[n] = {
			94,
			14,
			74,
			31,
			80,
			32,
			96,
			23,
			27,
			2
	}; //n = 10, seed = 123

	double begin = omp_get_wtime();

	srand(123);
	for(int i = 0; i < n; ++i) {
//		a[i] = rand() % 100 + 1;
		cout << a[i] << endl;
	}


	double end = omp_get_wtime();
	cout << "time: " << end-begin << endl;
}
