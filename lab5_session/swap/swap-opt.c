#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
 
void panic(char *miss)
{
        if (errno != 0) perror(miss);
        else fprintf(stderr, "%s\n", miss);
 
        exit(1);
}
 
int main(int argc, char *argv[])
{
    char * string = (char*)malloc(128*sizeof(char));
    char temp;
    int count = 0;
 
    while ((count=read(0, string, 128)) && count > 0)
    {
      for (int i=0; i<count; i+=2) {
        temp = string[i+1];
        string[i+1] = string[i];
        string[i]=temp;
      }
      write(1, string, strlen(string));
    }
 
    if (count<0) panic("read");
 
    return 0;
}
