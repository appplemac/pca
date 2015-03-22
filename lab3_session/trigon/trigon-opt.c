#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define N 6000
#define PUNTS 1000

double sin_arr[PUNTS], cos_arr[PUNTS];

void precalc() {
  int i;
  double d = 0.0;
  double inc = 2*M_PI/PUNTS;
  for (i = 0; i < PUNTS; ++i) {
    sin_arr[i] = sin(d);
    cos_arr[i] = cos(d);
    d += inc;
  }
}

int main(int argc, char *argv[])
{
	unsigned int i, r, j, n;
	double x, y;

  double buff[2*PUNTS];
  precalc();

	if (argc == 1) n = N; else n = atoi(argv[1]);

	srand(0);
	for (i=0; i<n; i++)
	{
		r = rand();
		for (j=0; j<PUNTS; j++)
		{
      buff[2*j] = r*cos_arr[j];
      buff[2*j+1] = r*sin_arr[j];
		}
    write(1, buff, sizeof(x) * 2 * PUNTS);
	}
	return 0;
}
