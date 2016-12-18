#include "rectangle.h"
#include <cstring>
#include <cstdio>


Rectangle::Rectangle(int id, int x, int y, int width, int height): Figure(id, x, y), width(width), height(height) {
}


void Rectangle::print() const {
  printf("Rectangle %i: x = %i y = %i width = %i height = %i\n", id, x, y, width, height);
}


bool Rectangle::is_inside(int x, int y) const {
  int x_right = 2 * this->x + width, x_left = 2 * this->x - width;
  int y_top = 2 * this->y + height, y_bottom = 2 * this->y - height;

  return ((2 * x <= x_right) && (2 * x >= x_left) && (2 * y <= y_top) && (2 * y >= y_bottom));
}


void Rectangle::zoom(int factor) {
  width *= factor;
  height *= factor;
}










