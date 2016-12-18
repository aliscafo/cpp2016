#include <algorithm>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include "matrix.h"

Matrix::Matrix(std::size_t r, std::size_t c) {
  int *mtx = new int [r * c];
  memset(mtx, 0, 4 * r * c);

  _data = new int* [r];

  for (size_t i = 0; i < r * c; i += c)
    _data[i / c] = mtx + i; 

  _rows = r;
  _cols = c;
}

Matrix::~Matrix() {
  delete[] *_data;  
  delete[] _data;
}

Matrix::Matrix(const Matrix& m) {
  _rows = m._rows;
  _cols = m._cols;
  
  int *mtx = new int [_rows * _cols];
  _data = new int* [_rows];

  for (size_t i = 0; i < _rows * _cols; i += _cols)
    _data[i / _cols] = mtx + i; 
  
  for (size_t i = 0; i < _rows; i++)
    for (size_t j = 0; j < _cols; j++)  
      _data[i][j] = m._data[i][j];
}

void Matrix::swap(Matrix& m) {
  std::swap(this->_rows, m._rows);
  std::swap(this->_cols, m._cols);
  std::swap(this->_data, m._data);
}

Matrix& Matrix::operator=(const Matrix& m) {
  if (this == &m)
    return *this;
  
  Matrix cpy(m);
  this->swap(cpy);

  return *this;
}

std::size_t Matrix::get_rows() const { return _rows; }
std::size_t Matrix::get_cols() const { return _cols; }

void Matrix::set(std::size_t i, std::size_t j, int val) {
  _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const {
  return _data[i][j];
}

void Matrix::print(FILE* f) const {
  for (size_t i = 0; i < _rows; i++) {
    for (size_t j = 0; j < _cols; j++) 
      fprintf(f, "%d ", _data[i][j]);
    fprintf(f, "\n");
  }     
}

bool Matrix::operator==(const Matrix& m) const {
  if (_rows != m._rows || _cols != m._cols)
    return false;

  for (std::size_t i = 0; i < _rows; i++)
    for (std::size_t j = 0; j < _cols; j++)
      if (_data[i][j] != m._data[i][j])
        return false;
  
  return true;
}

bool Matrix::operator!=(const Matrix& m) const {
  return !(*this == m);
}

Matrix& Matrix::operator+=(const Matrix& m) {
  Matrix mtx(*this + m);
  *this = mtx;

  return *this;
}

Matrix& Matrix::operator-=(const Matrix& m) {
  Matrix mtx(*this - m);
  *this = mtx;

  return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {
  Matrix mtx(*this * m);
  *this = mtx;

  return *this;
}

Matrix Matrix::operator+(const Matrix& m) const {
  Matrix ans(m);
  
  for (std::size_t i = 0; i < this->_rows; i++)
    for (std::size_t j = 0; j < this->_cols; j++)
      ans._data[i][j] += this->_data[i][j];

  return ans;
}

Matrix Matrix::operator-(const Matrix& m) const {
  Matrix ans(*this);
  
  for (std::size_t i = 0; i < this->_rows; i++)
    for (std::size_t j = 0; j < this->_cols; j++)
      ans._data[i][j] -= m._data[i][j];

  return ans;
}

Matrix Matrix::operator*(const Matrix& m) const {
  Matrix ans(this->_rows, m._cols);
  
  for (std::size_t i = 0; i < this->_rows; i++)
    for (std::size_t j = 0; j < m._cols; j++)
      for (std::size_t k = 0; k < this->_cols; k++)      
        ans._data[i][j] += this->_data[i][k] * m._data[k][j];

  return ans;
}
