#include <omp.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

int main(int argc, char * argv[]) {
	omp_set_nested(1);
	omp_set_max_active_levels(2);
	int n = atoi(argv[1]);
	int threads = atoi(argv[2]);
	cout << "n: " << n << " threads " << threads << endl;

	double begin = omp_get_wtime();

	long sumB = 0;
	long b[n];
	bool counter[n];
	int a[n][3];

	b[0] = 0;
	counter[0] = 1;

	srand(123);
	a[0][0] = a[0][1] = a[0][2] = 0;
	//sequentiell!
	for(int i = 1; i < n; ++i) {
		a[i][0] = rand() % i;
		a[i][1] = (rand() % 19) - 9;
		a[i][2] = (rand() % 3) + 1;
		cout << a[i][0] << endl;
	}

	#pragma omp parallel sections num_threads(threads) shared(counter,b)
	{
		#pragma omp section
		{
			//Berechnung
			double start;
			int help;
			#pragma omp parallel for schedule(dynamic) private(help) shared(counter,b) num_threads(threads-1)
			for(int i = 1; i < n; ++i) {
				int halp = 0;
				while(halp == 0){
					//warte
					#pragma omp atomic read
					halp = counter[a[i][0]];
				}
				#pragma omp atomic read
				help = b[a[i][0]];

				start = omp_get_wtime();
				while(omp_get_wtime() - start < a[i][2]/10) {} //very complicated calculation
				b[i] = help + a[i][1];
				#pragma omp atomic write
				counter[i] = 1;
			}
		}
		#pragma omp section
		{
			//Ausgabe
			for(int i = 0; i < n; ++i) {
				int halp = 0;
				while(halp == 0) {
					#pragma omp atomic read
					halp = counter[i];
				}
				#pragma omp atomic read
				halp = b[i];
				cout << "b[" << i << "] = " << halp<< "\n";
				sumB += halp;
			}
			cout << "sum = " << sumB << endl;
		}
	}

	double end = omp_get_wtime();
	cout << "time: " << end-begin << endl;

	return 0;
}
