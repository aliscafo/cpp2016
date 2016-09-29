#include "../include/clist.h"


void init_list(intrusive_list_t* l) {
  l->head = NULL;
}


int get_length(intrusive_list_t* l) {
    int n = 1;
    intrusive_node_t* t = l->head;
    
    if (l->head == NULL)
        return 0;

    while (t->next != l->head) {
        t = t->next;
        n++;
    }

    return n;
}


void add_node(intrusive_list_t* l, intrusive_node_t* node) {
    if (l->head == NULL) {
        node->next = node;
        node->prev = node;
        l->head = node;
    }
    else {
        node->prev = l->head;
        node->next = l->head->next;
        l->head->next->prev = node;
        l->head->next = node;
    }
}


void remove_node(intrusive_list_t* l, intrusive_node_t* node) {
    if (get_length(l) == 1)
        l->head = NULL;
    else if (node == l->head) {
        l->head->prev->next = l->head->next;
        l->head->next->prev = l->head->prev;
        l->head = l->head->prev;      
    }
    else {
      node->next->prev = node->prev;
      node->prev->next = node->next;  
    }
}


