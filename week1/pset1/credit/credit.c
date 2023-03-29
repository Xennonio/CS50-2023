#include <stdio.h>
#include <cs50.h>
#include <math.h>

long int cardtest = 0;

/*
AMEX - 15 digits, starts w/ 34 or 37
MASTERCARD - 16 digits, starts w/ 51, 52, 53, 54 or 55
VISA - 13 or 16 digits, starts w/ 4

input: int n := cardnumber
v[k] = [n₁, n₂, ..., nₖ]
v[j] = digroot(v[j])
  digrootₖ(n) = n - (k - 1)⌊(n - 1)/(k - 1)⌋
cardtest : (2*(sum v[2*i]) + (sum v[2*i + 1])) % 10 ≡ 0 (mod 10)
*/

bool amex(long int n, int k)
{
  if(k == 15 && (floor(n/pow(10,13)) == 34 || floor(n/pow(10,13)) == 37) && (cardtest % 10) == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool macard(long int n, int k)
{
  if(k == 16 && (floor(n/pow(10,14)) == 51 ||
                 floor(n/pow(10,14)) == 52 ||
                 floor(n/pow(10,14)) == 53 ||
                 floor(n/pow(10,14)) == 54 ||
                 floor(n/pow(10,14)) == 55) && (cardtest % 10) == 0)
    return true;
  else return false;
}

bool visa(long int n, int k)
{
  if((k == 13 || k == 16) && (floor(n/pow(10,12)) == 4 || floor(n/pow(10,15)) == 4) && (cardtest % 10) == 0)
    return true;
  else return false;
}

int main()
{
  long int cnumb;
  cnumb = get_long("Número: ");

  int k = round(log10(cnumb)) + 1;
  long int v[k];

  for(int i = 1; i <= k; i++)
  {
    v[i - 1] = ((cnumb % (long int)pow(10, i)) - (cnumb % (long int)pow(10, i - 1)))/pow(10, i - 1);
    if((i - 1) % 2 == 1)
      v[i - 1] = (2*v[i - 1]) - 9*round((2*v[i - 1] - 1)/9);
  }

  for(int j = 0; j < round(k/2); j++)
  {
    cardtest += v[2*j + 1] + v[2*j];
  }

  if(amex(cnumb, k - 1))
    printf("AMEX\n");
  else if(macard(cnumb, k - 1))
    printf("MASTERCARD\n");
  else if(visa(cnumb, k - 1))
    printf("VISA\n");
  else printf("INVALID\n");
}