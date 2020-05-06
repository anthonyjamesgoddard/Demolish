#include "Sphere.h"
#include <iostream>
#include <cassert>


crashr::primitives::Sphere::Sphere(
  double centre[3],
  double radius,
  double h
):
  Sphere(
    centre[0], centre[1], centre[2],
	radius, h
  ) {
}


crashr::primitives::Sphere::Sphere(
  double centreX,
  double centreY,
  double centreZ,
  double radius,
  double h
):
  _centre{ centreX, centreY, centreZ },
  _radius(radius) {

  #if DEBUG>=1
  std::cout << crashr::getOutputPrefix() << "create sphere around ("
		    << centreX << ","
		    << centreY << ","
		    << centreZ << ")^T with radius " << radius << std::endl;
  #endif
}


double crashr::primitives::Sphere::getCentreX() const {
  return _centre[0];
}


double crashr::primitives::Sphere::getCentreY() const {
  return _centre[1];
}


double crashr::primitives::Sphere::getCentreZ() const {
  return _centre[2];
}


double crashr::primitives::Sphere::getBoundingSphereRadius() const {
  return _radius;
}


int crashr::primitives::Sphere::getNumberOfTriangles() const {
  assert(false);
  return 0;
}


const double* crashr::primitives::Sphere::getXCoordinates() const {
  assert(false);
  return nullptr;
}


const double* crashr::primitives::Sphere::getYCoordinates() const {
  assert(false);
  return nullptr;
}


const double* crashr::primitives::Sphere::getZCoordinates() const {
  assert(false);
  return nullptr;
}

