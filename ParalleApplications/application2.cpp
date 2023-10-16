#include"application2.h"
#define MNOGIT 1
float vector_forsum[VECTOR_LENGTH];
float vector_sum[MAX_THREAD_COUNT];
void vector_sum_init(float* vector, int vlength) {
	for (int i = 0; i < vlength; i++) {
		vector[i] = MNOGIT;
	}
}
void vector_sum_compute(float* vector, int vlength, int thread_id, int offset, float* sum_vector) {
	int pos = thread_id;
	sum_vector[thread_id] = 0;
	while (pos < vlength) {
		sum_vector[thread_id] += vector[pos];
		pos += offset;
	}
}
void task2() {
	int proc_count, proc_this;
	MPI_Comm_size(MPI_COMM_WORLD, &proc_count);
	MPI_Comm_rank(MPI_COMM_WORLD, &proc_this);

	printf("Hello, I’m processor No_%d from %d\n", proc_this, proc_count);
}

void task2_2(int* arc, char** argv) {
	int proc_count,proc_this;
	MPI_Comm_size(MPI_COMM_WORLD, &proc_count);
	//MPI_Finalize();
	cout << "task2_2:\n";
	cout << "vector init:\n";
	vector_sum_init(vector_forsum, VECTOR_LENGTH);
	cout << "vector_compute\n";
	//MPI_Init(arc,&argv);
	//MPI_Comm_size(MPI_COMM_WORLD, &proc_count);
	MPI_Comm_rank(MPI_COMM_WORLD, &proc_this);
	vector_sum_compute(vector_forsum, VECTOR_LENGTH, proc_this, proc_count, vector_sum);
	MPI_Finalize();
	cout << "vector result:\n";
	float totsum = 0;
	for (int i = 0; i < proc_count; i++)
		totsum += vector_sum[i];
	if (totsum == VECTOR_LENGTH * MNOGIT) {
		cout << "true\n";
	}
	else {
		cout << "false";
	}
	//MPI_Init(arc, &argv);
}