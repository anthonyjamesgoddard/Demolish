/*
 See LICENSE file in root of repository

 Authors: Konstantinos Krestenitis, Tobias Weinzierl
 */
#ifndef _DELTA_PRIMITIVES_CYLINDER_H_
#define _DELTA_PRIMITIVES_CYLINDER_H_


#include "../crashr.h"
#include "../Mesh.h"


namespace crashr {
  namespace primitives {
    class Cylinder;
  }
}


/**
 * A cylinder
 *
 */
class crashr::primitives::Cylinder: public crashr::Mesh {
  private:
	const double _centre[3];
	const double _radius;
	const double _h;
	const double _maxZ;
	const double _minZ;

	double* _xCoordinates;
	double* _yCoordinates;
	double* _zCoordinates;

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
	  double centre[3],
	  double radius,
	  double minZ,
	  double maxZ,
	  double h
    );

	Cylinder(
	  double centreX,
	  double centreY,
	  double centreZ,
	  double radius,
	  double minZ,
	  double maxZ,
	  double h
    );

	virtual ~Cylinder();

	double getCentreX() const  ;
	double getCentreY() const  ;
	double getCentreZ() const  ;

	double getBoundingSphereRadius() const  ;

	/**
	 * You need at least three lines to approximate a circle. Lets assume
	 * that we have k lines to approximate a circle. Per line, we need two
	 * triangles to span a rectangular face.
	 *
	 * @image html Cylinder.png
	 */
	int getNumberOfTriangles() const  ;
	const double* getXCoordinates() const  ;
	const double* getYCoordinates() const  ;
	const double* getZCoordinates() const  ;
};


#endif

