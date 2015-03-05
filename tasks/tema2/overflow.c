#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv) {
  if (argc < 3) {
    printf("Usage: overflow int1 int2\n");
  }

  unsigned first = atoi(argv[1]);
  unsigned second = atoi(argv[2]);

  unsigned sum = first + second;

  if (sum < first || sum < second)
    printf("Overflow.\n");
  else printf("No overflow.\n");
  return 0;
}
