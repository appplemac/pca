#include <stdio.h>
#include <stdlib.h>
#define N  1024*1024

int main() {
  unsigned long *B = (unsigned long *)malloc(1023);
  unsigned long * A = (unsigned long *)malloc(N*sizeof(int));
  unsigned long *pAux;
  int i;
  for (i=0; i<N; ++i) {
    if ((unsigned long)(&A[i])%16 == 0) {
      pAux = &A[i];
      break;
    }
  }
  printf("B = \t%lx\n", (unsigned long)B);
  printf("A = \t%lx\n", (unsigned long)A);
  printf("pAux = \t%lx\n", (unsigned long)pAux);
  if ((unsigned long)pAux % 16 == 0) printf("Dividable by 16\n");
  free(A);
}
