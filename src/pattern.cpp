#include <omp.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>

using namespace std;

int main(int argc, char * argv[]) {
	omp_set_nested(1);
	int n = atoi(argv[1]);
	int threads = atoi(argv[2]);
	cout << "n: " << n << " threads " << threads << endl;
	int count = 0;
	short a[n][n];
	int acount = 0;
	clock_t begin = clock();


	//not this loop
	for(int k = 1; k < 100; ++k) {
		//Initialisierung
		for(int i = 0; i < n; ++i) {
			srand (k * (i+1));
			for(int j = 0; j < n; ++j) {
				a[i][j] = rand() % 10;
				acount++;

			}
			for(int j = 0; j < n; ++j) {
				cout << a[i][j];
			}
			cout << endl;
		}

		//Pattern-Suche
		#pragma omp parallel for collapse(2) num_threads(threads) schedule(static) reduction(+:count)
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
		cout << "Ende suche " << k << ",found " << count << " 1234's" << endl;
		cout << "\n\n\n\n";
	}

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "time: " << elapsed_secs << endl;

	cout << "Anzahl Vorkommen: " << count << "\n";

	return 0;
}
