#include "../include/clist.h"
#include <string.h>          
#define check(xx, yy) pos->x == x && pos->y == y
#define MAXN 10

struct position_node {
  int x, y;
  struct intrusive_node node;
};

void remove_position(intrusive_list_t* l, int x, int y) {
  if (get_length(l) == 0) { return; }  
  
  intrusive_node_t* t = l->head->next;  
  position_node_t* pos;

  while (1) {
    pos = container_of(t, position_node_t, node);
    
    if (check(x, y)) {
      remove_node(l, t);
      free(pos);
    }
    
    if (l->head == NULL || t == l->head)
      break;

    t = t->next;
  }        
} 

void add_position(intrusive_list_t* l, int x, int y) {
  position_node_t* pos = (position_node_t*)malloc(sizeof(position_node_t));
  pos->x = x;
  pos->y = y;
  add_node(l, &(pos->node));
}

void show_all_positions(intrusive_list_t* l) {
  if (get_length(l) == 0) {
    printf("<empty line>\n");
    return;
  }

  intrusive_node_t* t = l->head->next;
  position_node_t* pos;

  while (1) {
    pos = container_of(t, position_node_t, node);
    
    printf("(%d %d) ", pos->x, pos->y);
    
    if (t == l->head)
      break;

    t = t->next;
  }
  
  printf("\n");
}

void remove_all_positions(intrusive_list_t* l) {
  if (get_length(l) == 0) { return; }

  intrusive_node_t* t = l->head->next;
  position_node_t* pos;

  while (1) {
    pos = container_of(t, position_node_t, node);
    
    remove_node(l, t);
    free(pos);

    if (l->head == NULL || t == l->head)
      break;        

    t = t->next;
  }
}

int main() {
  intrusive_list_t l;
  init_list(&l);    
  
  int flag = 1, id = 0, i = 0;
  char q[MAXN], c;
  char add[] = {'a', 'd', 'd', 0};
  char rm[] = {'r', 'm', 0};
  char print[] = {'p', 'r', 'i', 'n', 't', 0};
  char rma[] = {'r', 'm', 'a', 0};
  char len[] = {'l', 'e', 'n', 0};
  char ex[] = {'e', 'x', 'i', 't', 0};
  
  while (flag) {
    id = 0;

    while (scanf("%c", &c) == 1) {
      if (c == ' ' || c == '\n')
        break;
      q[id++] = c;
    }   
    q[id] = 0;

    if (strcmp(q, add) == 0) {
      int x, y;
      scanf("%d %d", &x, &y);
      add_position(&l, x, y);
    }
    else if (strcmp(q, rm) == 0) {
      int x, y;
      scanf("%d %d", &x, &y);
      remove_position(&l, x, y);
    }
    else if (strcmp(q, print) == 0) {
      show_all_positions(&l);
    }
    else if (strcmp(q, rma) == 0) {
      remove_all_positions(&l);
    }
    else if (strcmp(q, len) == 0) {
      printf("%d\n", get_length(&l));
    }
    else if (strcmp(q, ex) == 0)
    {
      flag = 0;
      remove_all_positions(&l);
    }
    else
      printf("Unknown command\n");

    while (c != '\n')
      scanf("%c", &c);
  }
  
  return 0;
}



