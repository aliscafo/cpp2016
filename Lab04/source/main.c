#include "../include/merge_sort.h"
#include "../include/ms_cli.h" 
#include <stdlib.h>
#define MAXN (int)1e3

int main(int argc, char* argv[])
{
  int n = argc - 2, i;
  
  switch(*argv[1]) {
    
    case 'c': {
      char* array = (char*)malloc(sizeof(char) * n);

      for (i = 0; i < n; i++)
        *(array + i) = argv[2 + i][0];

      mergesort(array, n, 1, compare_char);

      for (i = 0; i < n; i++)
        printf("%c ", *(array + i));
      printf("\n");
      
      free(array);

      break;
    }
    case 'i': {
      int* array = (int*)malloc(sizeof(int) * n);

      for (i = 0; i < n; i++) {
        int number = 0, minus = 1, j = 0;
        
        if (argv[2 + i][0] == '-')
          minus = -1, j++;

        while (argv[2 + i][j])
          number = number * 10 + (argv[2 + i][j] - '0'), j++;

        number *= minus;

        array[i] = number;
      }
      
      mergesort(array, n, 4, compare_int);

      for (i = 0; i < n; i++)
        printf("%i ", array[i]);
      printf("\n");
      
      free(array);

      break;
    }
    case 's': {
      char** array = (char**)malloc(sizeof(char*) * n);
      char* strings = (char*)malloc(sizeof(char) * MAXN * n);

      for (i = 0; i < n; i++)
        array[i] = strings + i * MAXN;

      for (i = 0; i < n; i++) {
        char* it = array[i];
        int j = 0;

        while (argv[2 + i][j])
          *it = argv[2 + i][j], it++, j++;
        *it = 0;
      }

      mergesort(*array, n, MAXN, compare_str);

      for (i = 0; i < n; i++)
        printf("%s ", array[i]);
      printf("\n");
      
      free(strings);
      free(array);
          
      break;
    }
    default:
      printf("Wrong name of type!\n");
  }
   

  return 0;
}
