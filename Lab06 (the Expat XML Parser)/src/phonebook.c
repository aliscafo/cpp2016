#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <expat.h>
#include "../include/phonebook.h"
#include "../include/names.h"

int cmp (const void* human1, const void* human2) {
  return strcmp(((human_t *)human1)->family_name, ((human_t *)human2)->family_name);
}

void push_back_human(phonebook_t *book, human_t *human) {
  if (book->size >= book->capacity) {
    book->capacity *= 2;
    book->humans = realloc(book->humans, book->capacity * sizeof(human_t));
  }
  book->humans[book->size++] = *human;
}

void print_phonebook(phonebook_t *book) {
  printf("%d\n", book->size);
  
  size_t i, j;

  for (i = 0; i < book->size; i++) {
    printf("name: %s\n", (book->humans[i]).name);
    printf("middle name: %s\n", (book->humans[i]).middle_name);
    printf("family name: %s\n", (book->humans[i]).family_name);
    for(j = 0; j < (book->humans[i]).phones_size; j++)
      printf("phone: %s\n", (book->humans[i]).phones[j]);
    printf("\n"); 
  }  
}

void clear_phonebook(phonebook_t *book) {
  free(book->humans);
  free(book);
}

void gen_phonebook(phonebook_t *book, size_t size) {
  free(book->humans);
  book->humans = (human_t*)malloc(sizeof(human_t));
  book->size = 0;
  book->capacity = 1;

  srand(time(NULL));  
  human_t human;
  size_t i, j, k;
  int len;

  for (i = 0; i < size; i++) {
    strcpy(human.name, kNames[rand() % NAMES_CNT]);
    strcpy(human.family_name, kFamilyNames[rand() % FAMILY_NAMES_CNT]);
    strcpy(human.middle_name, kMiddleNames[rand() % MIDDLE_NAMES_CNT]);
    
    human.phones_size = (rand() % 10) + 1;
    for (j = 0; j < human.phones_size; j++) {
      len = rand() % 20 + 1;
      
      for(k = 0; k < len; k++)
        human.phones[j][k] = '0' + (rand() % 9); 
      human.phones[j][k] = '\0'; 
    }
    push_back_human(book, &human);  
  }
}


