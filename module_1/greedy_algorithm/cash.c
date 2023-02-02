#include <stdio.h>
#include <math.h>
#include <cs50.h>

double cash;

int main()
{
  do cash = get_float("Troca devida: ");
  while(cash < 0);
  int cents = round(100*(cash)),
  c25 = round(cents/25),
  c10 = round((cents - 25*c25)/10),
  c5 = round((cents - 25*c25 - 10*c10)/5),
  c1 = cents - 25*c25 - 10*c10 - 5*c5;
  printf("%d\n", c25 + c10 + c5 + c1);
}