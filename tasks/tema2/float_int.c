#include <stdio.h>
#include <float.h>

int main(int argc, char ** argv) {
  if (DBL_MIN * DBL_MIN >= 0.0)
    printf("Right!\n");
  else printf("Wrong.\n");
  return 0;
}
