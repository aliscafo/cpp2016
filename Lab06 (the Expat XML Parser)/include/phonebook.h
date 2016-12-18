#ifndef __PHONEBOOK_H__
#define __PHONEBOOK_H__

#include <stddef.h>
#define BUFFER_SIZE 100000

typedef struct human_s {
  char name[256];
  char middle_name[256];
  char family_name[256];
  char phones[10][21];
  int phones_size;
} human_t;

typedef struct phonebook_s {
  human_t *humans;
  size_t size;
  size_t capacity;
} phonebook_t;

int load_phonebook_xml(const char *filename, phonebook_t *book);
int save_phonebook_xml(const char *filename, phonebook_t *book);
void print_phonebook(phonebook_t *book);
void gen_phonebook(phonebook_t *book, size_t size);
void clear_phonebook(phonebook_t *book);
void push_back_human(phonebook_t *book, human_t *human);
int cmp (const void* human1, const void* human2);

#endif
