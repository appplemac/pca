#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
   short rg;
   char b;
} Tpixel;

#define ROWS 5000
#define COLUMNS 20000

Tpixel buffer[ROWS][COLUMNS];

void rgb_verd()
{
  unsigned int i,j;

  for ( i=0 ; i<ROWS; i++)
  {
    for ( j=0 ; j<COLUMNS; j++)
    {
       buffer[i][j].rg = 0x01;
       buffer[i][j].b = 0;
    }
  }
}

int main(int argc, char *argv[])
{
  rgb_verd();

  write(1, buffer, sizeof(buffer));

  return(0);
}

