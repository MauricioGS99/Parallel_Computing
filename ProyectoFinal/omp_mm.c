#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define NRA 4                 /* number of rows in matrix A */
#define NCA 4               /* number of columns in matrix A */
#define NCB 4                 /* number of columns in matrix B */


int main (int argc, char *argv[]) 
{
int	tid, nthreads, i, j, k, chunk;
double	a[NRA][NCA],           /* matrix A to be multiplied */
	      b[NCA][NCB],           /* matrix B to be multiplied */
	      c[NRA][NCB];           /* result matrix C */

chunk = 10;                    /* set loop iteration chunk size */

int thread_count = strtol(argv[1],NULL,10);

printf("Ejemplo de multiplicación de matrices usando OpenMP.\n");
printf("Starting matrix multiple example with %d threads\n",thread_count);
printf("Initializing matrices...\n");

/*** Spawn a parallel region explicitly scoping all variables ***/
double start_time = omp_get_wtime();
#pragma omp parallel num_threads(thread_count) shared(a,b,c,thread_count,chunk) private(tid,i,j,k)
{
  tid = omp_get_thread_num();

  nthreads = omp_get_num_threads();   

  /*** Initialize matrices ***/
  #pragma omp for num_threads(thread_count) schedule(static, chunk) 
  for (i=0; i<NRA; i++)
    for (j=0; j<NCA; j++)
      a[i][j]= i+j+1;
  #pragma omp for num_threads(thread_count) schedule(static, chunk)
  for (i=0; i<NCA; i++)
    for (j=0; j<NCB; j++)
      b[i][j]= (i*j)+1;
  #pragma omp for num_threads(thread_count) schedule(static, chunk)
  for (i=0; i<NRA; i++)
    for (j=0; j<NCB; j++)
      c[i][j]= 0;

  /*** Do matrix multiply sharing iterations on outer loop ***/
  /*** Display who does which iterations for demonstration purposes ***/
  printf("Thread %d starting matrix multiply...\n",tid);
  #pragma omp for schedule (static, chunk)
  for (i=0; i<NRA; i++)    
    {
    printf("Thread=%d did row=%d\n",tid,i);
    for(j=0; j<NCB; j++)       
      for (k=0; k<NCA; k++)
        c[i][j] += a[i][k] * b[k][j];
    }
}   /*** End of parallel region ***/
double time = omp_get_wtime()-start_time;
printf("El tiempo de ejecucion fue: %f\n",time);
/*** Print results ***/
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