#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv) {
  if (argc < 3) {
    printf("Usage: overflow int1 int2\n");
  }

  int first = atoi(argv[1]);
  int second = atoi(argv[2]);

  int sum = first + second;

  if (sum-first == second && sum-second==first)
    printf("Works.\n");
  else printf("Does not work.\n");
  return 0;
}
