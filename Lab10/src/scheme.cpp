#include "scheme.h"
#include <cassert>
#include <cstdio>

Scheme::Scheme(int capacity) {
  figures_ = new Figure*[capacity];
  sz = 0;
}


Scheme::~Scheme() {
  delete [] figures_;
}


void Scheme::push_back_figure(Figure* fg) {
  figures_[sz] = fg;
  sz++;  
}

    
void Scheme::remove_figure(int id) {
  assert(sz > 0);
  int i;

  for (i = 0; i < sz; i++) 
    if (figures_[i]->get_id() == id)
      break;

  if (i == sz)
    return;

  delete figures_[i];

  for (int j = i; j < sz - 1; j++)
    figures_[j] = figures_[j + 1];
  sz--;
}


void Scheme::print_all_figures() {
  for (int i = 0; i < sz; i++)
    figures_[i]->print();
}


void Scheme::zoom_figure(int id, int factor) {
  for (int i = 0; i < sz; i++) 
    if (figures_[i]->get_id() == id)
      figures_[i]->zoom(factor);
}
    

Figure* Scheme::is_inside_figure(int x, int y) {
  for (int i = 0; i < sz; i++)
    if (figures_[i]->is_inside(x, y))
      return figures_[i];
  return NULL;
}


void Scheme::move(int id, int new_x, int new_y) {
  for (int i = 0; i < sz; i++) 
    if (figures_[i]->get_id() == id)
      figures_[i]->move(new_x, new_y);
}


