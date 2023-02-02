#include <stdio.h>
#include <cs50.h>

int main()
{
  int a, b, y = 0;

  do a = get_int("Valor inicial: ");
  while (a < 9);

  do b = get_int("Valor final: ");
  while (b < a);

  if(a != b)
  {
    do
    {
      a += a/3 - a/4;
      y += 1;
    } while (a < b);
    printf("Years: %d\n", y);
  } else printf("Years: %d\n", y);
}