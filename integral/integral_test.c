#include "integral.h"

double square(double x) { return x * x; }

double constant(double x) {
  (void)x;
  return 2.0;
}

double reciprocal(double x) { return 1.0 / x; }

void test_integral_sin() {
  double result = integral(0, 1, 10000, sin);
  assert(fabs(result - 0.4596977) < 1e-6);
}
void test_integral_square_1() {
  double result = integral(0, 1, 10000, square);
  assert(fabs(result - 0.3333333) < 1e-6);
}
void test_integral_square_2() {
  double result = integral(1, 0, 10000, square);
  assert(fabs(result - (-0.3333333)) < 1e-6);
}
void test_integral_constant() {
  double result = integral(0, 5, 10000, constant);
  assert(fabs(result - 10.0) < 1e-6);
}
void test_integral_reciprocal() {
  double result = integral(1, 2, 10000, reciprocal);
  assert(fabs(result - 0.6931472) < 1e-6);
}

int main() {
  test_integral_sin();
  test_integral_square_1();
  test_integral_square_2();
  test_integral_constant();
  test_integral_reciprocal();

  return 0;
}
