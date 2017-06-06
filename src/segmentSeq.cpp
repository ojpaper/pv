#include <omp.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int main(int argc, char * argv[]) {
	int n = atoi(argv[1]);

	int a[n];
	long summe = 0;

	srand(4321);
	for(int i = 0; i < n; ++i) {
		a[i] = (rand() % 100 + 1);
		summe += a[i];
	}

	long m[n/2-1];
	int pushBackCounter = 0;
	m[pushBackCounter++] = summe;

	cout << summe << endl;

	for(int anzahl = 2; anzahl <= n/2; anzahl++) {
		int mitte = 0;
		long links = summe/anzahl;
		long rechts = summe;
		long segmentCount;
		long smallest = summe;
		long biggest;
		long segment;

		while (links <= rechts)
		{
			mitte = links + ((rechts - links) / 2); /* Bereich halbieren */
			segment = 0;
			biggest = 0;
			segmentCount = anzahl-1;
			for(int i = 0; i < n; i++) {
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
				links = mitte + 1;
			} else {
				rechts = mitte - 1;
			}
		}
		m[pushBackCounter++] = smallest;
	}

	//2, 3, 5, n/4, n/2 - 1, n/2
	cout << "M(m=2) = " << m[1] << endl;
	cout << "M(m=3) = "  << m[2] << endl;
	cout << "M(m=5) = "  << m[4] << endl;
	cout << "M(m=" << n/4 << ")= "  << m[n/4-1] << endl;
	cout << "M(m=" << n/2-1 << ") = "  << m[((n/2)-2)] << endl;
	cout << "M(m=" << n/2 << ") = "  << m[(n/2-1)] << endl;
}
