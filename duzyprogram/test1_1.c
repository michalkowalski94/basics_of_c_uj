#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int ReadNumber(void)
{
  int number;
  printf("Podaj liczbe rzeczywista, staloprzecinkowa:\n");
  scanf("%d", &number);
  return number;
}

int Condition(int number)
{
  for(int i = 2; i < number; i++)
  {
    if(number%i == 0)
    {
      return 1;
    }
  }
  return 0;
}

int main(void)
{
  int number = ReadNumber();
  if(Condition(number) == 0)
  {
    printf("Liczba jest liczba pierwsza\n");
  }
  else
  {
    printf("Liczba nie jest liczba pierwsza\n");
  }
  return 0;
}
