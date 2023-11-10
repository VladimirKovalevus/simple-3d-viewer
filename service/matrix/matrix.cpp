#include "matrix.hpp"

#include <stdlib.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <utility>

#define EPS 1e-6

Matrix::Matrix() : rows_{0}, columns_{0}, matrix_{nullptr} {}
Matrix::~Matrix() { __dealloc(); }
Matrix::Matrix(int rows, int columns)
    : rows_{rows}, columns_{columns}, matrix_{nullptr} {
  if (rows < 0 || columns < 0) {
    throw new std::invalid_argument("invalid matrix dimensions");
  }
  __alloc();
}

Matrix::Matrix(const Matrix &other)
    : rows_{0}, columns_{0}, matrix_{nullptr} {
  if (&other != this) {
    this->rows_ = other.rows_;
    this->columns_ = other.columns_;

    __alloc();

    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < columns_; j++) {
        (*this)[i][j] = other[i][j];
      }
    }
  }
}
Matrix::Matrix(Matrix &&other) {
  if (&other != this) {
    this->rows_ = other.rows_;
    this->columns_ = other.columns_;
    this->matrix_ = other.matrix_;

    other.rows_ = 0;
    other.columns_ = 0;
    other.matrix_ = nullptr;
  }
}

Matrix &Matrix::operator=(const Matrix &other) {
  if (this != &other) {
    __dealloc();

    this->rows_ = other.rows_;
    this->columns_ = other.columns_;

    __alloc();

    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < columns_; j++) {
        (*this)[i][j] = other[i][j];
      }
    }
  }
  return *this;
}
Matrix &Matrix::operator=(Matrix &&other) {
  if (&other != this) {
    __dealloc();

    this->rows_ = other.rows_;
    this->columns_ = other.columns_;
    this->matrix_ = other.matrix_;

    other.rows_ = 0;
    other.columns_ = 0;
    other.matrix_ = nullptr;
  }
  return *this;
}

bool Matrix::EqMatrix(const Matrix &other) {
  if (this->rows_ != other.rows_ && this->columns_ != other.columns_) {
    return false;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < columns_; j++) {
      if ((*this)[i][j] != other[i][j]) {
        return false;
      }
    }
  }
  return true;
}
void Matrix::SumMatrix(const Matrix &other) {
  if (rows_ != other.rows_ && columns_ != other.columns_) {
    throw new std::logic_error(
        "Can't compare matricies with different dimensions");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < columns_; j++) {
      (*this)[i][j] += other[i][j];
    }
  }
}
void Matrix::SubMatrix(const Matrix &other) {
  if (rows_ != other.rows_ && columns_ != other.columns_) {
    throw new std::logic_error(
        "Can't compare matricies with different dimensions");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < columns_; j++) {
      (*this)[i][j] -= other[i][j];
    }
  }
}
void Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < columns_; j++) {
      (*this)[i][j] *= num;
    }
  }
}
void Matrix::MulMatrix(const Matrix &other) {
  if (rows_ != other.columns_) {
    throw new std::logic_error(
        "Can't compare matricies with different dimensions");
  }
  Matrix tmp(this->rows_, other.columns_);

  for (int i = 0; i < tmp.rows_; i++) {
    for (int j = 0; j < tmp.columns_; j++) {
      tmp[i][j] = 0;
      for (int k = 0; k < tmp.columns_; k++) {
        tmp[i][j] += (*this)[i][k] * other[k][j];
      }
    }
  }
  *this = std::move(tmp);
}

float &Matrix::operator()(int i, int j) {
  if (rows_ <= i || columns_ <= j || i < 0 || j < 0) {
    throw new std::out_of_range("index out of range");
  }
  return (*this)[i][j];
}

Matrix Matrix::Transpose() {
  Matrix tmp(this->columns_, this->rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < columns_; j++) {
      tmp[j][i] = matrix_[i][j];
    }
  }
  return tmp;
}
Matrix Matrix::CalcComplements() {
  if (rows_ != columns_) {
    throw std::invalid_argument("matrix isn't square");
  }

  if (rows_ < 1 && columns_ < 1) {
    throw std::invalid_argument("rows and columns less than one");
  }

  if (rows_ == columns_ && rows_ == 1) {
    Matrix res(1, 1);
    res[0][0] = 1.;
    return res;
  }

  Matrix result(rows_, columns_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < columns_; j++) {
      result[i][j] = __calc_minor(i, j) * pow(-1, (i + j) % 2);
    }
  }
  return result;
}
float Matrix::Determinant() {
  if (rows_ != columns_) {
    throw std::invalid_argument("matrix isn't square");
  }

  if (rows_ < 1 && columns_ < 1) {
    throw std::invalid_argument("rows and columns less than one");
  }

  Matrix tmp = *this;
  int i, j, k;
  double det = 1.;
  int n = tmp.columns_;
  for (i = 0; i < n - 1; i++) {
    k = i;
    for (j = i + 1; j < n; ++j)
      if (fabs(tmp[j][i]) > fabs(tmp[k][i])) k = j;
    if (fabs(tmp[k][i]) < EPS) {
      det = 0;
      break;
    }
    for (int _i = 0; _i < n; _i++) {
      std::swap(tmp[k][_i], tmp[i][_i]);
    }

    if (i != k) {
      det = -det;
    }

    for (k = i + 1; k < n; k++) {
      if (fabs(tmp[i][i]) > EPS) {
        double coef = tmp[k][i] / tmp[i][i];
        for (j = i; j < n; j++) {
          tmp[k][j] -= tmp[i][j] * coef;
        }
      }
    }
    det *= tmp[i][i];
  }
  det *= tmp[columns_ - 1][columns_ - 1];

  return det;
}
Matrix Matrix::InverseMatrix() {
  double det = (*this).Determinant();
  if (fabs(det) < EPS) {
    throw std::invalid_argument("Determinant is zero");
  }
  Matrix tmp = (*this).CalcComplements();
  tmp = tmp.Transpose();
  tmp.MulNumber(1. / det);
  return tmp;
}

void Matrix::__alloc() {
  if (rows_ <= 0 || columns_ <= 0) {
    return;
  }
  this->matrix_ = new float *[rows_]();
  this->matrix_[0] = new float[columns_ * rows_]();
  for (int i = 1; i < rows_; i++) {
    this->matrix_[i] = &matrix_[0][i * columns_];
  }
}
void Matrix::__dealloc() {
  if (this->matrix_ == nullptr) {
    return;
  }
  delete[] matrix_[0];
  delete[] matrix_;
  rows_ = 0;
  columns_ = 0;
}

double Matrix::__calc_minor(int r, int c) {
  Matrix temp(this->rows_ - 1, this->columns_ - 1);
  int r_i = 0, c_i = 0;
  for (int i = 0; i < this->rows_; i++) {
    if (i != r) {
      for (int j = 0; j < this->columns_; j++) {
        if (j != c) {
          temp[r_i][c_i] = (*this)[i][j];
          c_i++;
        }
      }
      c_i = 0;
      r_i++;
    }
  }
  return temp.Determinant();
}
float *Matrix::operator[](int ind) const { return matrix_[ind]; }
Matrix Matrix::operator+(const Matrix &other) {
  Matrix res = *this;
  res.SumMatrix(other);
  return res;
}
Matrix Matrix::operator-(const Matrix &other) {
  Matrix res = *this;
  res.SubMatrix(other);
  return res;
}
Matrix Matrix::operator*(const Matrix &other) {
  Matrix res = *this;
  res.MulMatrix(other);
  return res;
}
Matrix Matrix::operator*(const double num) {
  Matrix res = *this;
  res.MulNumber(num);
  return res;
}
bool Matrix::operator==(const Matrix &other) {
  return (*this).EqMatrix(other);
}
Matrix Matrix::operator+=(const Matrix &other) {
  (*this).SumMatrix(other);
  return *this;
}
Matrix Matrix::operator-=(const Matrix &other) {
  (*this).SubMatrix(other);
  return *this;
}
Matrix Matrix::operator*=(const Matrix &other) {
  (*this).MulMatrix(other);
  return *this;
}
Matrix Matrix::operator*=(const double num) {
  (*this).MulNumber(num);
  return *this;
}

int Matrix::getRows() const { return rows_; }
int Matrix::getColumns() const { return columns_; }
void Matrix::setRows(int n_rows) {
  if (n_rows < 1) {
    throw new std::invalid_argument("Rows cant be less than 1");
  }
  Matrix tmp(n_rows, columns_);
  int min_rows = n_rows < rows_ ? n_rows : rows_;
  for (int i = 0; i < min_rows; i++) {
    for (int j = 0; j < columns_; j++) {
      tmp[i][j] = (*this)[i][j];
    }
  }
  *this = std::move(tmp);
}
void Matrix::setColumns(int n_columns) {
  if (n_columns < 1) {
    throw new std::invalid_argument("Columns cant be less than 1");
  }
  Matrix tmp(rows_, n_columns);
  int min_col = n_columns < columns_ ? n_columns : columns_;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < min_col; j++) {
      tmp[i][j] = (*this)[i][j];
    }
  }
  *this = std::move(tmp);
}
float* Matrix::data(){
  return matrix_[0];
}
