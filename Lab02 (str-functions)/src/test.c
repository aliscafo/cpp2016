#include "../include/test_str.h"

int main ()
{
  int i = 0;

  for (i = 0; i < NUMT; i++)
  {
    if (test_strcpy()) 
      printf("OK strcpy!\n");
    else
    {
      printf("Wrong strcpy!\n");
      break;
    }
  }
  printf("\n");

  for (i = 0; i < NUMT; i++)
  {
    if (test_strcat()) 
      printf("OK strcat!\n");
    else
    {
      printf("Wrong strcat!\n");
      break;
    }
  }
  printf("\n");

  for (i = 0; i < NUMT; i++)
  {
    if (test_strcmp()) 
      printf("OK strcmp!\n");
    else
    {
      printf("Wrong strcmp!\n");
      break;
    }
  }
  printf("\n");

  for (i = 0; i < NUMT; i++)
  {
    if (test_strlen()) 
      printf("OK strlen!\n");
    else
    {
      printf("Wrong strlen!\n");
      break;
    }
  }
  printf("\n");

  return 0;
}