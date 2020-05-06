#include "math.h"
#include <cmath>



double crashr::dot(double a[3], double b[3]) {
  return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}


void crashr::cross(double a[3], double b[3], double result[3]) {
  result[0] = a[1] * b[2] - a[2] * b[1];
  result[1] = a[2] * b[0] - a[0] * b[2];
  result[2] = a[0] * b[1] - a[1] * b[0];
}


crashr::Vertex crashr::cross(crashr::Vertex a,crashr::Vertex b) {
    double tempres[3];
  tempres[0] = a[1] * b[2] - a[2] * b[1];
  tempres[1] = a[2] * b[0] - a[0] * b[2];
  tempres[2] = a[0] * b[1] - a[1] * b[0];
  return crashr::Vertex(tempres[0],
                tempres[1],
                tempres[2]);

}

double crashr::det(double col0[3], double col1[3], double col2[3]) {
  return col0[0] * (col1[1] * col2[2] - col1[2] * col2[1]) -
		 col1[0] * (col0[1] * col2[2] - col2[1] * col0[2]) +
		 col2[0] * (col0[1] * col1[2] - col1[1] * col0[2]);
}


void crashr::invert(double col0[3], double col1[3], double col2[3] ) {
  double incol0[] = {col0[0],col0[1],col0[2]};
  double incol1[] = {col1[0],col1[1],col1[2]};
  double incol2[] = {col2[0],col2[1],col2[2]};

  double invdet = 1 / det(col0,col1,col2);

  col0[0] = (incol1[1] * incol2[2] - incol1[2] * incol2[1]) * invdet;
  col1[0] = (incol2[0] * incol1[2] - incol1[0] * incol2[2]) * invdet;
  col2[0] = (incol1[0] * incol2[1] - incol2[0] * incol1[1]) * invdet;
  col0[1] = (incol2[1] * incol0[2] - incol0[1] * incol2[2]) * invdet;
  col1[1] = (incol0[0] * incol2[2] - incol2[0] * incol0[2]) * invdet;
  col2[1] = (incol0[1] * incol2[0] - incol0[0] * incol2[1]) * invdet;
  col0[2] = (incol0[1] * incol1[2] - incol0[2] * incol1[1]) * invdet;
  col1[2] = (incol0[2] * incol1[0] - incol0[0] * incol1[2]) * invdet;
  col2[2] = (incol0[0] * incol1[1] - incol0[1] * incol1[0]) * invdet;
}


void crashr::mult(double col0[3], double col1[3], double col2[3], double x[3], double result[3]) {
  result[0] = col0[0] * x[0] + col1[0] * x[1] + col2[0]*x[2];
  result[1] = col0[1] * x[0] + col1[1] * x[1] + col2[1]*x[2];
  result[2] = col0[2] * x[0] + col1[2] * x[1] + col2[2]*x[2];
}


void crashr::normalise(double x[3]) {
  double length = std::sqrt( dot(x,x) );

  x[0] /= length;
  x[1] /= length;
  x[2] /= length;
}
