// SlinSortOMP.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<omp.h>
#define PI 3.14
#define EPS 0.333
#define N 1024*128
#define MIN(a,b) (a<b)?a:b
#define MAX(a,b) (a>b)?a:b
#define BLOCK_SIZE N/THREAD_COUNT
#define THREAD_COUNT 8
using namespace std;
double GenerateValue() {
    
    return 1024.00 - 2048.00 * sin((PI/ (rand() + EPS)) - EPS);
    
}
int main()
{
    double* array_i = new double[N];
    srand(time(0));
    for (int i = 0; i < N; i++)
        array_i[i] = GenerateValue();
omp_set_num_threads(THREAD_COUNT);
    std::cout << "start sort" << endl;
    
    double t0 = omp_get_wtime();
    int block_size = BLOCK_SIZE;
    while (block_size <=N) 
    {
        #pragma omp parallel 
        {
        #pragma omp for nowait 
           for (int thread = 0; thread < THREAD_COUNT; thread++)
           {
            //int thread = omp_get_thread_num();
               for (int offset = omp_get_thread_num(); offset < N / block_size; offset += THREAD_COUNT) 
               {
                     double  min, max;
                     for (int i = 0; i < block_size - 1; i++) 
                     {
                          for (int j = i + 1; j < block_size; j++) 
                          {
                             min = MIN(array_i[(block_size * offset) + i], array_i[(block_size * offset) + j]);
                             max = MAX(array_i[(block_size * offset) + i], array_i[(block_size * offset) + j]);
                             array_i[(block_size * offset) + i] = min;
                             array_i[(block_size * offset) + j] = max;
                          }
                     }
               }
           }
        }
        block_size *= 2;
        //std::cout << block_size << endl;
        printf("%d\n",block_size);
    }
    double t1 = omp_get_wtime();
    std::cout << "test" << std::endl;
    bool Suc = true;
    for(int i=0;i<N-1;i++)
        if (array_i[i] > array_i[i + 1]) {
            Suc = false;
            break;
        }
    delete[]array_i;
    std::cout << (t1 - t0) / 1000 << endl;
    std::cout << Suc << endl;
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
