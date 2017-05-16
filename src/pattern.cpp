#include <omp.h>
#include <stdio.h>

int main() {
	int id;
	omp_set_num_threads(4);
	#pragma omp parallel private(id)
	{
		id = omp_get_thread_num();
		printf("%d: Hello World!\n", id);
	}
	return 0;
}
