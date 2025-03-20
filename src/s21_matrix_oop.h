#include <cmath>
#include <iostream>
#include <stdexcept>

class S21Matrix {
 public:
  S21Matrix();  // Default constructor
  S21Matrix(int rows, int columns);
  ~S21Matrix();  // Destructor
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);

  double& operator()(int row, int col);
  const double& operator()(int row, int col) const;

  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);

  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(const double num) const;

  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other);
  bool operator==(const S21Matrix& other) const;

  S21Matrix CalcComplements() const;
  S21Matrix Transpose() const;
  double Determinant() const;
  S21Matrix InverseMatrix();

  bool EqMatrix(const S21Matrix& other) const;

  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulMatrix(const S21Matrix& other);
  void MulNumber(const double num);

  int GetRows() const;
  int GetCols() const;
  void SetRows(int rows);
  void SetCols(int cols);

 private:
  int rows_;
  int cols_;
  double** matrix_;
  void remove_matrix();
  bool IsInvalid() const;
  void create_matrix(int rows, int cols);
  void copy_matrix(const S21Matrix& other);
  int CheckMatrices(const S21Matrix& other) const;
  void get_minor(int skip_row, int skip_col, const S21Matrix& minor) const;
};