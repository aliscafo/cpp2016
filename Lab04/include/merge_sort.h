#ifndef __MERGE_SORT_H__
#define __MERGE_SORT_H__

#include <stdio.h>

int mergesort (void* base, size_t num, size_t size, int (*compar)(const void*, const void*));
void merge(void* a, void* b, int a_num, int b_num, size_t size, int (*compar)(const void*, const void*));
void copy(void* dest, void* src, size_t size);

#endif