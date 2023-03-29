#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

void wlscount(string t);
double w = 1, l = 0, s = 0,
L, S;

int main()
{
  string text;
  text = get_string("Text: ");

  wlscount(text);

  L = 100*l/w;
  S = 100*s/w;
  int index = round(0.0588*L - 0.296*S - 15.8);

  if(index >= 16)
  {
    printf("Grade 16+\n");
  }
  else
  {
    if(index < 1)
    {
      printf("Before Grade 1\n");
    }
    else
    {
      printf("Grade %d\n", index);
    }
  }
}

void wlscount(string t)
{
  for(int i = 0, n = strlen(t); i < n; i++)
  {
    if(t[i] == ' ')
    {
      w += 1;
    }

    if((t[i] >= 'a' && t[i] <= 'z') || (t[i] >= 'A' && t[i] <= 'Z'))
    {
      l += 1;
    }

    if(t[i] == '.' || t[i] == '!' || t[i] == '?')
    {
      s += 1;
    }
  }
}