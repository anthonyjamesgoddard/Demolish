#pragma once
#include "geo/vertex.h"

namespace crashr {
/**
 * Dot product
 */
double dot(double a[3], double b[3]);

/**
 * Cross product
 */
void cross(double a[3], double b[3], double result[3]);

Vertex cross(Vertex a, Vertex b);

/**
 * Solves a 3x3 product via direct inversion. The matrix is given
 * column-wise. The column entries are changed in-situ.
 */
void invert(double col0[3], double col1[3], double col2[3]);

/**
 * Determinant. Matrix is given column-wisely.
 */
double det(double col0[3], double col1[3], double col2[3]);

/**
 * Multiply a matrix given by its columns with a vector.
 */
void mult(double col0[3], double col1[3], double col2[3], double x[3],
          double result[3]);

void normalise(double x[3]);
}  // namespace crashr
