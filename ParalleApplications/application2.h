#pragma once
#ifndef APPLICATION_2
#define APPLICATION_2
#include "pch.h";
#define VECTOR_LENGTH 1024*1024
#define MAX_THREAD_COUNT 256
void task2_2(int* arc, char** argv);
void task2();
void vector_sum_init(float* vector,int vlength);
void vector_sum_compute(float* vector,int vlength,int thread_id,int offset,float *sum_vector);
//void vector_sum_write(float* vector,int vlength);

#endif // !APPLICATION_2
