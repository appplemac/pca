#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char ** argv) {
  if (argc < 3) {
    printf("Usage: overflow int1 int2\n");
  }

  unsigned first = atoi(argv[1]);
  unsigned second = atoi(argv[2]);

  if (log2(first) < 32 && log2(second) < 32)
    printf("No overflow here.\n");
  else printf("Overflow will be produced.\n");
  return 0;
}
