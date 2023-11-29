#include"application3.h"
#define N 1024*1024*35
#define VALUE 3.5
#define MPITAG 10

void task() {
double s[N]{ VALUE };
	int thread_id, thread_count;
	for (int i = 0; i < N; i++) {
		s[i] = VALUE;
	}
	double t0=0, t1;

	MPI_Comm_size(MPI_COMM_WORLD, &thread_count);
	MPI_Comm_rank(MPI_COMM_WORLD, &thread_id);
	int pos = thread_id;
	double sum = 0;
	if (thread_id == 0) {
		t0 = MPI_Wtime();
	}
	while (pos < N) {
		sum +=VALUE
			//s[pos]
			;
		pos += thread_count;
	}
	if (thread_id != 0) {
		MPI_Send(&sum, 1, MPI_DOUBLE, 0, MPITAG, MPI_COMM_WORLD);
	}
	else {
		double totalsum = sum;
		MPI_Status stat;
		for (int i = 1; i < thread_count; i++) {
			MPI_Recv(&sum, 1, MPI_DOUBLE, i, MPITAG, MPI_COMM_WORLD, &stat);
			totalsum += sum;
		}
		t1 = MPI_Wtime();
		
		cout << "time:" << t1 - t0 << endl;
		cout << "result:" << (totalsum == VALUE * N) << endl;
	}
}