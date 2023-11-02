#include"application4.h"
void task4base() {
	int size, threadid;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &threadid);
	int* buffer = new int[size];
	MPI_Request reqs[4];
	MPI_Status stat[4];
	int tag1 = 1, tag2 = 2;
	int pred = threadid - 1;
	int next = threadid + 1;
	if (pred < 0) {
		pred = size - 1;
	}
	if (next >= size) {
		next = 0;
	}
	buffer[threadid] = threadid;
	MPI_Irecv(&buffer[pred], 1, MPI_INT, pred, tag1, MPI_COMM_WORLD, &reqs[0]);
	MPI_Irecv(&buffer[next], 1, MPI_INT, next, tag2, MPI_COMM_WORLD, &reqs[1]);
	MPI_Isend(&threadid, 1, MPI_INT, pred, tag1, MPI_COMM_WORLD, &reqs[2]);
	MPI_Isend(&threadid, 1, MPI_INT, next, tag2, MPI_COMM_WORLD, &reqs[3]);
	MPI_Waitall(4, reqs, stat);
	bool* m = new bool[size];
	for (int i = 0; i < size; i++) {
		m[i] = false;
	}
	for (int i = 0; i < size; i++) {
		m[buffer[i]] = true;
	}
	for (int i = 0; i < size; i++) {
		if (m[i] == false)
			cout << "error on thread{" << i << "}in thread{" << threadid << "}\n";
	}
	delete m;
	delete buffer;
	//delete reqs;
	//delete stat;
}