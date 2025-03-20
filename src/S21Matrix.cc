#include "s21_matrix_oop.h"
// METHODS

S21Matrix::S21Matrix(int rows, int columns) {
  this->create_matrix(rows, columns);
}

// Constructor with default settings
S21Matrix::S21Matrix() { this->create_matrix(1, 1); }

// Adapter for Destructor
S21Matrix::~S21Matrix() {
  {
    if (matrix_) {
      remove_matrix();
    }
  }
}

// Adapter for copying
S21Matrix::S21Matrix(const S21Matrix& other) { this->copy_matrix(other); }

// Adapter for moving
S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

// REWRITTEN FROM THE LAST PROJECT
void S21Matrix::create_matrix(int rows, int cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument("Invalid matrix");
  }
  matrix_ = new double*[rows];
  if (!matrix_) {
    throw std::runtime_error("Memory allocation for rows has failed");
  }
  for (int i = 0; i < rows; ++i) {
    matrix_[i] = new double[cols];
    if (!matrix_[i]) {
      for (int j = 0; j < i; ++j) {
        delete[] matrix_[j];
      }
      delete[] matrix_;
      throw std::runtime_error("Memory allocation for columns has failed");
    }

    for (int j = 0; j < cols; ++j) {
      matrix_[i][j] = 0;
    }
  }
  rows_ = rows;
  cols_ = cols;
}

void S21Matrix::copy_matrix(const S21Matrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  this->create_matrix(other.rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

void S21Matrix::remove_matrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
  matrix_ = nullptr;
}

// ACCESS METHODS
int S21Matrix::GetRows() const { return rows_; }
int S21Matrix::GetCols() const { return cols_; }

void S21Matrix::SetRows(int rows) {
  if (rows != rows_) {
    S21Matrix temp(rows, cols_);
    int min_rows = std::min(rows, rows_);
    for (int i = 0; i < min_rows; i++) {
      for (int j = 0; j < cols_; ++j) {
        temp.matrix_[i][j] = matrix_[i][j];
      }
    }
    *this = std::move(temp);
  }
}

void S21Matrix::SetCols(int cols) {
  if (cols != cols_) {
    S21Matrix temp(rows_, cols);
    int min_cols = std::min(cols, cols_);
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < min_cols; j++) {
        temp.matrix_[i][j] = matrix_[i][j];
      }
    }
    *this = std::move(temp);
  }
}

// OPERATORS

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    remove_matrix();
    copy_matrix(other);
  }
  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
  if (this != &other) {
    remove_matrix();
    matrix_ = other.matrix_;
    rows_ = other.rows_;
    cols_ = other.cols_;

    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) {
  this->MulNumber(num);
  return *this;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  return EqMatrix(other);
}

double& S21Matrix::operator()(int row, int col) {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
    throw std::invalid_argument("Invalid argument");
  }
  return matrix_[row][col];
}

const double& S21Matrix::operator()(int row, int col) const {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
    throw std::invalid_argument("Invalid argument");
  }
  return matrix_[row][col];
}

// REWRITTEN FUNCTIONS FROM THE PREVIOUS PROJECT

bool S21Matrix::IsInvalid() const {
  return (matrix_ == nullptr || rows_ <= 0 || cols_ <= 0);
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (this->cols_ != other.rows_) {
    throw std::invalid_argument("Invalid matrix");
  }
  S21Matrix result(this->rows_, other.cols_);

  for (int k = 0; k < this->rows_; k++) {
    for (int i = 0; i < other.cols_; i++) {
      result.matrix_[k][i] = 0;
      for (int j = 0; j < this->cols_; j++) {
        result.matrix_[k][i] += this->matrix_[k][j] * other.matrix_[j][i];
      }
    }
  }
  this->copy_matrix(result);
}

int S21Matrix::CheckMatrices(const S21Matrix& other) const {
  if (IsInvalid() || other.IsInvalid()) {
    return 1;
  }
  return (rows_ == other.rows_ && cols_ == other.cols_) ? 0 : 1;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (CheckMatrices(other) != 0) {
    throw std::invalid_argument("Invalid matrix");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (CheckMatrices(other) != 0) {
    throw std::invalid_argument("Invalid matrix");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_ ||
      this->IsInvalid() || other.IsInvalid()) {
    throw std::invalid_argument("Invalid matrix");
  }

  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      if (std::fabs(this->matrix_[i][j] - other.matrix_[i][j]) >= 1e-07) {
        return false;
      }
    }
  }
  return true;
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

S21Matrix S21Matrix::Transpose() const {
  if (!this->IsInvalid()) {
    S21Matrix result(this->cols_, this->rows_);
    for (int i = 0; i < this->rows_; i += 1) {
      for (int j = 0; j < this->cols_; j += 1) {
        result.matrix_[j][i] = this->matrix_[i][j];
      }
    }
    return result;
  } else {
    throw std::invalid_argument("Invalid matrix");
  }
}

void S21Matrix::get_minor(int skip_row, int skip_col,
                          const S21Matrix& minor) const {
  int dimension = this->rows_;
  for (int row = 0, m_row = 0; row < dimension; row++) {
    for (int col = 0, m_col = 0; col < dimension; col++) {
      if (row != skip_row && col != skip_col) {
        minor.matrix_[m_row][m_col] = this->matrix_[row][col];
        m_col++;
        if (m_col == dimension - 1) {
          m_col = 0;
          m_row++;
        }
      }
    }
  }
}

double S21Matrix::Determinant() const {
  double result = 0.0;
  if ((this->IsInvalid()) || (this->rows_ != this->cols_)) {
    throw std::invalid_argument("Invalid matrix");
  } else {
    if (this->rows_ == 1) {
      result = this->matrix_[0][0];
    }
    if (this->rows_ == 2) {
      result = this->matrix_[0][0] * this->matrix_[1][1] -
               this->matrix_[0][1] * this->matrix_[1][0];
    }
  }
  if (this->rows_ > 2) {
    for (int f = 0; f < this->rows_; f++) {
      S21Matrix minor(this->rows_ - 1, this->cols_ - 1);
      this->get_minor(0, f, minor);
      double pre_result = 0;
      pre_result = minor.Determinant();
      result += (this->matrix_[0][f] * pre_result * (f % 2 == 0 ? 1 : -1));
      minor.~S21Matrix();
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() const {
  int sign;
  if (this->IsInvalid()) {
    throw std::invalid_argument("Invalid matrix");
  }
  if (this->rows_ != this->cols_) {
    throw std::invalid_argument("Invalid matrix");
  }
  double determinant = 0;

  S21Matrix result(this->rows_, this->cols_);
  if (this->rows_ != 1) {
    S21Matrix minor(this->rows_ - 1, this->cols_ - 1);
    for (int i = 0; i < this->rows_; i += 1) {
      for (int j = 0; j < this->cols_; j += 1) {
        this->get_minor(i, j, minor);
        if ((i + j) % 2 == 0) {
          sign = 1;
        } else
          sign = -1;
        determinant = minor.Determinant();
        result.matrix_[i][j] = sign * determinant;
      }
    }
  } else {
    result.matrix_[0][0] = 1;
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (this->IsInvalid() || this->cols_ != this->rows_) {
    throw std::invalid_argument("Invalid matrix");
  }
  double determinant = this->Determinant();
  if (fabs(determinant) < 1e-6) {
    throw std::invalid_argument("Invalid matrix");
  }
  if (this->rows_ == 1) {
    S21Matrix result(1, 1);
    result.matrix_[0][0] = 1.0 / this->matrix_[0][0];
    return result;
  }
  S21Matrix result(this->rows_, this->cols_);
  S21Matrix transposed_m = this->Transpose();
  S21Matrix adj_m = transposed_m.CalcComplements();
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      result.matrix_[i][j] = adj_m.matrix_[i][j] * (1 / determinant);
    }
  }
  return result;
}
