#include <stdio.h>

int tamanho;

int main()
{
  do
  {
    printf("Tamanho: ");
    scanf("%d", &tamanho);
  } while(tamanho <= 0 || tamanho > 8);
  for(int i = 0; i < tamanho; i++)
  {
    for(int j = 1; j <= tamanho; j++){
      if(j < tamanho - i) printf(" ");
      else printf("#");
      if(j == tamanho) printf("\n");
    }
  }
}