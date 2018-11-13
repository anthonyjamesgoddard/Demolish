#include "ContactPoint.h"
#include <iostream>
#include <iomanip>

demolish::ContactPoint::ContactPoint() {}

demolish::ContactPoint::ContactPoint(const ContactPoint& copy):
  distance(copy.distance),
  indexA(copy.indexA),
  indexB(copy.indexB) {

  x[0] = copy.x[0];
  x[1] = copy.x[1];
  x[2] = copy.x[2];

  normal[0] = copy.normal[0];
  normal[1] = copy.normal[1];
  normal[2] = copy.normal[2];
}


demolish::ContactPoint::ContactPoint(
  const iREAL PA[3],
  const iREAL QB[3],
  const bool&     outside
):
  ContactPoint(
    PA[0], PA[1], PA[2],
    QB[0], QB[1], QB[2],
	outside
  ) {
}


demolish::ContactPoint::ContactPoint(
  const iREAL&  	xPA,
  const iREAL&  	yPA,
  const iREAL&  	zPA,

  const iREAL&  	xQB,
  const iREAL&  	yQB,
  const iREAL&  	zQB,

  const bool&       outside
):
  indexA(-1),
  indexB(-1) {
  x[0] = (xPA+xQB)/2.0;
  x[1] = (yPA+yQB)/2.0;
  x[2] = (zPA+zQB)/2.0;

  normal[0] = xPA-xQB;
  normal[1] = yPA-yQB;
  normal[2] = zPA-zQB;

  const iREAL normalLength = std::sqrt( normal[0]*normal[0] + normal[1]*normal[1] + normal[2]*normal[2] );

  normal[0] /= normalLength;
  normal[1] /= normalLength;
  normal[2] /= normalLength;

  distance = outside ? normalLength : -normalLength;

  // note that this version of the constructor is useless if we need depth information.
  depth = 0;
  friction = true;
}


demolish::ContactPoint::ContactPoint(
  const iREAL&  	xPA,
  const iREAL&  	yPA,
  const iREAL&  	zPA,

  const iREAL&  	xQB,
  const iREAL&  	yQB,
  const iREAL&  	zQB,

  const bool&       outside,

  const iREAL&      epsilonA,
  const iREAL&      epsilonB,
   bool             fric
):
  indexA(-1),
  indexB(-1) {
  x[0] = (xPA+xQB)/2.0;
  x[1] = (yPA+yQB)/2.0;
  x[2] = (zPA+zQB)/2.0;
    
  friction = fric;
  normal[0] = xPA-xQB;
  normal[1] = yPA-yQB;
  normal[2] = zPA-zQB;

  const iREAL normalLength = std::sqrt( normal[0]*normal[0] + normal[1]*normal[1] + normal[2]*normal[2] );

  normal[0] /= normalLength;
  normal[1] /= normalLength;
  normal[2] /= normalLength;

  distance = outside ? normalLength : -normalLength;

  depth = (epsilonA+epsilonB)-normalLength;
}

demolish::ContactPoint::ContactPoint(
  const iREAL&  	xPA,
  const iREAL&  	yPA,
  const iREAL&  	zPA,

  const iREAL&  	xQB,
  const iREAL&  	yQB,
  const iREAL&  	zQB,

  const bool&       outside,

  const iREAL&      epsilonA,
  const iREAL&      epsilonB,

  const int        &particleA,
  const int        &particleB,

  bool             fric
):
  indexA(particleA),
  indexB(particleB) {
  x[0] = (xPA+xQB)/2.0;
  x[1] = (yPA+yQB)/2.0;
  x[2] = (zPA+zQB)/2.0;

  normal[0] = xPA-xQB;
  normal[1] = yPA-yQB;
  normal[2] = zPA-zQB;

  const iREAL normalLength = std::sqrt( normal[0]*normal[0] + normal[1]*normal[1] + normal[2]*normal[2] );

  friction = fric;
  normal[0] /= normalLength;
  normal[1] /= normalLength;
  normal[2] /= normalLength;

  distance = outside ? normalLength : -normalLength;

  depth = (epsilonA+epsilonB)-normalLength;
}

