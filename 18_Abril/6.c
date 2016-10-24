#include<stdio.h>

int main(void){

	int arreglo1[15];
	int i;
	arreglo1[0]=-3;
	arreglo1[4]=-5;
	for (int i = 0; i < 5; ++i)
	{
		printf("arreglo1[%d]= %d\n",i,arreglo1[i]);	
	}
	printf("-----\n");
	for (int i = 0; i < 5; ++i)
	{
		printf("arreglo1[%d]=%d\n",i,*(arreglo1+i));
	}

	printf("base address:%p\n",arreglo1);
	printf("más uno: %p\n",arreglo1+1 );
	printf("un byte: %p\n",(char *)arreglo1+1);
	printf("contenido: %d\n",*(arreglo1+1));
	printf("contenido mas un byte: %d\n", );
}