#include <stdio.h>
#include <cs50.h>

int main()
{
  int start_size, end_size, i = 0;

  do start_size = get_int("Start Size: ");
  while (start_size < 9);

  do end_size = get_int("End Size: ");
  while (end_size < start_size);

  if(start_size != end_size)
  {
    do
    {
      start_size += start_size/3 - start_size/4;
      i += 1;
    }
    while (start_size < end_size);
    
    printf("Years: %d\n", i);
  }
  else
  {
    printf("Years: %d\n", i);
  }
}