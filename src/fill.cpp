#include <omp.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

int main(int argc, char * argv[]) {
	int n = atoi(argv[1]);
	int threads = atoi(argv[2]);

	double begin = omp_get_wtime();

	long b[n];
	long sumB = 0;
	int a[n][3];

	b[0] = 0;

	srand(123);
	a[0][0] = a[0][1] = a[0][2] = 0;
	//sequentiell!
	for(int i = 1; i < n; ++i) {
		a[i][0] = rand() % i;
		a[i][1] = (rand() % 19) - 9;
		a[i][2] = (rand() % 3) + 1;
	}

	double start;
	int help;
	#pragma omp parallel for ordered schedule(dynamic) num_threads(threads) reduction(+:sumB) private(help)
	for(int i = 1; i < n; ++i) {
		//TODO only wait for b[a[i][0]] to finish instead of everyone
		#pragma omp ordered
		help = b[a[i][0]];
		start = omp_get_wtime();
		while(omp_get_wtime() - start < a[i][2]) {}
		b[i] = help + a[i][1];
		sumB += b[i];
		#pragma omp ordered
		cout << "b[" << i << "] = " << b[i]<< "\n";
	}
	cout << "sum = " << sumB << endl;

	double end = omp_get_wtime();
	cout << "time: " << end-begin << endl;

	return 0;
}
