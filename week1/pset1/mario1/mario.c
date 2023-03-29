#include <stdio.h>

int height;

int main()
{
  do
  {
    printf("Height: ");
    scanf("%d", &height);
  }
  while(height <= 0 || height > 8);

  for(int i = 0; i < height; i++)
  {
    for(int j = 1; j <= height; j++)
    {
      if(j < height - i)
      {
        printf(" ");
      }
      else
      {
        printf("#");
      }

      if(j == height)
      {
        printf("\n");
      }
    }
  }
}