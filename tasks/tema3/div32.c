#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv) {
  if (argc < 2) {
    printf("Usage: div32 num\n");
    return 1;
  }

  int num = atoi(argv[1]);
  int mask = num >> 31; // sign extension mask
  mask = mask & 31;
  num += mask;
  num = num >> 5;

  printf("Result: %d\n", num);
  return 0;
}
