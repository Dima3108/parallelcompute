
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <iostream>
#include <stdio.h>

#define PI 3.14
#define EPS 0.0313
#define N 1024*10
#define THREADS_PER_BLOCK 256
#define BLOCK_COUNT 256

cudaError_t SortWithCuda(double* array_,int*array_pos, int block_size, int Length);

__global__ void SlimSortKernel(double* array, int ArLength, int BlockSize) {
    int pos =threadIdx.x+ blockIdx.x*blockDim.x;
    if (pos < ArLength) {
        array_pos
   }
}
int main()
{

    double* dat = new double[N];
    double sum = 0,control_sum=0;
    srand(time(0));
    for (int i = 0; i < N; i++) {
        dat[i] = 256 - 512 * sin((PI / (rand() - EPS)) - EPS);
        //sum += dat[i];

    }
    for (int i = 0; i < N; i++)
        sum += dat[i];
    // Add vectors in parallel.
    cudaError_t cudaStatus=cudaSuccess;
   // cudaStatus= addWithCuda(c, a, b, arraySize);
    cudaStatus = SortWithCuda(dat, 2, N);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "addWithCuda failed!");
        //return 1;
        goto Error;
    }
    bool suc = true;
    ;
    for (int i = 0; i < N-1; i++) {
        control_sum += dat[i];
        if (dat[i] > dat[i + 1]) {
            suc = false;
            break;
        }
    }
    for (int i = 0; i < N; i++)
        control_sum += dat[i];
    if (!suc) {

        printf("error sort!\n");
       
    }
    if (sum != control_sum) {
 printf("{%d}:{%d}", control_sum, sum);
    }
    /*printf("{1,2,3,4,5} + {10,20,30,40,50} = {%d,%d,%d,%d,%d}\n",
        c[0], c[1], c[2], c[3], c[4]);*/

    // cudaDeviceReset must be called before exiting in order for profiling and
    // tracing tools such as Nsight and Visual Profiler to show complete traces.
    cudaStatus = cudaDeviceReset();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaDeviceReset failed!");
        //return 1;
        goto Error;
    }
Error:
    delete[]dat;
    return 0;
}

// Helper function for using CUDA to add vectors in parallel.

cudaError_t SortWithCuda(double* array_,int block_size,int Length) {
    double* dev_a = 0;
    double* dev_pos_a = 0;

    cudaError_t cudaStatus;
    cudaStream_t cudaStream = 0;

    // Choose which GPU to run on, change this on a multi-GPU system.
    cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
        goto Error;
    }
    cudaStatus = cudaStreamCreate(&cudaStream);
    // Allocate GPU buffers for three vectors (two input, one output)    .
    cudaStatus = cudaMalloc((void**)&dev_a, Length * sizeof(double));
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }
    cudaStatus = cudaMalloc((void**)&dev_pos_a, Length * sizeof(int));
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }
    cudaStatus = cudaMemcpy(dev_a, array_, Length * sizeof(double), cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }
    while (block_size<=Length)
    {
        printf("block_size:%d\n", block_size);
        dim3 size(256, 256);
        SlimSortKernel<<<BLOCK_COUNT,THREADS_PER_BLOCK,0,cudaStream>>>(dev_a,dev_pos_a, Length, block_size);
      //  cudaStatus = cudaThreadSynchronize();
        if (cudaStatus != cudaSuccess) {
            fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching addKernel!\n", cudaStatus);
            fprintf(stderr, "cuda error%s", cudaGetErrorString(cudaStatus));
            goto Error;
        }
        cudaStatus = cudaDeviceSynchronize();
        if (cudaStatus != cudaSuccess) {
      
          fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching addKernel!\n", cudaStatus);
                fprintf(stderr, "cuda error%s", cudaGetErrorString(cudaStatus));
          goto Error;
        }
        
        if (block_size < Length) {
block_size *= 2;
if (block_size > Length) {
    block_size = Length;
}
        }
        else {
            break;
        }
        
    }
    cudaStatus = cudaMemcpy(array_, dev_a, Length * sizeof(double), cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

Error:
    cudaFree((void*)dev_a);
    cudaStreamDestroy(cudaStream);
    return cudaStatus;
}