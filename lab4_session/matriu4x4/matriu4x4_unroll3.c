#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define N_ITER 10000000

void print_matriu(int C[][4])
{
   int i,j,k;

   for (i = 0; i < 4; i++) 
   {
     for (j = 0; j < 4; j++) 
     {
       printf("%d ", C[i][j]);
     }
     printf("\n");
   }
}

#define MATRIX_OP(A,B,C,i,j,k) \
  C[i][j] = C[i][j] + A[i][k] * B[k][j]

#define INNER1_OP(A,B,C,i,j) \
  MATRIX_OP(A,B,C,i,j,0); \
  MATRIX_OP(A,B,C,i,j,1); \
  MATRIX_OP(A,B,C,i,j,2); \
  MATRIX_OP(A,B,C,i,j,3)

#define INNER2_OP(A,B,C,i) \
  INNER1_OP(A,B,C,i,0); \
  INNER1_OP(A,B,C,i,1); \
  INNER1_OP(A,B,C,i,2); \
  INNER1_OP(A,B,C,i,3)

#define INNER3_OP(A,B,C) \
  INNER2_OP(A,B,C,0); \
  INNER2_OP(A,B,C,1); \
  INNER2_OP(A,B,C,2); \
  INNER2_OP(A,B,C,3)

int main(int argc, char *argv[])
{
    int A[4][4], B[4][4], C[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    unsigned int n_iter=N_ITER, i,j,k;

    for (i=0; i<4; i++) {
        for (j=0; j<4; j++) {
            A[i][j] = rand();
            B[i][j] = rand();
        }
    }

    if (argc > 1) {
      n_iter = atoi(argv[1]);
    }

    int iter;
    for (iter=0; iter<n_iter; iter++) {
      INNER3_OP(A,B,C);
    }

    print_matriu(C);
    return 0;
}
