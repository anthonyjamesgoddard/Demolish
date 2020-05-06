#include "Sphere.h"
#include <iostream>
#include <cassert>


demolish::primitives::Sphere::Sphere(
  iREAL centre[3],
  iREAL radius,
  iREAL h
):
  Sphere(
    centre[0], centre[1], centre[2],
	radius, h
  ) {
}


demolish::primitives::Sphere::Sphere(
  iREAL centreX,
  iREAL centreY,
  iREAL centreZ,
  iREAL radius,
  iREAL h
):
  _centre{ centreX, centreY, centreZ },
  _radius(radius) {

  #if DELTA_DEBUG>=1
  std::cout << demolish::getOutputPrefix() << "create sphere around ("
		    << centreX << ","
		    << centreY << ","
		    << centreZ << ")^T with radius " << radius << std::endl;
  #endif
}


iREAL demolish::primitives::Sphere::getCentreX() const {
  return _centre[0];
}


iREAL demolish::primitives::Sphere::getCentreY() const {
  return _centre[1];
}


iREAL demolish::primitives::Sphere::getCentreZ() const {
  return _centre[2];
}


iREAL demolish::primitives::Sphere::getBoundingSphereRadius() const {
  return _radius;
}


int demolish::primitives::Sphere::getNumberOfTriangles() const {
  assert(false);
  return 0;
}


const iREAL* demolish::primitives::Sphere::getXCoordinates() const {
  assert(false);
  return nullptr;
}


const iREAL* demolish::primitives::Sphere::getYCoordinates() const {
  assert(false);
  return nullptr;
}


const iREAL* demolish::primitives::Sphere::getZCoordinates() const {
  assert(false);
  return nullptr;
}

