#include "../include/clist.h"
#include <string.h>          
#define check(xx, yy) pos->x == x && pos->y == y
#define MAXN 10

struct position_node {
  int x, y;
  struct intrusive_node node;
}; 
 

void add_position(intrusive_list_t* l, int x, int y) {
  position_node_t* pos = (position_node_t*)malloc(sizeof(position_node_t));
  pos->x = x;
  pos->y = y;
  add_node(l, &(pos->node));
}

void print_node(intrusive_node_t* t, void* arg) {
  position_node_t* pos;
  pos = container_of(t, position_node_t, node);
  
  printf((char*)arg, pos->x, pos->y);
}  

void count_node(intrusive_node_t* t, void* arg) {
  *(int*)arg += 1;
}
                                                                                               
void apply(intrusive_list_t* l, void (*op)(intrusive_node_t*, void*), void* arg) {
  if (get_length(l) == 0) { return; }

  intrusive_node_t* t = l->head;
  position_node_t* pos;

  while (1) {
    op(t, arg);

    if (t == l->head->next)
      break;

    t = t->prev;
  }
}

void save_text(intrusive_list_t* l, FILE* f) {
  if (get_length(l) == 0) { return; }

  intrusive_node_t* t = l->head;
  position_node_t* pos;

  while (1) {
    pos = container_of(t, position_node_t, node);
    
    fprintf(f, "%d %d\n", pos->x, pos->y);

    if (t == l->head->next)
      break;

    t = t->prev;
  }  
}


void save_bin(intrusive_list_t* l, FILE* f) {
  if (get_length(l) == 0) { return; }

  intrusive_node_t* t = l->head;
  position_node_t* pos;

  while (1) {
    pos = container_of(t, position_node_t, node);
    
    fwrite(&(pos->x), 3, 1, f);
    fwrite(&(pos->y), 3, 1, f);

    if (t == l->head->next)
      break;

    t = t->prev;
  }  
}

void remove_all_positions(intrusive_list_t* l) {
  if (get_length(l) == 0) { return; }  
  
  intrusive_node_t* t = l->head;  
  position_node_t* pos;

  while (1) {
    pos = container_of(t, position_node_t, node);
    
    remove_node(l, t);
    t = t->next;
    free(pos);

    if (l->head == NULL)
      break;
    if (t == l->head)
    {
      pos = container_of(t, position_node_t, node);
      remove_node(l, t);
      free(pos);
      break;
    }
  }
}


int to_int(int x) {
  if (x & (1 << 23)) {
    x = x | (255 << 24);
    x = ~x;
    x += 1;
    x = -x;
  }      
  return x;
}


int main(int argc, char* argv[]) {  
  intrusive_list_t l;
  init_list(&l);    

  FILE* fload;

  if (strcmp(argv[1], "loadtext") == 0) {
    fload = fopen(argv[2], "rt");
    int x, y;
    
    while (fscanf(fload, "%d %d", &x, &y) == 2)
      add_position(&l, x, y);
  }

  if (strcmp(argv[1], "loadbin") == 0) {
    fload = fopen(argv[2], "rb");
    int x = 0, y = 0;
    
    while (fread(&x, 3, 1, fload) == 1 && fread(&y, 3, 1, fload) == 1) { 
      x = to_int(x);
      y = to_int(y);

      add_position(&l, x, y);
      x = 0;
      y = 0;
    }
  }
    
  if (strcmp(argv[3], "print") == 0) 
    apply(&l, print_node, argv[4]);

  if (strcmp(argv[3], "count") == 0) {
    int n = 0;
    apply(&l, count_node, &n);
    printf("%d", n);
  }

  if (strcmp(argv[3], "savetext") == 0) {
    FILE* fsave = fopen(argv[4], "wt");
    save_text(&l, fsave);
    fclose(fsave);
  }

  if (strcmp(argv[3], "savebin") == 0) {
    FILE* fsave = fopen(argv[4], "wb");
    save_bin(&l, fsave);
    fclose(fsave);
  }

  remove_all_positions(&l);
  fclose(fload);
  
  return 0;
}
