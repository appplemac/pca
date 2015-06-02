#include <stdio.h>
#include <stdlib.h>
/*#include <malloc.h>*/
#include <emmintrin.h> 

#define N 4000000
/* #define DEBUG 0 */

float * rgb_r;
float * rgb_g;
float * rgb_b;
float * yuv_y;
float * yuv_u;
float * yuv_v;

typedef struct s_pixel_rgb {
	float r;
	float g;
	float b;
} t_pixel_rgb;

typedef struct s_pixel_yuv {
	float y;
	float u;
	float v;
} t_pixel_yuv;

#define CONV(rgb, yuv, i) \
{   yuv_y[i] = 0.299 * rgb_r[i] + 0.587 * rgb_g[i] + 0.114 * rgb_b[i]; \
    yuv_u[i] = -0.147 * rgb_r[i] - 0.289 * rgb_g[i] + 0.436 * rgb_b[i]; \
    yuv_v[i] = 0.615 * rgb_r[i] - 0.515 * rgb_g[i] - 0.100 * rgb_b[i]; \
}

void rgb_to_yuv(t_pixel_rgb *rgb, t_pixel_yuv *yuv, int len, int N_iter)
{
	int i,j;
  __m128 temp_r, temp_g, temp_b, temp, temp_op, temp_res;

     for (j=0; j<N_iter; j++)
	for (i=0; i<len; i+=4) {
    temp_r = _mm_load_ps((const float *)&rgb_r[i]);
    temp_g = _mm_load_ps((const float *)&rgb_g[i]);
    temp_b = _mm_load_ps((const float *)&rgb_b[i]);

    temp_op = _mm_set1_ps(0.299);
    temp_res = _mm_mul_ps(temp_r, temp_op);

    temp_op = _mm_set1_ps(0.587);
    temp = _mm_mul_ps(temp_g, temp_op);
    temp_res = _mm_add_ps(temp_res, temp);

    temp_op = _mm_set1_ps(0.114);
    temp = _mm_mul_ps(temp_b, temp_op);
    temp_res = _mm_add_ps(temp_res, temp);

    _mm_store_ps((float *)&yuv_y[i], temp_res);

    temp_r = _mm_load_ps((const float *)&rgb_r[i]);
    temp_g = _mm_load_ps((const float *)&rgb_g[i]);
    temp_b = _mm_load_ps((const float *)&rgb_b[i]);

    temp_op = _mm_set1_ps(-0.147);
    temp_res = _mm_mul_ps(temp_r, temp_op);

    temp_op = _mm_set1_ps(-0.289);
    temp = _mm_mul_ps(temp_g, temp_op);
    temp_res = _mm_add_ps(temp_res, temp);

    temp_op = _mm_set1_ps(0.436);
    temp = _mm_mul_ps(temp_b, temp_op);
    temp_res = _mm_add_ps(temp_res, temp);

    _mm_store_ps((float *)&yuv_u[i], temp_res);

    temp_r = _mm_load_ps((const float *)&rgb_r[i]);
    temp_g = _mm_load_ps((const float *)&rgb_g[i]);
    temp_b = _mm_load_ps((const float *)&rgb_b[i]);

    temp_op = _mm_set1_ps(0.615);
    temp_res = _mm_mul_ps(temp_r, temp_op);

    temp_op = _mm_set1_ps(-0.515);
    temp = _mm_mul_ps(temp_g, temp_op);
    temp_res = _mm_add_ps(temp_res, temp);

    temp_op = _mm_set1_ps(-0.100);
    temp = _mm_mul_ps(temp_b, temp_op);
    temp_res = _mm_add_ps(temp_res, temp);

    _mm_store_ps((float *)&yuv_v[i], temp_res);

    /*CONV(rgb, yuv, i);*/
    /*CONV(rgb, yuv, i+1);*/
    /*CONV(rgb, yuv, i+2);*/
    /*CONV(rgb, yuv, i+3);*/
		/*yuv[i].u = 0.492 * (rgb_b[i] - yuv[i].y);*/
		/*yuv[i].v = 0.877 * (rgb_r[i] - yuv[i].y);*/
	}
}

int main (int argc, char *argv[])
{
  t_pixel_rgb *rgb; t_pixel_yuv *yuv; // Vectores para malloc

  int i;
  int n=N; // tamanyo vectores
  int NIt=50; // Num.iters

  if (argc>1) NIt = atoi(argv[1]);
  if (argc>2) n = atoi(argv[2]);

  if (n>N) { printf("Maxima longitud vector: %d\n",N); exit(-1); }

  rgb_r = (float *)malloc(n * sizeof(float));
  rgb_g = (float *)malloc(n * sizeof(float));
  rgb_b = (float *)malloc(n * sizeof(float));

  yuv_y = (float *)malloc(n * sizeof(float));
  yuv_u = (float *)malloc(n * sizeof(float));
  yuv_v = (float *)malloc(n * sizeof(float));
  /*if (posix_memalign((void**)&rgb, 16, n*sizeof(t_pixel_rgb)) !=0) {*/
      /*fprintf(stderr, "No memory.\n");*/
      /*exit(-1);*/
  /*}*/
  /*if (posix_memalign((void**)&yuv, 16, n*sizeof(t_pixel_yuv)) !=0) {*/
      /*fprintf(stderr, "No memory.\n");*/
      /*exit(-1);*/
  /*}*/
 
  for (i=0;i<n;i++) {

     rgb_r[i]=(float) ((i<<26) ^ ((i + 340) << 22) ^ i ^ 0xf215fabc);
     rgb_g[i]=(float) (((i+450)<<27) ^ ((i + 567) <<20) ^ i ^ 0xb152e8ca);
     rgb_b[i]=(float) (((i+7823454) << 25) ^0xbad51cde);
  }

  rgb_to_yuv(rgb, yuv, n, NIt);

  write(1, yuv, n*sizeof(t_pixel_yuv));
  
  return(0);
}
