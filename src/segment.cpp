#include <omp.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int main(int argc, char * argv[]) {
	// init parallel
	int n = atoi(argv[1]);
	int threads = atoi(argv[2]);
	omp_set_num_threads(threads);

	int a[n];
	long summe = 0;

	//init a, summe
	srand(4321);
	for(int i = 0; i < n; ++i) {
		a[i] = (rand() % 100 + 1);
		summe += a[i];
	}

	long m[n/2-1];
	int counter = 0;
	m[0] = summe;
	long sumM = 0;


	//main parallel part
	#pragma omp parallel for ordered schedule(dynamic) num_threads(threads) reduction(+:sumM)
	for(int anzahl = 2; anzahl <= n/2; anzahl++) {
		long mitte = 0;
		long links = m[0]/anzahl;
		int help;
		#pragma omp atomic read
		help = counter;
		long rechts = m[help];
		long smallest = m[help];
		long segmentCount;
		long biggest;
		long segment;

		while (links <= rechts) {
			// halve area for each cycle as long as the maxima dont hit each other
			mitte = links + ((rechts - links) / 2);
			segment = 0;
			biggest = 0;
			segmentCount = anzahl-1;
			for(int i = 0; i < n; i++) {
				// if the current segment is to big search the next segment
				if(segment + a[i] <= mitte) {
					segment += a[i];
				} else if(segmentCount > 0) {
					if(segment > biggest) {
						biggest = segment;
					}
					segment = a[i];
					segmentCount--;
				} else {
					segment += a[i];
				}
			}
			if(segment > biggest) {
				biggest = segment;
			}
			if(biggest < smallest) {
				smallest = biggest;
			}
			if(biggest > mitte) {
				links = mitte+1;
			} else {
				rechts = mitte-1;
			}
		}
		// add smallest for the current part and increase counter
		#pragma omp ordered
		{
			#pragma omp atomic write
			m[anzahl-1] = smallest;
			#pragma omp atomic write
			counter = counter + 1;
		}
		sumM += smallest;
	}

	//2, 3, 5, n/4, n/2 - 1, n/2
	cout << "M[2]=" << m[1] << endl;
	cout << "M[3]="  << m[2] << endl;
	cout << "M[5]="  << m[4] << endl;
	cout << "M[" << n/4 << "]="  << m[n/4-1] << endl;
	cout << "M[" << n/2-1 << "]="  << m[((n/2)-2)] << endl;
	cout << "M[" << n/2 << "]="  << m[(n/2-1)] << endl;
	cout << "sum=" << sumM << endl;
}
