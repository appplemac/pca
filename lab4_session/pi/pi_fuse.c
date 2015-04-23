#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int N, N4;
char a[10240], b[10240], c[10240];
char string[100];

uint16_t r_239[2390];
unsigned char r_25[250];

unsigned char q_239[2390];
unsigned char q_25[250];

void precalc() {
  int i;
  for (i = 0; i < 2390; ++i) {
    q_239[i] = i / 239;
    r_239[i] = (i-(i / 239)*239)*10;
  }
  for (i = 0; i < 250; ++i) {
    r_25[i] = (i-(i / 25)*25)*10;
    q_25[i] = i / 25;
  }
}

#define DIV239_OP(u,r,x,k,q,q_239,r_239) \
  ({ \
    u = r + x[k]; \
    q = q_239[u]; \
    r = r_239[u]; \
    x[k] = q; \
  })

#define DIV239_4OP(u,r,x,k,q,q_239,r_239) \
  ({ \
    DIV239_OP(u,r,x,k,q,q_239,r_239); \
    DIV239_OP(u,r,x,k+1,q,q_239,r_239); \
    DIV239_OP(u,r,x,k+2,q,q_239,r_239); \
    DIV239_OP(u,r,x,k+3,q,q_239,r_239); \
  })

void DIV239( char *x )
{
  int j, k;
  unsigned q, r, u;

  r = 0;
  for( k = 0; k <= N4; k+=4 )
  {
    DIV239_4OP(u,r,x,k,q,q_239,r_239);
  }
}

#define DIV25_OP(u,r,x,k,q,q_25,r_25) \
  ({ \
    u = r + x[k]; \
    q = q_25[u]; \
    r = r_25[u]; \
    x[k] = q; \
   })

#define DIV25_4OP(u,r,x,k,q,q_25,r_25) \
  ({ \
    DIV25_OP(u,r,x,k,q,q_25,r_25); \
    DIV25_OP(u,r,x,k+1,q,q_25,r_25); \
    DIV25_OP(u,r,x,k+2,q,q_25,r_25); \
    DIV25_OP(u,r,x,k+3,q,q_25,r_25); \
   })

void DIV25( char *x )
{
  int j, k;
  unsigned q, r, u;
  long v;

  r = 0;
  for( k = 0; k <= N4; k+=4 )
  {
    DIV25_4OP(u,r,x,k,q,q_25,r_25);
  }
}

#define DIVIDE_OP(u,r,x,k,q,n) \
  ({ \
    u = r * 10 + x[k]; \
    q = u / n; \
    r = u - q * n; \
    x[k] = q; \
  })

#define DIVIDE_4OP(u,r,x,k,q,n) \
  ({ \
    DIVIDE_OP(u,r,x,k,q,n); \
    DIVIDE_OP(u,r,x,k+1,q,n); \
    DIVIDE_OP(u,r,x,k+2,q,n); \
    DIVIDE_OP(u,r,x,k+3,q,n); \
   })

void DIVIDE( char *x, int n )
{
  int j, k;
  unsigned q, r, u;
  long v;

  r = 0;
  for( k = 0; k <= N4; k+=4 )
  {
    DIVIDE_4OP(u,r,x,k,q,n);
  }
}

#define LONGDIV_OP(u,r,x,k,q,n) \
  ({ \
    u = r * 10 + x[k]; \
    q = u / n; \
    r = u - q * n; \
    x[k] = q; \
  })

#define LONGDIV_4OP(u,r,x,k,q,n) \
  ({ \
    LONGDIV_OP(u,r,x,k,q,n); \
    LONGDIV_OP(u,r,x,k+1,q,n); \
    LONGDIV_OP(u,r,x,k+2,q,n); \
    LONGDIV_OP(u,r,x,k+3,q,n); \
   })

void LONGDIV( char *x, int n )
{
  int j, k;
  unsigned q, r, u;
  long v;

  r = 0;
  for( k = 0; k <= N4; k+=4 )
  {
    LONGDIV_4OP(u,r,x,k,q,n);
  }
}

#define MULTIPLY_OP(q,n,x,k,r) \
  ({ \
    q = n * x[k] + r; \
    r = q / 10; \
    x[k] = q - r * 10; \
  })

#define MULTIPLY_4OP(q,n,x,k,r) \
  ({ \
    MULTIPLY_OP(q,n,x,k,r); \
    MULTIPLY_OP(q,n,x,k-1,r); \
    MULTIPLY_OP(q,n,x,k-2,r); \
    MULTIPLY_OP(q,n,x,k-3,r); \
   })

void MULTIPLY( char *x, int n )
{
  int j, k;
  unsigned q, r, u;
  long v;
  r = 0;
  for( k = N4; k >= 0; k-=4 )
  {
    MULTIPLY_4OP(q,n,x,k,r);
  }
}

void SET( char *x, int n )
{
  memset( x, 0, N4 + 1 );
  x[0] = n;
}


void SUBTRACT( char *x, char *y, char *z )
{
  int j, k;
  unsigned q, r, u;
  long v;
  for( k = N4; k >= 0; k-- )
  {
    if( (x[k] = y[k] - z[k]) < 0 )
    {
      x[k] += 10;
      z[k-1]++;
    }
  }
}

void SUBTRACT_FUSE( char *x1, char *x2, char *y, char *z1, char *z2 )
{
  int j, k;
  unsigned q, r, u;
  long v;
  for( k = N4; k >= 0; k-- )
  {
    if( (x1[k] = y[k] - z1[k]) < 0 )
    {
      x1[k] += 10;
      z1[k-1]++;
    }
    if( (x2[k] = y[k] - z2[k]) < 0 )
    {
      x2[k] += 10;
      z2[k-1]++;
    }
  }
}

void calculate( void );
void progress( void );
void epilog( void );


int main( int argc, char *argv[] )
{
  N = 10000;
  if (argc>1) {
    N = atoi(argv[1]);
  }

  setbuf(stdout, NULL);

  precalc();
  calculate();

  epilog();

  return 0;
}

#define PROGRESS printf(".")

void calculate( void )
{
  int j;

  N4 = N + 4;

  SET( a, 0 );
  SET( b, 0 );

  for( j = 2 * N4 + 1; j >= 3; j -= 2 )
  {
    SET( c, 1 );
    LONGDIV( c, j );

    SUBTRACT_FUSE( a, b, c, a, b );
    DIV25( a );

    DIV239( b );
    DIV239( b );

    PROGRESS;
  }

  SET( c, 1 );

  SUBTRACT( a, c, a );
  DIVIDE( a, 5 );

  SUBTRACT( b, c, b );
  DIVIDE( b, 239 );

  MULTIPLY( a, 4 );
  SUBTRACT( a, a, b );
  MULTIPLY( a, 4 );

  PROGRESS;
}

/*

 N = 10000
 A = 0
 B = 0
 J = 2 * (N + 4) + 1
 FOR J = J TO 3 STEP -2
   A = (1 / J - A) / 5 ^ 2
   B = (1 / J - B) / 239 ^ 2
 NEXT J
 A = (1 - A) / 5
 B = (1 - B) / 239
 PI = (A * 4 - B) * 4

*/

void epilog( void )
{
    int j;

    {
        fprintf( stdout, " \n3.");
        for( j = 1; j <= N; j++ )
        {
            fprintf( stdout, "%d", a[j]);
            if( j % 5  == 0 )
                if( j % 50 == 0 )
                    if( j % 250  == 0 )
                        fprintf( stdout, "    <%d>\n\n   ", j );
                    else
                        fprintf( stdout, "\n   " );
                else
                    fprintf( stdout, " " );
        }
    }
}

