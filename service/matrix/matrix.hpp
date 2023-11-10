#ifndef _MATRIX_
#define _MATRIX_

class Matrix
{
public:
  Matrix();
  Matrix(int rows, int columns);
  Matrix(const Matrix &other);
  Matrix(Matrix &&other);

  Matrix &operator=(const Matrix &other);
  Matrix &operator=(Matrix &&other);

  float operator()(int i, int j) const;
  float &operator()(int i, int j);

  Matrix operator+(const Matrix &other);
  Matrix operator-(const Matrix &other);
  Matrix operator*(const Matrix &other);
  Matrix operator*(const double num);
  Matrix operator+=(const Matrix &other);
  Matrix operator-=(const Matrix &other);
  Matrix operator*=(const Matrix &other);
  Matrix operator*=(const double num);
  bool operator==(const Matrix &other);

  bool EqMatrix(const Matrix &other);
  void SumMatrix(const Matrix &other);
  void SubMatrix(const Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const Matrix &other);

  Matrix Transpose();
  Matrix CalcComplements();
  float Determinant();
  Matrix InverseMatrix();

  ~Matrix();

  int getRows() const;
  int getColumns() const;

  void setRows(int n_rows);
  void setColumns(int n_columns);

  float* data();
private:
  int rows_;
  int columns_;
  float **matrix_;

  float*operator[](int ind) const;

  void __dealloc();
  void __alloc();
  void __resize(int n_rows, int n_coluns);

  double __calc_minor(int r, int c);
};

#endif //_MATRIX_
