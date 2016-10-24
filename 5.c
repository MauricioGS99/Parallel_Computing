#include<stdio.h>
int main(void){
	int a=1;
	int b=2;
	int c=3;
	int *p;
	int *q;

	p=&a;
	q=&b;
	c=*p;
	p=q;
	*p=13;

	printf("el valor de a es: %d\n",a);
	printf("el valor de b es: %d\n",b);
	printf("el valor de c es: %d\n",c);
}