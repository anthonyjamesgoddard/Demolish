#include "Cylinder.h"
#include <iostream>
#include <cassert>
#include <cmath>


namespace {
  constexpr double PI = 3.1415926535897932384626433832795028841972;
}


demolish::primitives::Cylinder::Cylinder(
  iREAL centre[3],
  iREAL radius,
  double minZ,
  double maxZ,
  iREAL h
):
  Cylinder(
    centre[0],
	centre[1],
	centre[2],
	radius,
	minZ,
	maxZ,
	h
  ) {
}


demolish::primitives::Cylinder::Cylinder(
  iREAL centreX,
  iREAL centreY,
  iREAL centreZ,
  iREAL radius,
  iREAL minZ,
  iREAL maxZ,
  iREAL h
):
  _centre{ centreX, centreY, centreZ },
  _radius(radius),
  _h(h),
  _maxZ(maxZ),
  _minZ(minZ),
  _xCoordinates(nullptr),
  _yCoordinates(nullptr),
  _zCoordinates(nullptr) {
  #if DELTA_DEBUG>=1
  std::cout << demolish::getOutputPrefix() << "create sphere around ("
		    << centreX << ","
		    << centreY << ","
		    << "[" << minZ << "," << maxZ << "])^T with radius " << radius << std::endl;
  #endif
  discretise();
}


demolish::primitives::Cylinder::~Cylinder() {
  assert( _xCoordinates!=nullptr );
  assert( _yCoordinates!=nullptr );
  assert( _zCoordinates!=nullptr );

  if (_xCoordinates==nullptr) delete[] _xCoordinates;
  if (_yCoordinates==nullptr) delete[] _yCoordinates;
  if (_zCoordinates==nullptr) delete[] _zCoordinates;
}


iREAL demolish::primitives::Cylinder::getCentreX() const {
  return _centre[0];
}


iREAL demolish::primitives::Cylinder::getCentreY() const {
  return _centre[1];
}


iREAL demolish::primitives::Cylinder::getCentreZ() const {
  return _centre[2];
}


int demolish::primitives::Cylinder::getNumberOfTrianglesPerCircle() const {
  const iREAL surface = 2.0 * PI * _radius;
  return std::max(
	3,
	static_cast<int>( std::floor( surface / _h + 0.5) )
  );
}


int demolish::primitives::Cylinder::getNumberOfTriangles() const {
  return 4*getNumberOfTrianglesPerCircle();
}


iREAL demolish::primitives::Cylinder::getBoundingSphereRadius() const {
  return std::sqrt(_radius*_radius + (_maxZ-_minZ)*(_maxZ-_minZ) );
}


void demolish::primitives::Cylinder::discretise() {
  _xCoordinates = new iREAL[3*getNumberOfTriangles()];
  _yCoordinates = new iREAL[3*getNumberOfTriangles()];
  _zCoordinates = new iREAL[3*getNumberOfTriangles()];

  assert(getNumberOfTriangles()%2==0);

  int tt = 0;

  const double angle = 2.0 * PI / getNumberOfTrianglesPerCircle();
  for (int i=0; i<getNumberOfTrianglesPerCircle(); i++) {
    _xCoordinates[tt] = _centre[0];
    _yCoordinates[tt] = _centre[1];
    _zCoordinates[tt] = _minZ;
    tt++;

    _xCoordinates[tt] = _centre[0] + _radius * std::cos( i*angle );
    _yCoordinates[tt] = _centre[1] + _radius * std::sin( i*angle );
    _zCoordinates[tt] = _minZ;
    tt++;

    _xCoordinates[tt] = _centre[0] + _radius * std::cos( (i+1)*angle );
    _yCoordinates[tt] = _centre[1] + _radius * std::sin( (i+1)*angle );
    _zCoordinates[tt] = _minZ;
    tt++;

    _xCoordinates[tt] = _centre[0];
    _yCoordinates[tt] = _centre[1];
    _zCoordinates[tt] = _maxZ;
    tt++;

    _xCoordinates[tt] = _centre[0] + _radius * std::cos( i*angle );
    _yCoordinates[tt] = _centre[1] + _radius * std::sin( i*angle );
    _zCoordinates[tt] = _maxZ;
    tt++;

    _xCoordinates[tt] = _centre[0] + _radius * std::cos( (i+1)*angle );
    _yCoordinates[tt] = _centre[1] + _radius * std::sin( (i+1)*angle );
    _zCoordinates[tt] = _maxZ;
    tt++;
  }

  for (int i=0; i<getNumberOfTrianglesPerCircle(); i++) {
    _xCoordinates[tt] = _centre[0] + _radius * std::cos( i*angle );
    _yCoordinates[tt] = _centre[1] + _radius * std::sin( i*angle );
    _zCoordinates[tt] = _minZ;
    tt++;

    _xCoordinates[tt] = _centre[0] + _radius * std::cos( (i+1)*angle );
    _yCoordinates[tt] = _centre[1] + _radius * std::sin( (i+1)*angle );
    _zCoordinates[tt] = _minZ;
    tt++;

    _xCoordinates[tt] = _centre[0] + _radius * std::cos( i*angle );
    _yCoordinates[tt] = _centre[1] + _radius * std::sin( i*angle );
    _zCoordinates[tt] = _maxZ;
    tt++;


    _xCoordinates[tt] = _centre[0] + _radius * std::cos( (i+1)*angle );
    _yCoordinates[tt] = _centre[1] + _radius * std::sin( (i+1)*angle );
    _zCoordinates[tt] = _minZ;
    tt++;

    _xCoordinates[tt] = _centre[0] + _radius * std::cos( i*angle );
    _yCoordinates[tt] = _centre[1] + _radius * std::sin( i*angle );
    _zCoordinates[tt] = _maxZ;
    tt++;

    _xCoordinates[tt] = _centre[0] + _radius * std::cos( (i+1)*angle );
    _yCoordinates[tt] = _centre[1] + _radius * std::sin( (i+1)*angle );
    _zCoordinates[tt] = _maxZ;
    tt++;
  }
  assert(tt==3*getNumberOfTriangles());
}


const iREAL* demolish::primitives::Cylinder::getXCoordinates() const {
  assert( _xCoordinates!=nullptr );
  assert( _yCoordinates!=nullptr );
  assert( _zCoordinates!=nullptr );
  return _xCoordinates;
}


const iREAL* demolish::primitives::Cylinder::getYCoordinates() const {
  assert( _xCoordinates!=nullptr );
  assert( _yCoordinates!=nullptr );
  assert( _zCoordinates!=nullptr );
  return _yCoordinates;
}


const iREAL* demolish::primitives::Cylinder::getZCoordinates() const {
  assert( _xCoordinates!=nullptr );
  assert( _yCoordinates!=nullptr );
  assert( _zCoordinates!=nullptr );
  return _zCoordinates;
}

