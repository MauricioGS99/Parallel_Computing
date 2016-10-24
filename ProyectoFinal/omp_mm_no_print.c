#include <omp.h>
#include <stdio.h>
#include <stdlib.h>


#define NRA 10                 /* number of rows in matrix A */
#define NCA 10               /* number of columns in matrix A */
#define NCB 10                /* number of columns in matrix B */


int main (int argc, char *argv[]) 
{
int	tid, i, j, k, chunk;
double	a[NRA][NCA],           /* matrix A to be multiplied */
	      b[NCA][NCB],           /* matrix B to be multiplied */
	      c[NRA][NCB];           /* result matrix C */

chunk = 1;                    /* set loop iteration chunk size */

int nthreads=strtol(argv[1],NULL,10);

/*** Spawn a parallel region explicitly scoping all variables ***/

#pragma omp parallel num_threads(nthreads) shared(a,b,c,nthreads,chunk) private(tid,i,j,k)
 {
  tid = omp_get_thread_num();
  if (tid == 0)
    {
    nthreads = omp_get_num_threads();
    printf("Starting matrix multiple example with %d threads\n",nthreads);
    printf("Initializing matrices...\n");
    }
  /*** Initialize matrices ***/
  #pragma omp for schedule (static, chunk) 
  for (i=0; i<NRA; i++)
    for (j=0; j<NCA; j++)
      a[i][j]= rand() % (10 + 1 - 0) + 0;
  #pragma omp for schedule (static, chunk)
  for (i=0; i<NCA; i++)
    for (j=0; j<NCB; j++)
      b[i][j]= rand() % (10 + 1 - 0) + 0;
  #pragma omp for schedule (static, chunk)
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