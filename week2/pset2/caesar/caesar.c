#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

bool isntnum(char n[]);

int main(int n, string k[])
{
  if(n != 2 || isntnum(k[1]))
  {
    printf("Usage: ./caesar key\n");

    return 1;
  }
  else{
    string text = get_string("plaintext: ");

    for(int i = 0, l = strlen(text); i < l; i++)
    {
      if(islower(text[i]))
      {
        text[i] = ((int)text[i] + atoi(k[1]) - 97) % 26 + 97;
      }

      if(isupper(text[i]))
      {
        text[i] = ((int)text[i] + atoi(k[1]) - 65) % 26 + 65;
      }
    }

    printf("ciphertext: %s\n", text);
  }
}

bool isntnum(char n[])
{
  int i = 0;
  // Verifies if n < 0
  if (n[0] == '-')
  {
    i = 1;
  }

  for (; n[i] != 0; i++)
  {
    // if (n[i] > '9' || n[i] < '0')
    if (!isdigit(n[i]))
    {
      return true;
    }
  }

  return false;
}