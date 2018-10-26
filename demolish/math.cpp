#include "math.h"
#include <cmath>



iREAL demolish::dot(iREAL a[3], iREAL b[3]) {
  return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}


void demolish::cross(iREAL a[3], iREAL b[3], iREAL result[3]) {
  result[0] = a[1] * b[2] - a[2] * b[1];
  result[1] = a[2] * b[0] - a[0] * b[2];
  result[2] = a[0] * b[1] - a[1] * b[0];
}


iREAL demolish::det(iREAL col0[3], iREAL col1[3], iREAL col2[3]) {
  return col0[0] * (col1[1] * col2[2] - col1[2] * col2[1]) -
		 col1[0] * (col0[1] * col2[2] - col2[1] * col0[2]) +
		 col2[0] * (col0[1] * col1[2] - col1[1] * col0[2]);
}


void demolish::invert(iREAL col0[3], iREAL col1[3], iREAL col2[3] ) {
  iREAL incol0[] = {col0[0],col0[1],col0[2]};
  iREAL incol1[] = {col1[0],col1[1],col1[2]};
  iREAL incol2[] = {col2[0],col2[1],col2[2]};

  iREAL invdet = 1 / det(col0,col1,col2);

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


void demolish::mult(iREAL col0[3], iREAL col1[3], iREAL col2[3], iREAL x[3], iREAL result[3]) {
  result[0] = col0[0] * x[0] + col1[0] * x[1] + col2[0]*x[2];
  result[1] = col0[1] * x[0] + col1[1] * x[1] + col2[1]*x[2];
  result[2] = col0[2] * x[0] + col1[2] * x[1] + col2[2]*x[2];
}


void demolish::normalise(iREAL x[3]) {
  iREAL length = std::sqrt( dot(x,x) );

  x[0] /= length;
  x[1] /= length;
  x[2] /= length;
}
