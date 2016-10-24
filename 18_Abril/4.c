#include<stdio.h>

int main(void){

	char *s[] = {"Cosas que vuelan", "animal", "vegetal"};
	printf("%p\n",s );
	printf("%c\n", *s[0]); //letra c
	printf("%p\n",s[0]); //direccion de memoria
	printf("%s\n",s[1] ); //animal
	printf("%c\n",*(*s+1));
	printf("%c\n",*(*(s+2)+1)); //deberia imprimir la e de vegetal
	printf("n de animal: %c\n", *(*(s+1)+1)	);

return 0;
}