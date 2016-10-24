#include<stdio.h>

int main(void){
	int *apuntador1;
	int variable;

	apuntador1 = &variable;

	printf("%p\n", &variable);
	printf("%p\n", apuntador1);

	*apuntador1 = -10;

return 0;	
}