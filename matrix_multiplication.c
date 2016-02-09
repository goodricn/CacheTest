include <stdio.h>      /* printf */
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h>       /* sqrt */
#include <stdlib.h>



int** init(int size) 
{
  int** ret;
  ret = (int**) malloc(size*sizeof(int*));
  int i;
  for (i = 0; i < size; i++)
    {
      ret[i] = (int*) malloc(size*sizeof(int));
    }
  return ret;
}


void ijk0(int** a, int** b, int** c,int n){
        int sum;
        for (int i=0; i<n; i++) {
                for (int j=0; j<n; j++) {
                         sum = 0;
                 for (int k=0; k<n; k++)
                         sum += a[i][k] * b[k][j];
                 c[i][j] = sum;
                 }
        }
}

void kij0(int** a, int** b, int** c,int n){
        int sum, r;
	for (int k=0; k<n; k++) {
		 for (int i=0; i<n; i++) {
			 r = a[i][k];
		 for (int j=0; j<n; j++)
			 c[i][j] += r * b[k][j];
 		}
	}
}


int min(int a, int b)
{
  if (a<=b)
    {
      return a;
    }
  else
    {
      return b;
    }

}


void bmm(int n, int** a, int** b, int** c,int B){
	int jj,i,j,kk,k,sum;
	for(jj=0;jj<n;jj+=B){
		for(i=0;i<n;i++){
			for(j=jj;j<min(jj+B,n);j++){
				c[i][j]=0.0;
				for(kk=0;kk<n;kk+=B){
					for(i=0;i<n;i++){
						for(j=jj; j<min(jj+B,n);j++){
							sum=0.0;
							for(k=kk;k<min(kk+B,n);k++){
								sum+=a[i][k] * b[k][j];
							}
						c[i][j]+=sum;
						}
					}
				}
			}
		}
	}
}




float runB(int n, int** a, int** b, int** c,int size)
{
    clock_t start_cycles, end_cycles, diff;
    int elems = size / sizeof(int);

    start_cycles = clock();  /* Read CPU cycle counter */

    bmm(n,a,b,c,size);
    end_cycles = clock();
    diff = end_cycles - start_cycles;

    return ((float)diff/CLOCKS_PER_SEC);
}


float runkij(int** a, int** b, int** c,int size)
{
   clock_t start_cycles, end_cycles, diff;
    int elems = size / sizeof(int);

    start_cycles = clock();  /* Read CPU cycle counter */

    kij0(a,b,c,size);

    end_cycles = clock();
    diff = end_cycles - start_cycles;

    return ((float)diff/CLOCKS_PER_SEC);
}


float runijk(int** a, int** b, int** c,int size)
{
    clock_t start_cycles, end_cycles, diff;
    int elems = size / sizeof(int);

    start_cycles = clock();  /* Read CPU cycle counter */

    ijk0(a,b,c,size);

    end_cycles = clock();
    diff = end_cycles - start_cycles;

    return ((float)diff/CLOCKS_PER_SEC);
}


int main()
{
  for(int i=50;i<2500;i+=100){
/*
	int** a= init(i);
	int** b= init(i);
	int** c= init(i);
//	printf("ijk:");
	printf("%d",i);
	printf(",");
	printf("%.00000004f",runijk(a,b,c,i));
	printf("	");
//	printf("     kij:");
        printf("%d",i);
	printf(",");
        printf("%.00000004f",runkij(a,b,c,i));
	printf("\n");
   }*/
//   for(int B=4;B<1000;B+=100){
	int** a= init(i);
        int** b= init(i);
        int** c= init(i);
//	printf("Bmm:");
	printf("%d",i);
	printf(",");
       // printf("%d",B);
//	printf(",");
        printf("%.000004f",runB(i,a,b,c,i/10));
	printf("\n");
//	}
}
  exit(0);
 }


