#ifndef __CLIST_H__
#define __CLIST_H__
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#define container_of(ptr, type, member) (type*)( (char*)(ptr) - offsetof(type, member))

typedef struct intrusive_node intrusive_node_t; 
typedef struct intrusive_list intrusive_list_t;
typedef struct position_node position_node_t;

struct intrusive_node {
  struct intrusive_node* next;
  struct intrusive_node* prev;
};

struct intrusive_list {
  struct intrusive_node* head;
};

void init_list(intrusive_list_t* l);
void add_node(intrusive_list_t* l, intrusive_node_t* node);
void remove_node(intrusive_list_t* l, intrusive_node_t* node);

int get_length(intrusive_list_t* l);

#endif