#include <omp.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

int main(int argc, char * argv[]) {
	int n = atoi(argv[1]);
	int threads = atoi(argv[2]) + 1;
	omp_set_num_threads(threads);

	long b[n];
	bool counter[n];
	long sumB;
	int order[n][n];
	int orderCount[n];
	int done;
	int ordered[n];

	#pragma omp parallel sections
	{
		#pragma omp section
		{
			counter[0] = 1;
			for(int i = 1; i < n; ++i) {
				counter[i] = 0;
			}
		}
		#pragma omp section
		{
			for(int i = 0; i < n; ++i) {
				orderCount[i] = 0;
			}
		}
	}

	//sequentiell
	int a[n][3];
	srand(123);
	a[0][0] = a[0][1] = a[0][2] = 0;
	for(int i = 1; i < n; ++i) {
		a[i][0] = rand() % i;
		a[i][1] = (rand() % 19) - 9;
		a[i][2] = (rand() % 3) + 1;
		order[a[i][0]][orderCount[a[i][0]]] = i;
		orderCount[a[i][0]]++;
	}

	sumB = 0;
	done = 0;
	for(int i = 1; i < n;) {
		//baumartige Erstellung einer Abarbeitungsliste
		for(int j = 0; j < orderCount[done]; j++) {
			ordered[i] = order[done][j];
			i++;
		}
		done++;
	}

	#pragma omp parallel sections
	{
		#pragma omp section
		{
			//Berechnung
			#pragma omp parallel for schedule(dynamic) num_threads(threads-1)
			for	(int i = 1; i < n; ++i) {
				int counter_c = 0;
				while(counter_c == 0){
					#pragma omp atomic read
					counter_c = counter[a[ordered[i]][0]];
				}
				int help;
				#pragma omp atomic read
				help = b[a[ordered[i]][0]];
				double start = omp_get_wtime();
				while(omp_get_wtime() - start < a[ordered[i]][2]) {}
				#pragma omp atomic write
				b[ordered[i]] = help + a[ordered[i]][1];
				#pragma omp atomic write
				sumB = sumB + b[ordered[i]];
				#pragma omp atomic write
				counter[ordered[i]] = 1;
			}
		}

		#pragma omp section
		{
			//Ausgabe
			int counter_b;
			for(int i = 0; i < n; ++i) {
				counter_b = 0;
				while(!counter_b) {
					#pragma omp atomic read
					counter_b = counter[i];
				}
				#pragma omp atomic read
				counter_b = b[i];
				#pragma omp critical
				{
					cout << "b[" << i << "] = " << counter_b << "\n";
				}
			}
			cout << "sum = " << sumB << endl;
		}
	}
	return 0;
}
