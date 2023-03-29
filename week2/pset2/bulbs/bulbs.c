#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);
int decimal_to_binary(char character, int index);

int main(void)
{
  string message = get_string("Message: ");

  int lenght = strlen(message);

  for(int i = 0; i < lenght; i++)
  {
    for(int j = 0; j < 8; j++)
    {
      print_bulb(decimal_to_binary((message[i]), j));
    }

    printf("\n");
  }
}

int decimal_to_binary(char character, int index)
{
  int ascii_dec = character;
  int ascii_bin[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  int i = 0;

  while(ascii_dec != 0)
  {
    if(ascii_dec % 2 == 0)
    {
      ascii_bin[7 - i] = 0;
      ascii_dec = ascii_dec/2;
      i++;
    }
    else
    {
      ascii_bin[7 - i] = 1;
      ascii_dec = (ascii_dec - 1)/2;
      i++;
    }
  }

  return ascii_bin[index];
}

void print_bulb(int bit)
{
  if (bit == 0)
  {
    // Dark emoji
    printf("\U000026AB");
  }
  else if (bit == 1)
  {
    // Light emoji
    printf("\U0001F7E1");
  }
}
