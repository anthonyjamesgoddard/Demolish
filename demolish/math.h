
#ifndef _DEMOLISH_MATH
#define _DEMOLISH_MATH


#include "demolish.h"


namespace demolish {
  /**
   * Dot product
   */
  iREAL dot(iREAL a[3], iREAL b[3]);

  /**
   * Cross product
   */
  void cross(iREAL a[3], iREAL b[3], iREAL result[3]);

  /**
   * Solves a 3x3 product via direct inversion. The matrix is given
   * column-wise. The column entries are changed in-situ.
   */
  void invert(iREAL col0[3], iREAL col1[3], iREAL col2[3]);

  /**
   * Determinant. Matrix is given column-wisely.
   */
  iREAL det(iREAL col0[3], iREAL col1[3], iREAL col2[3]);

  /**
   * Multiply a matrix given by its columns with a vector.
   */
  void mult(iREAL col0[3], iREAL col1[3], iREAL col2[3], iREAL x[3], iREAL result[3]);

  void normalise(iREAL x[3]);
}

#endif
