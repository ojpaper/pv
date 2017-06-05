#include <omp.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;

int summe(vector<int> a) {
	int sum = 0;
	for(vector<int>::iterator it=a.begin(); it != a.end(); it++) {
		sum += *it;
	}
	return sum;
}

int main(int argc, char * argv[]) {
	int n = atoi(argv[1]);
	int threads = atoi(argv[2]);

	//aufeinanderfolgende zahlen: 94, 14, ...
	vector<int> a = {
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
	};//n = 10, seed = 123

	double begin = omp_get_wtime();

	srand(4321);
	for(int i = 0; i < n; ++i) {
		a.push_back(rand() % 100 + 1);
		//		cout << a[i] << endl;
	}

	long s = summe(a);
	vector<long> m;
	m.push_back(s);

	cout << s << endl;

	for(int anzahl = 2; anzahl <= n/2; anzahl++) {
		int mitte = 0;
		long links = s/anzahl;
		long rechts = s;
		long segmentCount;
		long smallest = s;
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
				if(segment+a.at(i) <= mitte) {
					segment += a.at(i);
				} else if(segmentCount > 0) {
					if(segment > biggest) {
						biggest = segment;
					}
					segment = a.at(i);
					segmentCount--;
				} else {
					segment += a.at(i);
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
		m.push_back(smallest);
	}

	/*2, 3, 5, n/4, n/2 - 1, n/2
	 *
	 */

	cout << "M(m=2) = " << m.at(1) << endl;
	cout << "M(m=3) = "  << m.at(2) << endl;
	cout << "M(m=5) = "  << m.at(4) << endl;
	cout << "M(m=" << n/4 << ")= "  << m.at(n/4-1) << endl;
	cout << "M(m=" << n/2-1 << ") = "  << m.at((n/2)-2) << endl;
	cout << "M(m=" << n/2 << ") = "  << m.at(n/2-1) << endl;

	double end = omp_get_wtime();
	cout << "time: " << end-begin << endl;
}
