#include <stdio.h>
#include <string.h>
#include <math.h>

int main(int argc, char* argv[])
{
  char* temp = "stdio %s %i";
  char x[50];
  printf(temp, argv[1], argc);
  sprintf(x, temp, argv[1], argc);
  printf("\nstrlen(temp) = %d\nstrlen(x) = %d\n", strlen(temp) + (int)log10(argc) + 1 - 2 + strlen(argv[1]) - 2 + 1,strlen(x) + 1);
}
