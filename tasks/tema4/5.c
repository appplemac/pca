#define K_FACTOR 5
#define OP(acc,v,offset) acc += v[i-offset] * v[i+1-offset]

int code_to_unroll(int n, int *v) {
  int iter = (n-2)%K_FACTOR;
  int rest = n-2 - iter;
  int acc = 0;
  int i;
  for ( i = iter; i > rest; i -= K_FACTOR ) {
    OP(acc,v,0);
    OP(acc,v,1);
    OP(acc,v,2);
    OP(acc,v,3);
    OP(acc,v,4);
  }
  for ( i = rest; i > 0 ; i-- ) {
    acc += v[i]*v[i+1];
  }
  return acc;
}
