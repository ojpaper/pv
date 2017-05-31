#include <omp.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;

int main(int argc, char * argv[]) {
	int n = atoi(argv[1]);
	int threads = atoi(argv[2]);

	clock_t begin = clock();

	long b[n];
	long sumB = 0;
	int a[n][3];

	b[0] = 0;

	srand(123);
	a[0][0] = a[0][1] = a[0][2] = 0;
	for(int i = 1; i < n; ++i) {
		a[i][0] = rand() % i;
		a[i][1] = (rand() % 19) - 9;
		a[i][2] = (rand() % 3) + 1;
	}

	double start;
	for(int i = 1; i < n; ++i) {
		int help = b[a[i][0]];
		start = omp_get_wtime();
		while(omp_get_wtime() - start < a[i][2]/10) {}
		b[i] = help + a[i][1];
		sumB += b[i];
		cout << "b[" << i << "] = " << b[i]<< "\n";
	}
	cout << "sum = " << sumB << endl;

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "time: " << elapsed_secs;

	return 0;
}
