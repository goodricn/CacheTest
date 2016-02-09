nclude <stdio.h>      /* printf */
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h>       /* sqrt */

//#define CPU_MHZ 2.8 * 1024.0 * 1024.0; /* e.g., 2.8 GHz */
#define MINBYTES (1 << 10)  /* Working set size ranges from 1 KB */
#define MAXBYTES (1 << 23)  /* ... up to 8 MB */
#define MAXSTRIDE 16        /* Strides range from 1 to 16 */
#define MAXELEMS MAXBYTES/sizeof(int)

int data[MAXELEMS];


/* The test function */
void test(int elems, int stride) 
{    
  int i, result = 0;
 volatile int sink;
    for (i = 0; i < elems; i += stride)
        result += data[i];
    sink = result; /* So compiler doesn't optimize away the loop */
}

/* Run test(elems, stride) and return read throughput (MB/s) */
double run(int size, int stride)
{   clock_t start_cycles, end_cycles, diff;
    int elems = size / sizeof(int); 
    test(elems, stride);                     /* warm up the cache */    
    start_cycles = clock();  /* Read CPU cycle counter */
    test(elems,stride);
    end_cycles = clock();
    diff = end_cycles - start_cycles;
    //JR - I added this calculation of time
    // (the original used something different).
    // is it accurate? does it work?
    return (size/stride)/ ((double)diff/CLOCKS_PER_SEC); 
}

void init_data(int *data, int size)
{
  int i;
  for (i = 0; i < size; i++)
    {
      data[i] = 1;
    }
}

int main() 
{    
  int size;
  int stride;
  init_data(data, MAXELEMS); /* Initialize each element in data to 1 */
  for (size = MAXBYTES; size >= MINBYTES; size >>= 1)
    { 
      for (stride = 1; stride <= MAXSTRIDE; stride++){
	printf("%d",stride);
	printf(",");	
	printf("%d",size);
	printf(",");
	printf("%.1f", run(size, stride));
	printf("\n");	
	}
//      printf("\n");
    }
  exit(0);
 }

