#include <assert.h>
#include <math.h>
#include <stdio.h>

#define ERROR_LINEAR_EQUATION -1
#define ERROR_NO_REAL_ROOTS -2

int root(double a, double b, double c, double *roots, int *num_roots,
         double eps);
