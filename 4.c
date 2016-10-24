#include<stdio.h>

int main(void){
	int *p;
	int c;

	printf("valor de c: %d\n",c);
	printf("Valor de p: %p\n",p);
	printf("Direccion de memoria de c: %p\n",&c);
	p = &c;
	printf("valor de p: %p\n",p);
return 0;
}