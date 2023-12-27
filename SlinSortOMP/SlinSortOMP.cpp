// SlinSortOMP.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <future>
#include<random>
#include<omp.h>
#define PI 3.14
#define EPS 0.333
#define N 20
/*#define MIN(a,b) (a<b)?a:b
#define MAX(a,b) (a>b)?a:b
#define BLOCK_SIZE 2
#define THREAD_COUNT 1*/
#define VALUE 100
using namespace std;
void print(double* mas,int n) {
    for (int i = 0; i < n; i++) {
        printf("%f,", mas[i]);
    }
    printf("\n");
}
void Merge(double* arr1, int count1, double* arr2, int count2, double* mas);
void MergeSort(double* array, int arrayLen);

void Merge(double* arr1, int count1, double *arr2, int count2,double*mas) {
    // mas = new double[count1+count2];
    int ptr1 = 0, ptr2 = 0;
    for (int i = 0; i < count1+count2; i++) {
        if (ptr1 < count1 && ptr2 < count2)
        {
            mas[i] = arr1[ptr1] > arr2[ptr2] ? arr1[ptr1++] : arr2[ptr2++];
        }
        else
        {
            mas[i] = ptr2 < (count2) ? arr2[ptr2++] : arr1[ptr1++];
        }
    }

   // print(mas,count1+count2);

   
}
void MergeSort(double* array,int arrayLen)
{
    if (arrayLen == 1)
    {
      
    }
    else {


        int middle = static_cast<int>(arrayLen / 2);
        double* arr1 = new double[middle];
        double* arr2 = new double[arrayLen - middle];
        for (int i = 0; i < middle; i++) {
            arr1[i] = array[i];
        }
        int p = 0;
        for (int i = middle; i < arrayLen; i++) {
            arr2[p++] = array[i];
        }
        p = 0;
int c = arrayLen - middle;
       
  /* auto t1 = std::async(std::launch::async, [arr1, middle] {
    MergeSort(arr1, middle);
             });
auto t2=std::async(std::launch::async, [arr2, c] {
    MergeSort(arr2,c);
            });
t1.wait();
t2.wait();*/
        
       thread t1, t2;
        
        t1 = thread(&MergeSort, arr1, middle);
        t2 = thread(&MergeSort, arr2, c);
        t1.join();
        t2.join();
       /* MergeSort(arr1, middle);
        MergeSort(arr2, c);*/
        double* cesh = new double[arrayLen];
        Merge(arr1, middle, arr2, c, cesh);
        delete[]arr1;
        delete[]arr2;
        for (int i = 0; i < arrayLen; i++) {
            array[i] = cesh[i];
        }
        delete[]cesh;
    }
  
}
void print(double *mas) {
    for (int i = 0; i < N; i++) {
        printf("%f,", mas[i]);
    }
    printf("\n");
}
double GenerateValue(double val) {
    double t = val;
    while (abs(t) > VALUE)
        t /= 10.0;
    return VALUE-2*VALUE*sin((PI/(t-EPS))+EPS);
}
int main()
{
    double* array_i = new double[N];
    random_device rd;   // non-deterministic generator
    mt19937 gen(rd());  // to seed mersenne twister.
    // replace the call to rd() with a
    // constant value to get repeatable
    // results.
   
    for (int i = 0; i < N; i++)
        array_i[i] = gen();
    for (int i = 0; i < N; i++) {
        double v = array_i[i];
        array_i[i] = GenerateValue(v);
    }
    printf("input:\n");
    print(array_i);

    std::cout << "start sort" << endl;
    
    double t0 = omp_get_wtime();
    MergeSort(array_i, N);
    double t1 = omp_get_wtime();
    printf("\noutput\n");
    print(array_i);
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
