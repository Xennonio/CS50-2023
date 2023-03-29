// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>

bool valid(string password);

int main(void)
{
  string password = get_string("Enter your password: ");
  if (valid(password))
  {
      printf("Your password is valid!\n");
  }
  else
  {
      printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
  }
}

bool valid(string password)
{
  bool password_check[4] = {false, false, false, false};
  int lenght = strlen(password);

  for(int i = 0; i < lenght; i++)
  {
    if(islower(password[i]))
    {
      password_check[0] = true;
    }

    if(isupper(password[i]))
    {
      password_check[1] = true;
    }

    if(isdigit(password[i]))
    {
      password_check[2] = true;
    }

    if(ispunct(password[i]))
    {
      password_check[3] = true;
    }
  }

  if(password_check[0] && password_check[1] && password_check[2] && password_check[3])
  {
    return true;
  }
  else
  {
    return false;
  }
}
