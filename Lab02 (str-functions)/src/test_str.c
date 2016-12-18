#include "../include/str.h"
#define MAXN 100
#include <stdlib.h>

int gen_string(char * str)
{
  int n = rand() % (MAXN / 3);
  int i;

  for (i = 0; i < n; i++)
    *str++ = rand() % 26 + 'a';

  *str = 0;

  return n;
}

int test_strcpy() 
{
  char s1[MAXN], s2[MAXN];
  gen_string(s1);
  gen_string(s2);
  
  strcpy(s1, s2);

  int i = 0;

  while (s1[i] && s2[i] && s1[i] == s2[i])
    i++;

  if (s1[i] == s2[i] && !s1[i])
    return 1;
  else
    return 0;
}


int test_strcat() 
{
  char s1[MAXN], s2[MAXN];
  int n = gen_string(s1), m = gen_string(s2);

  strcat(s1, s2);

  int i = 0;

  while (s1[n + i] && s2[i] && s1[n + i] == s2[i])
    i++;

  if (s1[n + i] == s2[i] && !s1[n + i])
    return 1;
  else
    return 0;
}


int test_strcmp()
{
  char s1[MAXN], s2[MAXN];
  int n = gen_string(s1), m = gen_string(s2);

  int ans = strcmp(s1, s2);

  int i = 0;

  while (s1[i] && s2[i] && s1[i] == s2[i])
    i++;

  if (s1[i] == s2[i] && ans == 0 || s1[i] > s2[i] && ans == 1 || s1[i] < s2[i] && ans == -1)
    return 1;
  else
    return 0;
}


int test_strlen()
{
  char s[MAXN];
  int n = gen_string(s);

  int s_len = strlen(s);

  if (n == s_len)
    return 1;
  else
    return 0;
}

