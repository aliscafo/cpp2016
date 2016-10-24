#include "../include/my_vector.h"
#include <assert.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <stdio.h>

MyVector::MyVector() {
  _cp = 2;
  _sz = 0;
  _data = (int*)malloc(2 * sizeof(int));
}

MyVector::MyVector(std::size_t init_capacity) {
  _cp = init_capacity;
  _sz = 0;
  _data = (int*)malloc(init_capacity * sizeof(int));
}

MyVector::~MyVector() {
  free(_data);
}

void MyVector::set(std::size_t index, int value) {
  assert(0 <= index && index < _sz);
  _data[index] = value;
}

int MyVector::get(std::size_t index) {
  assert(0 <= index && index < _sz);
  return _data[index];
}

std::size_t MyVector::size() {
  return _sz;
}

std::size_t MyVector::capacity() {
  return _cp;
}

void MyVector::reserve(std::size_t new_capacity) {
  if (_cp < new_capacity) {
    _data = (int*)realloc(_data, new_capacity * sizeof(int));
    _cp = new_capacity;
  }  
}

void MyVector::resize(std::size_t new_size) {
  if (_cp < new_size) {
    size_t new_capacity_pow = _cp;
    while (new_capacity_pow < new_size)
      new_capacity_pow *= 2;

    reserve(new_capacity_pow);
  }

  for (size_t i = _sz; i < new_size; i++)
    _data[i] = 0; 

  _sz = new_size;
}

void MyVector::push_back(int value) {
  if (_sz + 1 > _cp)
    reserve(_cp * 2);  
  _sz++;
  set(_sz - 1, value);
}

void MyVector::insert(std::size_t index, int value) {
  _sz++;
  assert(0 <= index && index < _sz);
  reserve(_sz);
  for (size_t i = _sz - 1; i > index; i--)
    _data[i] = _data[i - 1];
  set(index, value);
}

void MyVector::erase(std::size_t index) {
  assert(0 <= index && index < _sz);

  for (size_t i = index; i < _sz - 1; i++)
    _data[i] = _data[i + 1];
  _sz--;    
}



