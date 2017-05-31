#include <omp.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

int main(int argc, char * argv[]) {
	omp_set_nested(1);
	omp_set_max_active_levels(2);
	int n = atoi(argv[1]);
	int threads = atoi(argv[2]);
	omp_set_num_threads(threads);
	cout << "n: " << n << " threads " << threads << endl;

	long sumB;
	long b[n];
	bool counter[n];
	int a[n][3];

	sumB = b[0] = 0;
	counter[0] = 1;
	a[0][0] = a[0][1] = a[0][2] = 0;

	srand(123);
	//sequentiell!
	for(int i = 1; i < n; ++i) {
		b[i] = 0;
		counter[i] = 0;
		a[i][0] = rand() % i;
		a[i][1] = (rand() % 19) - 9;
		a[i][2] = (rand() % 3) + 1;
	}

	#pragma omp parallel sections
	{
		#pragma omp section
		{
			#pragma omp parallel for schedule(dynamic) num_threads(threads-1)
			//Berechnung
			for	(int i = 1; i < n; ++i) {
				int counter_c = 0;
				while(counter_c == 0){
					#pragma omp atomic read
					counter_c = counter[a[i][0]];
				}
				int help;
				#pragma omp atomic read
				help = b[a[i][0]];
				double start = omp_get_wtime();
				while(omp_get_wtime() - start < a[i][2]/10) {} //very complicated calculation
				#pragma omp atomic write
				b[i] = help + a[i][1];
				#pragma omp atomic write
				sumB = sumB + b[i];
				#pragma omp atomic write
				counter[i] = 1;
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
