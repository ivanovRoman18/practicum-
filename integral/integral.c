#include "integral.h"

double integral(double a, double b, int n, double (*f)(double)) {
  if (n <= 0) {
    return NAN;
  }

  if (f == NULL) {
    return NAN;
  }

  if (a > b) {
    return -integral(b, a, n, f);
  }

  double h = (b - a) / n;
  double sum = 0.5 * (f(a) + f(b));

  for (int i = 1; i < n; i++) {
    double x = a + i * h;
    sum += f(x);
  }

  return sum * h;
}
