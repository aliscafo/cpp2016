#include <stdlib.h>
#include <stdio.h>


void copy(void* dest, void* src, size_t size) {
  int i = 0;
  for (; i < size; i++)
    *(char*)dest = *(char*)src, dest++, src++;
}


void merge(void* a, void* b, int a_num, int b_num, size_t size, int (*compar)(const void*, const void*)) {
  int i = 0, j = 0, it = 0;
  char* res = (char*)malloc(sizeof(char) * size * (a_num + b_num));    

  for (; i < a_num; i++) {
    while (j < b_num && (*compar)((char*)b + j * size, (char*)a + i * size) < 0) 
      copy((char*)(res + it * size), (char*)((char*)b + j * size), size), j++, it++;        
    copy((char*)(res + it * size), (char*)((char*)a + i * size), size), it++; 
  }

  while (j < b_num)
    copy((char*)(res + it * size), (char*)((char*)b + j * size), size), j++, it++;

  for (i = 0; i < a_num + b_num; i++)
    copy((char*)((char*)a + i * size), (char*)(res + i * size), size);

  free(res);
}


int mergesort (void* base, size_t num, size_t size, int (*compar)(const void*, const void*)) {
  int a_num = num / 2, b_num = num - num / 2;

  if (num <= 1)
    return 0;

  char* a = (char*)base;
  char* b = (char*)base + a_num * size;

  mergesort(a, a_num, size, compar);
  mergesort(b, b_num, size, compar);

  merge((char*)a, (char*)b, a_num, b_num, size, compar);

  return 0;
}

