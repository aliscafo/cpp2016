#include <stdio.h>

char * strcpy(char * destination, const char * source)
{
  char *dest = destination;
  
  while (*source)
  {
    *dest = *source;
    dest++;
    source++;
  }

  *dest = 0;

  return destination; 
}

char * strcat(char * destination, const char * source)
{
  char *dest = destination;

  while (*dest)
    dest++;

  while (*source)
  {
    *dest = *source;
    dest++;
    source++;
  }

  *dest = 0;

  return destination;
}

int strcmp(const char * str1, const char * str2)
{
  while (*str1 && *str2 && *str1 == *str2)
  {
    str1++;
    str2++;
  }

  if (*str1 == *str2)
    return 0;
  else if (*str1 > *str2)
    return 1;
  else
    return -1;
}
                                 
size_t strlen(const char * str)
{
  int n = 0;

  while (*str++)
    n++;
  
  return n;
}

