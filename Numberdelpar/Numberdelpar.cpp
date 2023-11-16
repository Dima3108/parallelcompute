// Numberdelpar.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include"mpi.h"
#include<fstream>
#include<string>
#include<string.h>
#include<vector>
using namespace std;
const char* INPUT_FILE = "inputdata.txt";
const char* OUTPUT_FILE = "outputdata.txt";
const char* TIME_FILE = "timedata.txt";
const char STOP_CHAR = '\0';
typedef struct MYHELPTYPE {
    long long value;
};
int str_len(char* str) {
    int len = 0;
    while (str[len] != STOP_CHAR) {
        len++;
    }
    return len;
}
int main(int* arc, char** argv)
{
     int input_data;
    string cesh;
    MPI_Request reqs[1];
    
    MPI_Init(arc, &argv);
    int thread_id, thread_count;
    MPI_Comm_size(MPI_COMM_WORLD, &thread_count);
    MPI_Status *stats=new MPI_Status[thread_count - 1];
    MPI_Comm_rank(MPI_COMM_WORLD, &thread_id);
    double t0, t1;
FILE* outputstr=NULL;
    if (thread_id == 0) {
        t0 = MPI_Wtime();
        outputstr = _fsopen(OUTPUT_FILE, "w", _SH_SECURE);
    }
    FILE* inputstr;
    
    if ((inputstr = _fsopen(INPUT_FILE, "r", _SH_DENYWR)) != NULL){
        char inpustr[40];
        if (fgets(inpustr,40, inputstr) != NULL) {
            int len = str_len(inpustr);
            if (len == 0) {
                printf("input data len =0 (thread %d) ", thread_id);

            }
            else {
            string s = "";
                 for (int i = 0; i < len; i++)
                     s += inpustr[i];
            input_data = stoll(s);
            MYHELPTYPE v_;
            v_.value = 0;
                for ( long long value = thread_id; value <= input_data; value += thread_count) 
                {
                    if (value>0 &&input_data % value == 0) {
                        //delitels_forthread.push_back(value);
                        if (thread_id != 0) {
                           // MPI_Irecv((void*)&input_data, 1, sizeof(int long long), 0, thread_id, MPI_COMM_WORLD, &reqs[0]);
                          //  cesh += to_string(value)+"\n";
                            v_.value = value;
                            //MPI_Irecv((void*)&v_, 1, sizeof(MYHELPTYPE), 0, thread_id, MPI_COMM_WORLD, &reqs[0]);
                            MPI_Isend(&v_.value, 1, MPI_LONG_LONG, 0, thread_id, MPI_COMM_WORLD, &reqs[0]);
                            printf("value on thread{ %d }: [ %d ] \n", thread_id, v_.value);
                        }
                        else {
                            fprintf(outputstr, "%s\n",to_string( value).c_str());
                        }
                    }
                }
                v_.value = 0;
                if (thread_id != 0) {
                 
                    MPI_Isend(&v_.value, 1, MPI_LONG_LONG, 0, thread_id, MPI_COMM_WORLD,&reqs[0]);
                   // MPI_Barrier(MPI_COMM_WORLD);
                }
                else {
                   // MPI_Barrier(MPI_COMM_WORLD);
                    MYHELPTYPE* buf = new MYHELPTYPE[thread_count - 1];
                    for (int i = 1; i < thread_count; i++) {
                        MPI_Recv(&(buf[i - 1].value), 1, MPI_LONG_LONG, i, i, MPI_COMM_WORLD, &stats[i - 1]);
                        while (buf[i-1].value != 0) {
                            fprintf(outputstr, "%s\n", to_string(buf[i-1].value).c_str());

                            MPI_Recv((void*)&buf[i - 1].value, 1, MPI_LONG_LONG, i, i, MPI_COMM_WORLD, &stats[i - 1]);
                        }
                    }
                }
               /* if (cesh.size()>0) {
                   const char* ccesh = cesh.c_str();
                   MPI_Irecv((void*)ccesh, cesh.size(), MPI_CHAR, 0, thread_id, MPI_COMM_WORLD, &reqs[0]);
                }*/

                
            }
           
            fclose(inputstr);
        }
        else {
            printf("not input data !(thread %d)\n", thread_id);
        }
    }
    else {
        printf("not input file! (thread %d )\n",thread_id);
        
    }
   // M

 if (thread_id == 0) {
       t1 = MPI_Wtime();
       FILE* timestr = _fsopen(TIME_FILE, "a", _SH_SECURE);
       double delta_time = t1 - t0;
       fprintf(timestr, "threadcount:[ %d ], time: [ %f ] \n", thread_count, delta_time);
       fclose(timestr);
 }
MPI_Finalize();
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
