#include"forcontrol.h"
#define N 1024*1024*1024
#define COMM_WORL MPI_COMM_WORLD
typedef unsigned char CHAR;
void prop_spos() {
	int thread_count, thread_id;
	MPI_Comm_size(COMM_WORL, &thread_count);
	if (thread_count <= 1) {
		printf("not enough processes (minimum 2)!");
	}
	else {
MPI_Comm_rank(COMM_WORL, &thread_id);

         if (thread_id == 0) {
              //array init
			 CHAR* buffer = (CHAR*)malloc(sizeof(CHAR) * N);
			 srand(time(0));
			 for (int i = 0; i < N; i++) {
				 buffer[i] =abs( rand()) % 256;
			 }
			 for (int proc = 1; proc < thread_count; proc++) {
				 MPI_Send(buffer, N, MPI_CHAR, proc, 0, COMM_WORL);
			 }
			 free(buffer);
         }
		 else {
			 MPI_Status stat;
			 //для остальных процессов
			 while (MPI_Probe(0,0,COMM_WORL,&stat)!=MPI_SUCCESS) {

			 }
			 double t0 = MPI_Wtime();
			 CHAR* buffer = new CHAR[N];
			 MPI_Recv(buffer, N, MPI_CHAR, 0, 0, COMM_WORL, &stat);
			 double t1 = MPI_Wtime();
			 delete []buffer;
			 double delta = t1 - t0;
			 double scor_bs = N / delta;
			 double scor_kbs = scor_bs / 1024;
			 double scor_mbs = scor_kbs / 1024;
			 double scor_gbs = scor_mbs / 1024;
			 double scor_tbs = scor_gbs / 1024;
			 double scor_kbm = ((N/delta)*60)/1024;
			 double scor_mbm = scor_kbm / 1024;
			 double scor_mbh = ((N/delta)*60*60)/(1024*1024);
			 double scor_gbm = scor_mbm / 1024;
			 double scor_gbh = scor_mbh/1024;
			 printf("read %f B/s for procces %d\n", scor_bs,thread_id);
			 printf("read %f KB/s for procces %d\n", scor_kbs,thread_id);
			 printf("read %f MB/s for procces %d\n", scor_mbs, thread_id);
			 printf("read %f GB/s for procces %d\n", scor_gbs, thread_id);
			 printf("read %f TB/s for procces %d\n", scor_tbs, thread_id);
			 printf("read %f KB/m for procces %d\n", scor_kbm, thread_id);
			 printf("read %f MB/m for procces %d\n", scor_mbm, thread_id);
			 printf("read %f MB/h for procces %d\n", scor_mbh, thread_id);
			 printf("read %f GB/m for procces %d\n", scor_gbm, thread_id);
			 printf("read %f GB/h for procces %d\n", scor_gbh, thread_id);
		 }
	}
	

}