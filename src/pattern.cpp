#include <omp.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
int main(int argc, char * argv[]) {
	int n = atoi(argv[1]);
	int threads = atoi(argv[2]);
	cout << "n: " << n << " threads " << threads << endl;
	int a[n][n];
	int count = 0;
	double start, end, sum = 0;

	//not this loop
	for(int k = 1; k < 100; ++k) {
		//Initialisierung
		#pragma omp parallel for num_threads(threads) schedule(static)
		for(int i = 0; i < n; ++i) {
			#pragma omp critical
			{
				srand(k * (i+1));
				for(int j = 0; j < n; ++j) {
					a[i][j] = rand() % 10;
				}
			}
		}
		start = omp_get_wtime();

		//Pattern-Suche
		#pragma omp parallel for num_threads(threads) schedule(static) reduction(+:count)
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j) {
				if(a[i][j] == 1) {
					if(j+3 < n && a[i][j+1] == 2 && a[i][j+2] == 3 && a[i][j+3] == 4) {
						count++;

					}
					if(i+3 < n && a[i+1][j] == 2 && a[i+2][j] == 3 && a[i+3][j] == 4) {
						count++;
					}
				}
			}
		}
		end = omp_get_wtime();
		sum += end - start;
	}

	cout << "Anzahl Vorkommen: " << count << "\n";
	cout << "Zeit: " << sum << endl;
	return 0;
}
