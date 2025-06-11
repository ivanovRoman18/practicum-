#include "quadratic_equations.h"

void test_root_1() {

  double roots[2];
  int num_roots = 0;
  double eps = 1E-14;

  int result = root(0, 0, 0, roots, &num_roots, eps);
  assert(result == ERROR_LINEAR_EQUATION);
}
void test_root_2() {

  double roots[2];
  int num_roots = 0;
  double eps = 1E-14;

  int result = root(1, 0, -1, roots, &num_roots, eps);

  assert(result == 0);
  assert(num_roots == 2);
  assert(fabs(roots[0] - (-1)) < 1E-7);
  assert(fabs(roots[1] - 1) < 1E-7);
}
void test_root_3() {

  double roots[2];
  int num_roots = 0;
  double eps = 1E-14;

  int result = root(1, 0, 0, roots, &num_roots, eps);

  assert(result == 0);
  assert(num_roots == 1);
  assert((fabs(roots[0] - 0) < 1e-7));
}
void test_root_4() {

  double roots[2];
  int num_roots = 0;
  double eps = 1E-14;

  int result = root(1, 0, 1, roots, &num_roots, eps);
  assert(result == ERROR_NO_REAL_ROOTS);
}
void test_root_5() {

  double roots[2];
  int num_roots = 0;
  double eps = 1E-14;

  int result = root(1, 0, -1E-7, roots, &num_roots, eps);
  assert(result == 0);
  assert(num_roots == 2);
  assert(fabs(roots[0] - (-3E-4)) < 1E-4);
  assert(fabs(roots[1] - 3E-4) < 1E-4);
}
void test_root_6() {

  double roots[2];
  int num_roots = 0;
  double eps = 1E-11;

  int result = root(1, -1E+10, -1, roots, &num_roots, eps);

  assert(result == 0);
  assert(num_roots == 2);
  assert(fabs(roots[0] - (-1E-10)) < eps);
  assert(fabs(roots[1] - 1E+10) < eps);
}
void test_root_7() {

  double roots[2];
  int num_roots = 0;
  double eps = 1E-7;

  int result = root(1, 0, -1E-8, roots, &num_roots, eps);

  assert(result == 0);
  assert(num_roots == 1);
  assert(fabs(roots[0] - 0) < eps);
}

int main() {
  test_root_1();
  test_root_2();
  test_root_3();
  test_root_4();
  test_root_5();
  test_root_6();
  test_root_7();

  return 0;
}
