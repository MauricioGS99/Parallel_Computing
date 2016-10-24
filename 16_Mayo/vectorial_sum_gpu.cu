#include<stdio.h>
#define N 10

__global__ void add(int *a, int *b, int*c){
	int tid=blockIdx.x;
	if(tid<N)
			c[tid] = a[tid] + b[tid];
}

int main(void){
	int a[N], b[N], c[N];
	int *dev_a, *dev_b, *dev_c;
	int i;

	//Allocate memory in GPU
	culdaMalloc((void***) &dev_a, N*sizeof(int));
	culdaMalloc((void***) &dev_b, N*sizeof(int));
	culdaMalloc((void***) &dev_c, N*sizeof(int));

	//Fill a and b
	for(i=0; i<N; i++){
	a[i]=i;
	b[i]=i*i;
	}

	//copy the arrays to the GPY
	cudaMemcpy(dev_a,a,N*sizeof(int),cudaMemcpyHostToDevice);
	cudaMemcpy(dev_b,b,N*sizeof(int),cudaMemcpyHostToDevice);

	//call to add:
	add<<N,1>>(dev_a,dev_b,dev_c); // N blocks of threads, 1 per block

	//copy the result array 'c' back from the GPU to the CPU
	cudaMemcpy(c,dev_c,N*sizeof(int), cucaMemcpyDevicetoHost);

	//print c
		for(i=0;i<N,i++){
		printf("%d + %d = %d\n",a[i],b[i],c[i]);
	}
	cudaFree(dev_a);
	cudaFree(dev_b);
	cudaFree(dev_c);

	return 0;

}