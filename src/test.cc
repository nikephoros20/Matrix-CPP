#include "gtest/gtest.h"
#include "s21_matrix_oop.h"

TEST(test_01, basic_constructor) {
  S21Matrix m;
  EXPECT_EQ(m.GetCols(), 1);
  EXPECT_EQ(m.GetRows(), 1);
  m.~S21Matrix();
}

TEST(test, complements_error) {
  S21Matrix m;
  m(0, 0) = 10;
  m.CalcComplements();
  EXPECT_EQ(m(0, 0), 10);
}

TEST(test, constructor_error_98) { EXPECT_ANY_THROW(S21Matrix m(-10, 10)); }

TEST(test, constructor_error_97) {
  S21Matrix m;
  m.~S21Matrix();
  EXPECT_ANY_THROW(m(10, 10));
}

TEST(test, eq_error_99) {
  S21Matrix A(1, 1);
  S21Matrix B(1, 1);
  A(0, 0) = 10;
  EXPECT_EQ(false, A.EqMatrix(B));
}

TEST(test_01, eq_Test) {
  S21Matrix m(12, 12);
  S21Matrix n(1, 1);
  EXPECT_ANY_THROW(m == n);
}

TEST(test_01, mul_error) {
  S21Matrix m(12, 12);
  S21Matrix n(1, 1);
  EXPECT_ANY_THROW(m = m * n);
}

TEST(test, setting_error_99) {
  S21Matrix n(1, 1);
  EXPECT_ANY_THROW(n(-1, 0));
}

TEST(test, access_error) {
  S21Matrix matrix(3, 3);
  matrix(1, 1) = 42.0;
  double value = 0;
  EXPECT_ANY_THROW(value = matrix(10, 10));
  EXPECT_EQ(value, 0);
}

TEST(test, access_error_02) {
  S21Matrix matrix(3, 3);
  matrix(1, 1) = 42.0;
  double value = 0;
  EXPECT_ANY_THROW(value = matrix(-10, 10));
  EXPECT_EQ(value, 0);
}

TEST(Test, Transpose1) {
  S21Matrix A(3, 2);
  A(2, 0) = 10;
  S21Matrix B = A.Transpose();
  EXPECT_EQ(A(2, 0), B(0, 2));
}

TEST(test_01, rc_constructor) {
  S21Matrix m(7, 13);
  EXPECT_EQ(m.GetRows(), 7);
  EXPECT_EQ(m.GetCols(), 13);
}

TEST(test_01, copy_constructor) {
  S21Matrix m(12, 12);
  S21Matrix copy(m);

  EXPECT_EQ(copy.GetCols(), 12);
  EXPECT_EQ(copy.GetRows(), 12);
}

TEST(test_01, move_constructor) {
  S21Matrix m(12, 12);
  S21Matrix moved(std::move(m));

  EXPECT_EQ(m.GetCols(), 0);
  EXPECT_EQ(m.GetRows(), 0);
  EXPECT_EQ(moved.GetCols(), 12);
  EXPECT_EQ(moved.GetRows(), 12);
}

TEST(test_01, brackets_operator) {
  S21Matrix m(6, 9);
  EXPECT_EQ(m(0, 0), 0);

  m(0, 1) = 21;
  EXPECT_EQ(m(0, 1), 21);

  m(5, 8) = 21.123;
  EXPECT_EQ(m(5, 8), 21.123);
}

TEST(test_01, square_brackets_operator) {
  S21Matrix m(6, 9);
  EXPECT_EQ(m(0, 0), 0);

  m(5, 5) = 21;
  EXPECT_EQ(m(5, 5), 21);

  m(5, 8) = 21.123;
  EXPECT_EQ(m(5, 8), 21.123);
}

TEST(test_03, SetRows_up) {
  S21Matrix m(2, 2);
  m(1, 1) = 6.9;

  m.SetRows(5);
  EXPECT_EQ(m.GetRows(), 5);
  EXPECT_EQ(m(1, 1), 6.9);
}

TEST(test_03, SetRows_down) {
  S21Matrix m(2, 2);
  m(0, 0) = 6.9;

  m.SetRows(1);
  EXPECT_EQ(m.GetRows(), 1);
  EXPECT_EQ(m(0, 0), 6.9);
}

TEST(test_03, SetRows_zero) {
  S21Matrix m;

  EXPECT_ANY_THROW(m.SetRows(0));
}

TEST(test_03, SetCols_up) {
  S21Matrix m(2, 2);
  m(1, 1) = 6.9;

  m.SetCols(5);
  EXPECT_EQ(m.GetCols(), 5);
  EXPECT_EQ(m(1, 1), 6.9);
}

TEST(test_03, SetCols_down) {
  S21Matrix m(2, 2);
  m(0, 0) = 6.9;

  m.SetCols(1);
  EXPECT_EQ(m.GetCols(), 1);
  EXPECT_EQ(m(0, 0), 6.9);
}

TEST(test_03, SetCols_zero) {
  S21Matrix m;

  EXPECT_ANY_THROW(m.SetCols(0));
}

TEST(test_overload, equal_lvalue) {
  S21Matrix m;
  S21Matrix x(3, 6);
  x(1, 2) = 3;
  x(2, 2) = 3;

  m = x;

  EXPECT_EQ(m.GetRows(), 3);
  EXPECT_EQ(m.GetCols(), 6);
  EXPECT_EQ(m(1, 2), 3);
  EXPECT_EQ(m(2, 2), 3);
}

TEST(test_overload, equal_rvalue) {
  S21Matrix m(2, 2);
  S21Matrix n;

  n = std::move(m);

  EXPECT_EQ(n.GetCols(), 2);
  EXPECT_EQ(n.GetRows(), 2);
}

TEST(test_02, eq_matrix) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  ASSERT_TRUE(m == n);
}

TEST(test_02, eq_matrix1) {
  S21Matrix m(3, 2);
  S21Matrix n;

  m(0, 1) = 21;
  n = m;

  ASSERT_TRUE(m == n);
}

TEST(test_02, sum_matrix) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m(1, 1) = 1;
  n(1, 1) = 1;

  m.SumMatrix(n);

  EXPECT_EQ(m(0, 0), 2);
  EXPECT_EQ(m(1, 1), 2);
}

TEST(test_02, add_operator_overload) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m(1, 1) = 1;
  n(1, 1) = 1;

  m = m + n;

  EXPECT_EQ(m(0, 0), 2);
  EXPECT_EQ(m(1, 1), 2);
}

TEST(test_02, eqadd_operator_overload) {
  S21Matrix m(1, 1);
  S21Matrix n(1, 1);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m += n;

  EXPECT_EQ(m(0, 0), 2);
}

TEST(test_02, sub_matrix) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m(1, 1) = 1;
  n(1, 1) = 1;

  m.SubMatrix(n);

  EXPECT_EQ(m(0, 0), 0);
  EXPECT_EQ(m(1, 1), 0);
}

TEST(test_02, eqsub_overloaded_operator) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m(1, 1) = 1;
  n(1, 1) = 1;

  m -= n;

  EXPECT_EQ(m(0, 0), 0);
  EXPECT_EQ(m(1, 1), 0);
}

TEST(test_02, sub_operator_overload) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m(1, 1) = 1;
  n(1, 1) = 1;

  m = m - n;

  EXPECT_EQ(m(0, 0), 0);
  EXPECT_EQ(m(1, 1), 0);
}

TEST(test_02, mul_matrices) {
  const int rows = 2;
  const int cols = 3;

  S21Matrix m(rows, cols);
  S21Matrix n(cols, rows);

  for (int i = 0, c = 1; i < rows; i++)
    for (int j = 0; j < cols; j++) m(i, j) = c++;

  for (int i = 0, c = 7; i < cols; i++)
    for (int j = 0; j < rows; j++) n(i, j) = c++;

  m.MulMatrix(n);

  S21Matrix res(2, 2);
  res(0, 0) = 58;
  res(0, 1) = 64;
  res(1, 0) = 139;
  res(1, 1) = 154;

  ASSERT_TRUE(m.EqMatrix(res));
}

TEST(test_02, eqmul_operator) {
  const int rows = 2;
  const int cols = 3;

  S21Matrix m(rows, cols);
  S21Matrix n(cols, rows);

  for (int i = 0, c = 1; i < rows; i++)
    for (int j = 0; j < cols; j++) m(i, j) = c++;

  for (int i = 0, c = 7; i < cols; i++)
    for (int j = 0; j < rows; j++) n(i, j) = c++;

  m *= n;

  S21Matrix res(2, 2);
  res(0, 0) = 58;
  res(0, 1) = 64;
  res(1, 0) = 139;
  res(1, 1) = 154;

  ASSERT_TRUE(m.EqMatrix(res));
}

TEST(test_02, eqmul_operator_num) {
  const int rows = 2;
  const int cols = 3;

  S21Matrix m(rows, cols);

  for (int i = 0, c = 1; i < rows; i++)
    for (int j = 0; j < cols; j++) m(i, j) = c++;

  m *= 2;

  S21Matrix res(2, 3);
  res(0, 0) = 2;
  res(0, 1) = 4;
  res(0, 2) = 6;
  res(1, 0) = 8;
  res(1, 1) = 10;
  res(1, 2) = 12;

  ASSERT_TRUE(m.EqMatrix(res));
}

TEST(test_02, mul_operator) {
  const int rows = 2;
  const int cols = 3;

  S21Matrix m(rows, cols);
  S21Matrix n(cols, rows);

  for (int i = 0, c = 1; i < rows; i++)
    for (int j = 0; j < cols; j++) m(i, j) = c++;

  for (int i = 0, c = 7; i < cols; i++)
    for (int j = 0; j < rows; j++) n(i, j) = c++;

  m = m * n;

  S21Matrix res(2, 2);
  res(0, 0) = 58;
  res(0, 1) = 64;
  res(1, 0) = 139;
  res(1, 1) = 154;

  ASSERT_TRUE(m == res);
}

TEST(test_02, mul_operator_num) {
  const int rows = 2;
  const int cols = 3;

  S21Matrix m(rows, cols);

  for (int i = 0, c = 1; i < rows; i++)
    for (int j = 0; j < cols; j++) m(i, j) = c++;

  m = m * 2;

  S21Matrix res(2, 3);
  res(0, 0) = 2;
  res(0, 1) = 4;
  res(0, 2) = 6;
  res(1, 0) = 8;
  res(1, 1) = 10;
  res(1, 2) = 12;

  ASSERT_TRUE(m == res);
}

TEST(test_02, determinant) {
  S21Matrix m(2, 3);
  EXPECT_THROW(m.Determinant(), std::invalid_argument);
}

TEST(test_02, determinant_zero) {
  const int size = 5;
  S21Matrix m(5, 5);

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) m(i, j) = j;

  ASSERT_NEAR(0, m.Determinant(), 1e-06);
}

TEST(test_02, determinant_5x5) {
  int size = 5;
  S21Matrix m(size, size);

  m(0, 1) = 6;
  m(0, 2) = -2;
  m(0, 3) = -1;
  m(0, 4) = 5;
  m(1, 3) = -9;
  m(1, 4) = -7;
  m(2, 1) = 15;
  m(2, 2) = 35;
  m(3, 1) = -1;
  m(3, 2) = -11;
  m(3, 3) = -2;
  m(3, 4) = 1;
  m(4, 0) = -2;
  m(4, 1) = -2;
  m(4, 2) = 3;
  m(4, 4) = -2;

  double res = m.Determinant();
  ASSERT_NEAR(res, 2480, 1e-6);
}

TEST(test_02, determinant_3x3) {
  const int size = 3;
  S21Matrix m(size, size);

  m(0, 0) = 2;
  m(0, 1) = 3;
  m(0, 2) = 1;
  m(1, 0) = 7;
  m(1, 1) = 4;
  m(1, 2) = 1;
  m(2, 0) = 9;
  m(2, 1) = -2;
  m(2, 2) = 1;

  double res = m.Determinant();
  ASSERT_NEAR(res, -32, 1e-6);
}

TEST(test_02, determinant_2x2) {
  const int size = 2;
  S21Matrix m(size, size);

  m(0, 0) = -5;
  m(0, 1) = -4;
  m(1, 0) = -2;
  m(1, 1) = -3;

  double res = m.Determinant();
  ASSERT_NEAR(res, 7, 1e-6);
}

TEST(test_02, complements_3x3) {
  const int rows = 3;
  const int cols = 3;

  S21Matrix value1(rows, cols);
  S21Matrix right_res(rows, cols);

  right_res(0, 0) = 0;
  right_res(0, 1) = 10;
  right_res(0, 2) = -20;
  right_res(1, 0) = 4;
  right_res(1, 1) = -14;
  right_res(1, 2) = 8;
  right_res(2, 0) = -8;
  right_res(2, 1) = -2;
  right_res(2, 2) = 4;

  value1(0, 0) = 1;
  value1(0, 1) = 2;
  value1(0, 2) = 3;
  value1(1, 0) = 0;
  value1(1, 1) = 4;
  value1(1, 2) = 2;
  value1(2, 0) = 5;
  value1(2, 1) = 2;
  value1(2, 2) = 1;

  S21Matrix res = value1.CalcComplements();

  ASSERT_TRUE(res == right_res);
}

TEST(test_02, CalcComplements_throw) {
  S21Matrix m(3, 12);
  EXPECT_ANY_THROW(m.CalcComplements());
}

TEST(test_02, complements_3x3_1) {
  const int rows = 3;
  const int cols = 3;

  S21Matrix value1(rows, cols);
  S21Matrix right_res(rows, cols);

  value1(0, 0) = 1.0;
  value1(0, 1) = 2.0;
  value1(0, 2) = 3.0;
  value1(1, 0) = 0.0;
  value1(1, 1) = 4.0;
  value1(1, 2) = 2.0;
  value1(2, 0) = 5.0;
  value1(2, 1) = 2.0;
  value1(2, 2) = 1.0;

  right_res(0, 0) = 0.0;
  right_res(0, 1) = 10.0;
  right_res(0, 2) = -20.0;
  right_res(1, 0) = 4.0;
  right_res(1, 1) = -14.0;
  right_res(1, 2) = 8.0;
  right_res(2, 0) = -8.0;
  right_res(2, 1) = -2.0;
  right_res(2, 2) = 4.0;

  S21Matrix res = value1.CalcComplements();

  ASSERT_TRUE(res == right_res);
}

TEST(test_01, zero_size) { EXPECT_ANY_THROW(S21Matrix(0, 1)); }

TEST(test_02, complements_3x3_2) {
  const int rows = 3;
  const int cols = 3;

  S21Matrix value1(rows, cols);
  S21Matrix right_res(rows, cols);

  value1(0, 0) = 1;
  value1(0, 1) = 2;
  value1(0, 2) = 3;
  value1(1, 1) = 4;
  value1(1, 2) = 2;
  value1(2, 0) = 5;
  value1(2, 1) = 2;
  value1(2, 2) = 1;

  right_res(0, 1) = 10;
  right_res(0, 2) = -20;
  right_res(1, 0) = 4;
  right_res(1, 1) = -14;
  right_res(1, 2) = 8;
  right_res(2, 0) = -8;
  right_res(2, 1) = -2;
  right_res(2, 2) = 4;

  S21Matrix res = value1.CalcComplements();
  ASSERT_TRUE(res == right_res);
}

TEST(test_02, inverese_3x3) {
  const int size = 3;
  S21Matrix value1(size, size);
  S21Matrix right_res(size, size);

  right_res(0, 0) = 44300.0 / 367429.0;
  right_res(0, 1) = -236300.0 / 367429.0;
  right_res(0, 2) = 200360.0 / 367429.0;
  right_res(1, 0) = 20600.0 / 367429.0;
  right_res(1, 1) = 56000.0 / 367429.0;
  right_res(1, 2) = -156483.0 / 367429.0;
  right_res(2, 0) = 30900.0 / 367429.0;
  right_res(2, 1) = 84000.0 / 367429.0;
  right_res(2, 2) = -51010.0 / 367429.0;

  value1(0, 0) = 2.8;
  value1(0, 1) = 1.3;
  value1(0, 2) = 7.01;
  value1(1, 0) = -1.03;
  value1(1, 1) = -2.3;
  value1(1, 2) = 3.01;
  value1(2, 0) = 0;
  value1(2, 1) = -3;
  value1(2, 2) = 2;

  ASSERT_TRUE(value1.InverseMatrix() == right_res);
}

TEST(test_02, inverese_3x3_1) {
  const int size = 3;
  S21Matrix value1(size, size);
  S21Matrix right_res(size, size);
  right_res(0, 0) = 1.0;
  right_res(0, 1) = -1.0;
  right_res(0, 2) = 1.0;
  right_res(1, 0) = -38.0;
  right_res(1, 1) = 41.0;
  right_res(1, 2) = -34.0;
  right_res(2, 0) = 27.0;
  right_res(2, 1) = -29.0;
  right_res(2, 2) = 24.0;

  value1(0, 0) = 2.0;
  value1(0, 1) = 5.0;
  value1(0, 2) = 7.0;
  value1(1, 0) = 6.0;
  value1(1, 1) = 3.0;
  value1(1, 2) = 4.0;
  value1(2, 0) = 5.0;
  value1(2, 1) = -2.0;
  value1(2, 2) = -3.0;

  ASSERT_TRUE(value1.InverseMatrix() == right_res);
}

TEST(test_02, inverse_throw) {
  S21Matrix m(2, 3);
  EXPECT_ANY_THROW(m.InverseMatrix());

  S21Matrix n(2, 2);
  EXPECT_ANY_THROW(n.InverseMatrix());
}

TEST(test_02, inverse_1x1) {
  S21Matrix m(1, 1);
  m(0, 0) = 21.123;
  double right_res = 1 / m(0, 0);
  double result = m.InverseMatrix()(0, 0);
  ASSERT_NEAR(right_res, result, 1e-06);
}

TEST(test_02, inverese_3x3_2) {
  const int size = 3;
  S21Matrix value1(size, size);
  S21Matrix right_res(size, size);

  value1(0, 0) = 2;
  value1(0, 1) = 5;
  value1(0, 2) = 7;
  value1(1, 0) = 6;
  value1(1, 1) = 3;
  value1(1, 2) = 4;
  value1(2, 0) = 5;
  value1(2, 1) = -2;
  value1(2, 2) = -3;

  right_res(0, 0) = 1;
  right_res(0, 1) = -1;
  right_res(0, 2) = 1;
  right_res(1, 0) = -38;
  right_res(1, 1) = 41;
  right_res(1, 2) = -34;
  right_res(2, 0) = 27;
  right_res(2, 1) = -29;
  right_res(2, 2) = 24;
  ASSERT_TRUE(value1.InverseMatrix() == right_res);
}

TEST(test_02, inverese_3x3_3) {
  const int size = 3;
  S21Matrix value1(size, size);
  S21Matrix right_res(size, size);

  value1(0, 0) = 2;
  value1(0, 1) = 5;
  value1(0, 2) = 7;
  value1(1, 0) = 6;
  value1(1, 1) = 3;
  value1(1, 2) = 4;
  value1(2, 0) = 5;
  value1(2, 1) = -2;
  value1(2, 2) = -3;

  right_res(0, 0) = 1;
  right_res(0, 1) = -1;
  right_res(0, 2) = 1;
  right_res(1, 0) = -38;
  right_res(1, 1) = 41;
  right_res(1, 2) = -34;
  right_res(2, 0) = 27;
  right_res(2, 1) = -29;
  right_res(2, 2) = 24;
  ASSERT_TRUE(value1.InverseMatrix() == right_res);
}

TEST(test_02, brackets_const) {
  const S21Matrix m(3, 3);

  ASSERT_EQ(m(0, 0), 0);
}

TEST(Test, Error1) {
  S21Matrix A;
  A.~S21Matrix();
  EXPECT_THROW(A.CalcComplements(), std::invalid_argument);
}
TEST(Test, Error2) {
  S21Matrix A;
  A.~S21Matrix();
  EXPECT_THROW(A.Determinant(), std::invalid_argument);
}
TEST(Test, Error3) {
  S21Matrix A(1, 2);
  EXPECT_THROW(A.Determinant(), std::invalid_argument);
}
TEST(Test, Error4) {
  S21Matrix A;
  A.~S21Matrix();
  EXPECT_THROW(A.Transpose(), std::invalid_argument);
}
TEST(Test, Error5) {
  S21Matrix A;
  A.~S21Matrix();

  EXPECT_THROW(A.CalcComplements(), std::invalid_argument);
}
TEST(Test, Error6) {
  S21Matrix A(1, 2);
  EXPECT_THROW(A.InverseMatrix(), std::invalid_argument);
}
TEST(Test, Error7) {
  S21Matrix A;
  S21Matrix B;
  A.~S21Matrix();

  EXPECT_THROW(A.SumMatrix(B), std::invalid_argument);
}
TEST(Test, Error8) {
  S21Matrix A;
  S21Matrix B;
  A.~S21Matrix();

  EXPECT_THROW(A.SubMatrix(B), std::invalid_argument);
}

TEST(Test, Inverse) {
  S21Matrix A(1, 1);
  S21Matrix B(1, 1);
  EXPECT_THROW(B = A.InverseMatrix(), std::invalid_argument);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
