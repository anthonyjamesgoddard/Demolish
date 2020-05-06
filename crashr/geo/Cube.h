/*
 See LICENSE file in root of repository

 Authors: Konstantinos Krestenitis, Tobias Weinzierl
 */
#ifndef _DELTA_PRIMITIVES_CUBE_H_
#define _DELTA_PRIMITIVES_CUBE_H_


#include "../demolish.h"
#include "../Mesh.h"


namespace demolish {
  namespace primitives {
    class Cube;
  }
}


/**
 * A cube
 */
class demolish::primitives::Cube: public demolish::Mesh {
  private:
	const iREAL _centre[3];
	const iREAL _h;

	iREAL* _xCoordinates;
	iREAL* _yCoordinates;
	iREAL* _zCoordinates;

	void discretise();
  public:
	/**
	 * Uses C++14's constructor delegation.
	 *
	 */
	Cube(
	  iREAL centre[3],
	  iREAL h
    );

	Cube(
	  iREAL centreX,
	  iREAL centreY,
	  iREAL centreZ,
	  iREAL h
    );

	virtual ~Cube();

	iREAL getCentreX() const  ;
	iREAL getCentreY() const  ;
	iREAL getCentreZ() const  ;

	iREAL getBoundingSphereRadius() const  ;

	int getNumberOfTriangles() const  ;
	const iREAL* getXCoordinates() const  ;
	const iREAL* getYCoordinates() const  ;
	const iREAL* getZCoordinates() const  ;
};


#endif

