#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int convert(string input, int n);
int *tmp_num;
int number = 0;

int main(void)
{
  string input = get_string("Enter a positive integer: ");
  int n = strlen(input);

  for(int i = 0; i < n; i++)
  {
    if(!isdigit(input[i]))
    {
      printf("Invalid Input!\n");
      return 1;
    }

    tmp_num = malloc(sizeof(int)*n);
    *(tmp_num + n) = '\0';
  }

  // Convert string to int
  printf("%i\n", convert(input, n));

  free(tmp_num);
}

int convert(string input, int n)
{
  int lenght = strlen(input);

  if(lenght == 0)
  {
    for(int i = 0; i < n; i++)
    {
      number += tmp_num[n - i - 1]*pow(10, i);
    }

    return number;
  }

  for(int i = 0; i < 10; i++)
  {
    if(input[lenght - 1] == 48 + i)
    {
      *(tmp_num + lenght - 1) = i;
      input[lenght - 1] = '\0';
      convert(input, n);
    }
  }

  return number;
}