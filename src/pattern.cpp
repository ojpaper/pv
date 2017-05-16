//============================================================================
// Name        : pv1.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int main(int argc, char * argv[]) {
	// Display each command-line argument.
	cout << "\nCommand-line arguments:\n";
	for(int i = 0; i < argc; i++ ) {
		cout << "  argv[" << i << "]   " << argv[i] << "\n";
	}

	int n = atoi(argv[1]);
	int threads = atoi(argv[2]);

	int id;
	omp_set_num_threads(threads);
	#pragma omp parallel private(id)
	{
		id = omp_get_thread_num();
		printf("%d: Hello World!\n", id);
	}

	int count = 0;
	short a[n][n];
	for(int k = 1; k < 100; ++k) {
		//Initialisierung
		for(int i = 0; i < n; ++i) {
			srand(k * (i+1));

			for(int j = 0; j < n; ++j) {
				a[i][j] = rand() % 10;
			}
		}

		//Pattern-Suche
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j) {
				if(a[i][j] == 1) {
					if(j+3 < n && a[i][j+1] == 2) {
						if(a[i][j+2] == 3) {
							if(a[i][j+3] == 4) {
								count++;
							}
						}
					}
					if(i+3 < n && a[i+1][j] == 2) {
						if(a[i+2][j] == 3) {
							if(a[i+3][j] == 4) {
								count++;
							}
						}
					}
				}
			}
		}
	}

	cout << "Anzahl Vorkommen: " << count;
	return 0;
}
