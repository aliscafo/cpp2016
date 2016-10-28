#include <expat.h>
#include <stdio.h>
#include <string.h>
#include "../include/phonebook.h"
#define is_dig(c) '0' <= c && c <= '9'

void start_element(void *data, const char *element, const char **attribute) {
  if(!strcmp(element, "human")) {
    human_t human;
    int i = 0;

    for (; i < 10; i++) 
      memset(human.phones[i], 0, 21);

    char str[1 << 10];
    strcpy(str, attribute[1]);    

    strcpy(human.name, strtok(str, " "));
    strcpy(human.middle_name, strtok(NULL, " "));
    strcpy(human.family_name, strtok(NULL, " "));

    human.phones_size = 0;
    push_back_human((phonebook_t*)data, &human);    
  }   
}

void end_element(void *data, const char *element) {
  if (!strcmp(element, "phone")) {
    human_t *human = &(((phonebook_t *)data)->humans[((phonebook_t *)data)->size - 1]);
    human->phones_size++;     
  }
}

void handle_data(void *data, const char *content, int length) {
  if (is_dig(content[0])) {
    human_t *human = &(((phonebook_t *)data)->humans[((phonebook_t *)data)->size - 1]); 
    strncat(human->phones[human->phones_size], content, length);   
  }
}

int load_phonebook_xml(const char *filename, phonebook_t *book) {
  char buff[BUFFER_SIZE];

  FILE *fp;
  fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Failed to open file\n");
    return 1;
  }

  XML_Parser parser = XML_ParserCreate(NULL);
  XML_SetUserData(parser, book); 
  XML_SetElementHandler(parser, start_element, end_element);
  XML_SetCharacterDataHandler(parser, handle_data);

  memset(buff, 0, BUFFER_SIZE);

  size_t len = 0;
  int done = 0;
  do {
    len = fread(buff, sizeof(char), BUFFER_SIZE, fp);
    done = len < BUFFER_SIZE;
     if (XML_Parse(parser, buff, len, done) == XML_STATUS_ERROR) {
        printf("Error: %s\n", XML_ErrorString(XML_GetErrorCode(parser)));
        return 2;
      }
  } while (!done);

  XML_ParserFree(parser);
  fclose(fp);
  qsort(book->humans, book->size, sizeof(human_t), cmp);
  return 0;
}

int save_phonebook_xml(const char *filename, phonebook_t *book) {
  FILE *fp = fopen(filename, "wt");
  if (fp == NULL) {
    printf("Failed to open file\n");
    return 1;
  }
  
  fprintf(fp,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
  fprintf(fp,"<phonebook>\n");
  
  int i, j;  

  for (i = 0; i < book->size; i++) {
    human_t* human = &book->humans[i];
    fprintf(fp, "    <human name=\"%s %s %s\">\n", human->name, human->middle_name, human->family_name);
    for (j = 0; j < human->phones_size; j++)
      fprintf(fp, "        <phone>%s</phone>\n", human->phones[j]);
    fprintf(fp, "    </human>\n");
  }

  fprintf(fp, "</phonebook>");

  fclose(fp);
  return 0;    
}

int main(int argc, char **argv) {
  int result;

  phonebook_t *book = malloc(sizeof(phonebook_t));

  book->humans = malloc(sizeof(human_t));
  book->size = 0;
  book->capacity = 1;

  result = load_phonebook_xml(argv[1], book);
  print_phonebook(book);

  gen_phonebook(book, 5);
  result = save_phonebook_xml(argv[2], book);
  
  clear_phonebook(book);   
  
  return 0;
}

