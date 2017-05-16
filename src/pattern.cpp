#include <omp.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <ctime>
using namespace std;

int main(int argc, char * argv[]) {
	int n = atoi(argv[1]);
	int threads = atoi(argv[2]);

	//TODO: fix stackoverflow for higher values for n
	n = 1000;
	threads = 1;

	chrono::time_point<chrono::system_clock> start, end;
	start = chrono::system_clock::now();

	int count = 0;
	short a[n][n];
	for(int k = 1; k < 100; ++k) {
		//Initialisierung
		for(int i = 0; i < n; ++i) {
			srand(k * (i + 1));
			for(int j = 0; j < n; ++j) {

				a[i][j] = rand() % 10;
			}
		}

		//Pattern-Suche
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j) {
				if(a[i][j] == 1) {
					if(j+3 < n && a[i][j+1] == 2 && a[i][j+2] == 3 && a[i][j+3] == 4) {
						count++;
//						cout << "k=" << k << ", horizontal ab a[" <<  i << ", " << j << "]\n";
//						for(int i = 0; i < n; ++i) {
//							for(int j = 0; j < n; ++j) {
//								cout << " " << a[i][j];
//							}
//							cout << "\n";
//						}

					}
					if(i+3 < n && a[i+1][j] == 2 && a[i+2][j] == 3 && a[i+3][j] == 4) {
						count++;
//						cout << "k=" << k << ", vertikal ab a[" <<  i << ", " << j << "]\n";
//						for(int i = 0; i < n; ++i) {
//							for(int j = 0; j < n; ++j) {
//								cout << " " << a[i][j];
//							}
//							cout << "\n";
//						}
					}
				}
			}
		}
	}

	end = chrono::system_clock::now();
	chrono::duration<double> elapsed_seconds = end-start;
	cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

	cout << "Anzahl Vorkommen: " << count;
	return 0;
}
