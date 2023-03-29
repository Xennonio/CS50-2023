#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool keytest(char s[]);

int main(int n, string k[])
{
  if(n != 2 || !keytest(k[1]))
  {
    printf("Usage: ./substitution key\n");

    return 1;
  }
  else
  {
    if(strlen(k[1]) != 26)
    {
      printf("The key must contain 26 characters.\n");

      return 1;
    }
    else
    {
      string text = get_string("simple text: ");

      for(int i = 0, l = strlen(text); i < l; i++)
      {
        int m = text[i];

        if(text[i] >= 'a' && text[i] <= 'z')
        {
          text[i] = tolower(k[1][m - 97]);
        }

        if(text[i] >= 'A' && text[i] <= 'Z')
        {
          text[i] = toupper(k[1][m - 65]);
        }
      }

      printf("ciphertext: %s\n", text);
    }
  }

  printf("teste");
}

bool keytest(char s[])
{
  for(int k = 0; s[k] != 0; k++)
  {
    for(int j = 1; s[j + k] != 0; j++)
    {
      if(s[k] == s[j + k] || !((s[k] >= 'a' && s[k] <= 'z') || (s[k] >= 'A' && s[k] <= 'Z')))
      {
        return false;
      }
    }
  }
  return true;
}