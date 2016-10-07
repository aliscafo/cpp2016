#include <string.h>
#include <stdio.h>

int compare_char(const void* x, const void* y) {
  return (*(char*)x - *(char*)y);
}

int compare_int(const void* x, const void* y) {
  return (*(int*)x - *(int*)y);
}

int compare_str(const void* x, const void* y) {
  //printf("%d %d\n", strlen((char*)x), strlen((char*)y));
  //printf("%s %s\n", (char*)x, (char*)y);
  //printf("%d\n", strcmp((char*)x, (char*)y));
  return strcmp(*(char**)x, *(char**)y);    
}