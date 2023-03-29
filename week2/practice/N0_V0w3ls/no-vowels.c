// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
  int lenght = strlen(argv[1]);

  for(int i = 0; i < lenght; i++)
  {
    if(argv[1][i] == 'a')
    {
      argv[1][i] = '6';
    }

    if(argv[1][i] == 'e')
    {
      argv[1][i] = '3';
    }

    if(argv[1][i] == 'i')
    {
      argv[1][i] = '1';
    }

    if(argv[1][i] == 'o')
    {
      argv[1][i] = '0';
    }
  }

  printf("%s\n", argv[1]);
}
