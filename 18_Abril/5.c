#include<stdio.h>

cambio(int *x int *y){
	int temp;

		temp=*x;
		*x=*y;
		*y=*temp;
}

int main(void){
	int a=1;
	int b=2;

	cambio(&a,&b);

	printf("valor de a: %d\n",a);
	printf("valor de b: %d\n",b);
}