#include "Cube.h"
#include <iostream>
#include <cassert>
#include <cmath>


demolish::primitives::Cube::Cube(
  iREAL centre[3],
  iREAL h
):
  Cube(
    centre[0],
	centre[1],
	centre[2],
	h
  ) {
}


demolish::primitives::Cube::Cube(
  iREAL centreX,
  iREAL centreY,
  iREAL centreZ,
  iREAL h
):
  _centre{ centreX, centreY, centreZ },
  _h(h),
  _xCoordinates(nullptr),
  _yCoordinates(nullptr),
  _zCoordinates(nullptr) {
  #if DELTA_DEBUG>=1
  std::cout << demolish::getOutputPrefix() << "create cube around ("
		    << centreX << ","
		    << centreY << ","
		    << " with h=" << h << std::endl;
  #endif
  discretise();
}


demolish::primitives::Cube::~Cube() {
  assert( _xCoordinates!=nullptr );
  assert( _yCoordinates!=nullptr );
  assert( _zCoordinates!=nullptr );

  if (_xCoordinates==nullptr) delete[] _xCoordinates;
  if (_yCoordinates==nullptr) delete[] _yCoordinates;
  if (_zCoordinates==nullptr) delete[] _zCoordinates;
}


iREAL demolish::primitives::Cube::getCentreX() const {
  return _centre[0];
}


iREAL demolish::primitives::Cube::getCentreY() const {
  return _centre[1];
}


iREAL demolish::primitives::Cube::getCentreZ() const {
  return _centre[2];
}


int demolish::primitives::Cube::getNumberOfTriangles() const {
  return 2*6;
}


iREAL demolish::primitives::Cube::getBoundingSphereRadius() const {
  return std::sqrt(3)*_h;
}


void demolish::primitives::Cube::discretise() {
  _xCoordinates = new iREAL[3*getNumberOfTriangles()];
  _yCoordinates = new iREAL[3*getNumberOfTriangles()];
  _zCoordinates = new iREAL[3*getNumberOfTriangles()];

  // front side
  _xCoordinates[0] = _centre[0] - _h/2;
  _yCoordinates[0] = _centre[1] - _h/2;
  _zCoordinates[0] = _centre[2] - _h/2;

  _xCoordinates[1] = _centre[0] + _h/2;
  _yCoordinates[1] = _centre[1] - _h/2;
  _zCoordinates[1] = _centre[2] - _h/2;

  _xCoordinates[2] = _centre[0] + _h/2;
  _yCoordinates[2] = _centre[1] + _h/2;
  _zCoordinates[2] = _centre[2] - _h/2;

  _xCoordinates[3] = _centre[0] - _h/2;
  _yCoordinates[3] = _centre[1] - _h/2;
  _zCoordinates[3] = _centre[2] - _h/2;

  _xCoordinates[4] = _centre[0] + _h/2;
  _yCoordinates[4] = _centre[1] + _h/2;
  _zCoordinates[4] = _centre[2] - _h/2;

  _xCoordinates[5] = _centre[0] - _h/2;
  _yCoordinates[5] = _centre[1] + _h/2;
  _zCoordinates[5] = _centre[2] - _h/2;

  // back side
  _xCoordinates[6] = _centre[0] - _h/2;
  _yCoordinates[6] = _centre[1] - _h/2;
  _zCoordinates[6] = _centre[2] + _h/2;

  _xCoordinates[7] = _centre[0] + _h/2;
  _yCoordinates[7] = _centre[1] - _h/2;
  _zCoordinates[7] = _centre[2] + _h/2;

  _xCoordinates[8] = _centre[0] + _h/2;
  _yCoordinates[8] = _centre[1] + _h/2;
  _zCoordinates[8] = _centre[2] + _h/2;

  _xCoordinates[9] = _centre[0] - _h/2;
  _yCoordinates[9] = _centre[1] - _h/2;
  _zCoordinates[9] = _centre[2] + _h/2;

  _xCoordinates[10] = _centre[0] + _h/2;
  _yCoordinates[10] = _centre[1] + _h/2;
  _zCoordinates[10] = _centre[2] + _h/2;

  _xCoordinates[11] = _centre[0] - _h/2;
  _yCoordinates[11] = _centre[1] + _h/2;
  _zCoordinates[11] = _centre[2] + _h/2;

  // left side
  _xCoordinates[12] = _centre[0] - _h/2;
  _yCoordinates[12] = _centre[1] - _h/2;
  _zCoordinates[12] = _centre[2] - _h/2;

  _xCoordinates[13] = _centre[0] - _h/2;
  _yCoordinates[13] = _centre[1] - _h/2;
  _zCoordinates[13] = _centre[2] + _h/2;

  _xCoordinates[14] = _centre[0] - _h/2;
  _yCoordinates[14] = _centre[1] + _h/2;
  _zCoordinates[14] = _centre[2] + _h/2;

  _xCoordinates[15] = _centre[0] - _h/2;
  _yCoordinates[15] = _centre[1] - _h/2;
  _zCoordinates[15] = _centre[2] - _h/2;

  _xCoordinates[16] = _centre[0] - _h/2;
  _yCoordinates[16] = _centre[1] + _h/2;
  _zCoordinates[16] = _centre[2] + _h/2;

  _xCoordinates[17] = _centre[0] - _h/2;
  _yCoordinates[17] = _centre[1] + _h/2;
  _zCoordinates[17] = _centre[2] - _h/2;

  // right side
  _xCoordinates[18] = _centre[0] + _h/2;
  _yCoordinates[18] = _centre[1] - _h/2;
  _zCoordinates[18] = _centre[2] - _h/2;

  _xCoordinates[19] = _centre[0] + _h/2;
  _yCoordinates[19] = _centre[1] - _h/2;
  _zCoordinates[19] = _centre[2] + _h/2;

  _xCoordinates[20] = _centre[0] + _h/2;
  _yCoordinates[20] = _centre[1] + _h/2;
  _zCoordinates[20] = _centre[2] + _h/2;

  _xCoordinates[21] = _centre[0] + _h/2;
  _yCoordinates[21] = _centre[1] - _h/2;
  _zCoordinates[21] = _centre[2] - _h/2;

  _xCoordinates[22] = _centre[0] + _h/2;
  _yCoordinates[22] = _centre[1] + _h/2;
  _zCoordinates[22] = _centre[2] + _h/2;

  _xCoordinates[23] = _centre[0] + _h/2;
  _yCoordinates[23] = _centre[1] + _h/2;
  _zCoordinates[23] = _centre[2] - _h/2;

  // bottom side
  _xCoordinates[24] = _centre[0] - _h/2;
  _yCoordinates[24] = _centre[1] - _h/2;
  _zCoordinates[24] = _centre[2] - _h/2;

  _xCoordinates[25] = _centre[0] + _h/2;
  _yCoordinates[25] = _centre[1] - _h/2;
  _zCoordinates[25] = _centre[2] - _h/2;

  _xCoordinates[26] = _centre[0] + _h/2;
  _yCoordinates[26] = _centre[1] - _h/2;
  _zCoordinates[26] = _centre[2] + _h/2;

  _xCoordinates[27] = _centre[0] - _h/2;
  _yCoordinates[27] = _centre[1] - _h/2;
  _zCoordinates[27] = _centre[2] - _h/2;

  _xCoordinates[28] = _centre[0] + _h/2;
  _yCoordinates[28] = _centre[1] - _h/2;
  _zCoordinates[28] = _centre[2] + _h/2;

  _xCoordinates[29] = _centre[0] - _h/2;
  _yCoordinates[29] = _centre[1] - _h/2;
  _zCoordinates[29] = _centre[2] + _h/2;

  // top side
  _xCoordinates[30] = _centre[0] - _h/2;
  _yCoordinates[30] = _centre[1] + _h/2;
  _zCoordinates[30] = _centre[2] - _h/2;

  _xCoordinates[31] = _centre[0] + _h/2;
  _yCoordinates[31] = _centre[1] + _h/2;
  _zCoordinates[31] = _centre[2] - _h/2;

  _xCoordinates[32] = _centre[0] + _h/2;
  _yCoordinates[32] = _centre[1] + _h/2;
  _zCoordinates[32] = _centre[2] + _h/2;

  _xCoordinates[33] = _centre[0] - _h/2;
  _yCoordinates[33] = _centre[1] + _h/2;
  _zCoordinates[33] = _centre[2] - _h/2;

  _xCoordinates[34] = _centre[0] + _h/2;
  _yCoordinates[34] = _centre[1] + _h/2;
  _zCoordinates[34] = _centre[2] + _h/2;

  _xCoordinates[35] = _centre[0] - _h/2;
  _yCoordinates[35] = _centre[1] + _h/2;
  _zCoordinates[35] = _centre[2] + _h/2;
}


const iREAL* demolish::primitives::Cube::getXCoordinates() const {
  assert( _xCoordinates!=nullptr );
  assert( _yCoordinates!=nullptr );
  assert( _zCoordinates!=nullptr );
  return _xCoordinates;
}


const iREAL* demolish::primitives::Cube::getYCoordinates() const {
  assert( _xCoordinates!=nullptr );
  assert( _yCoordinates!=nullptr );
  assert( _zCoordinates!=nullptr );
  return _yCoordinates;
}


const iREAL* demolish::primitives::Cube::getZCoordinates() const {
  assert( _xCoordinates!=nullptr );
  assert( _yCoordinates!=nullptr );
  assert( _zCoordinates!=nullptr );
  return _zCoordinates;
}

