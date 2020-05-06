/*
 See LICENSE file in root of repository

 Authors: Konstantinos Krestenitis, Tobias Weinzierl
 */
#ifndef _DELTA_PRIMITIVES_CYLINDER_H_
#define _DELTA_PRIMITIVES_CYLINDER_H_


#include "../demolish.h"
#include "../Mesh.h"


namespace demolish {
  namespace primitives {
    class Cylinder;
  }
}


/**
 * A cylinder
 *
 */
class demolish::primitives::Cylinder: public demolish::Mesh {
  private:
	const iREAL _centre[3];
	const iREAL _radius;
	const iREAL _h;
	const iREAL _maxZ;
	const iREAL _minZ;

	iREAL* _xCoordinates;
	iREAL* _yCoordinates;
	iREAL* _zCoordinates;

	/**
	 * @image html Cylinder.png
	 */
	void discretise();

    int getNumberOfTrianglesPerCircle() const;
  public:
	/**
	 * Uses C++14's constructor delegation.
	 *
	 * @see Cylinder()
	  double minZ = -1.0,
	  double maxZ =  1.0,
	 */
	Cylinder(
	  iREAL centre[3],
	  iREAL radius,
	  iREAL minZ,
	  iREAL maxZ,
	  iREAL h
    );

	Cylinder(
	  iREAL centreX,
	  iREAL centreY,
	  iREAL centreZ,
	  iREAL radius,
	  iREAL minZ,
	  iREAL maxZ,
	  iREAL h
    );

	virtual ~Cylinder();

	iREAL getCentreX() const  ;
	iREAL getCentreY() const  ;
	iREAL getCentreZ() const  ;

	iREAL getBoundingSphereRadius() const  ;

	/**
	 * You need at least three lines to approximate a circle. Lets assume
	 * that we have k lines to approximate a circle. Per line, we need two
	 * triangles to span a rectangular face.
	 *
	 * @image html Cylinder.png
	 */
	int getNumberOfTriangles() const  ;
	const iREAL* getXCoordinates() const  ;
	const iREAL* getYCoordinates() const  ;
	const iREAL* getZCoordinates() const  ;
};


#endif

