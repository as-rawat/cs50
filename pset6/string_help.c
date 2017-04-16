#include <stdio.h>
#include <string.h>
int main()
{
  char x[5];
  scanf("%s", x);
  char l[] = "lol";
  if(!strcmp(x, l))
  {
    printf("Yeahh\n");
  }
}
