#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NRA 1000             
#define NCA 1000      
#define NCB 1000              


int main (int argc, char *argv[]) 
{
srand(time(NULL));

int	tid, i, j, k, chunk;
double	a[NRA][NCA],           /* Matriz A */
	      b[NCA][NCB],           /* Matriz B */
	      c[NRA][NCB];           /* Matriz resultado C */

chunk = 1;                    /* chunk para el schedule */
int nthreads=strtol(argv[1],NULL,10);
/*** Aquí empieza la parte en paralelo, definimos el scope de las variables ***/
double start_time = omp_get_wtime();
#pragma omp parallel num_threads(nthreads) shared(a,b,c,nthreads,chunk) private(tid,i,j,k)
  {
  tid = omp_get_thread_num();
  if (tid == 0)
    {
    nthreads = omp_get_num_threads();
    printf("Ejemplo de multiplicación de matrices usando OpenMP.\n");
    printf("Inicializamos la multiplicación de matrices utilizando %d threads\n",nthreads);
    printf("Inicializamos las matrices...\n");
    }
  /***  Inicializamos las matrices ***/
  #pragma omp for schedule (static, chunk) 
  for (i=0; i<NRA; i++)
    for (j=0; j<NCA; j++)
      a[i][j]= rand() % (10 + 1 - 0) + 0;
      //a[i][j]= (rand()%10+1)*.1;
  #pragma omp for schedule (static, chunk)
  for (i=0; i<NCA; i++)
    for (j=0; j<NCB; j++)
        b[i][j]= rand() % (10 + 1 - 0) + 0;
      //b[i][j]= (rand()%10+1)*.1;
  #pragma omp for schedule (static, chunk)
  for (i=0; i<NRA; i++)
    for (j=0; j<NCB; j++)
      c[i][j]= 0;

  printf("El thread %d inicia la multiplicación...\n",tid);
  #pragma omp for schedule (static, chunk)
  for (i=0; i<NRA; i++)    
    {
    printf("El thread=%d hizo el renglón=%d\n",tid,i);
    for(j=0; j<NCB; j++)       
      for (k=0; k<NCA; k++)
        c[i][j] += a[i][k] * b[k][j];
    }
  }   /*** Aquí se termina la parte en paralelo ***/
double time = omp_get_wtime()-start_time;

printf("El tiempo de ejecucion fue: %f\n",time);

/*** Impresión de resultados ***/
printf("******************************************************\n");
printf("Matrix A:\n");
for (i=0; i<NRA; i++)
  {
  for (j=0; j<NCA; j++) 
    printf("%6.2f   ", a[i][j]);
    printf("\n"); 
  }
printf("******************************************************\n");

printf("******************************************************\n");
printf("Matrix B:\n");
for (i=0; i<NCA; i++)
  {
  for (j=0; j<NCB; j++) 
    printf("%6.2f   ", b[i][j]);
    printf("\n"); 
  }
printf("******************************************************\n");


printf("******************************************************\n");
printf("Result Matrix:\n");
for (i=0; i<NRA; i++)
  {
  for (j=0; j<NCB; j++) 
    printf("%6.2f   ", c[i][j]);
    printf("\n"); 
  }
printf("******************************************************\n");
printf ("Done.\n");
}