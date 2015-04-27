#define N 100000
#define M 1000

typedef struct {
  int vel[M];
  int acc[M];
} point;

point p[N];

void clear1(point * p,int n) {
  int i,j;
  for (i=0; i<n; i++) {
    for (j=0; j<M; j++)
      p[i].vel[j]=0;
    for (j=0; j<M; j++)
      p[i].acc[j]=0;
  }
}

void clear2(point * p,int n) {
  int i,j;
  for (i=0; i<n; i++) {
    for (j=0; j<M; j++) {
      p[i].vel[j]=0;
      p[i].acc[j]=0;
    }
  }
}

void clear3(point * p,int n) {
  int i,j;
  for (j=0; j<M; j++) {
    for (i=0; i<n; i++)
      p[i].vel[j]=0;
    for (i=0; i<n; i++)
      p[i].acc[j]=0;
  }
}

int main() {
  clear3(p,N);
}
