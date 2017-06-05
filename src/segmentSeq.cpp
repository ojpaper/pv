#include <omp.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;

/*int summe(vector<int> a) {
	int sum = 0;
	for(vector<int>::iterator it=a.begin(); it != a.end(); it++) {
		sum += *it;
	}
	return sum;
}*/

int main(int argc, char * argv[]) {
	int n = atoi(argv[1]);
	int threads = atoi(argv[2]);

	//aufeinanderfolgende zahlen: 94, 14, ...
//	vector<int> a = {
//			94,
//			14,
//			74,
//			31,
//			80,
//			32,
//			96,
//			23,
//			27,
//			2
//	};//n = 10, seed = 123
	int a[n];
	long summe = 0;

	double begin = omp_get_wtime();

	srand(4321);
	for(int i = 0; i < n; ++i) {
		a[i](rand() % 100 + 1);
		summe += a[i];
		//		cout << a[i] << endl;
	}

//	vector<long> m;

	long m[n+1];
	int pushBackCounter = 0;
	m[pushBackCounter++] = summe;
	//m.push_back(s);

	cout << summe << endl;

	for(int anzahl = 2; anzahl <= n/2; anzahl++) {
		int mitte = 0;
		long links = summe/anzahl;
		long rechts = summe;
		long segmentCount;
		long smallest = summe;
		long biggest;
		long segment;

		/* Solange die zu durchsuchende Menge nicht leer ist */
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
		//m.push_back(smallest);
	}

	/*2, 3, 5, n/4, n/2 - 1, n/2
	 *
	 */

	cout << "M(m=2) = " << m[1] << endl;
	cout << "M(m=3) = "  << m[2] << endl;
	cout << "M(m=5) = "  << m[4] << endl;
	cout << "M(m=" << n/4 << ")= "  << m[n/4-1] << endl;
	cout << "M(m=" << n/2-1 << ") = "  << m[((n/2)-2)] << endl;
	cout << "M(m=" << n/2 << ") = "  << m[(n/2-1)] << endl;

	double end = omp_get_wtime();
	cout << "time: " << end-begin << endl;
}
