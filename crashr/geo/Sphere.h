/*
 See LICENSE file in root of repository

 Authors: Konstantinos Krestenitis, Tobias Weinzierl
 */
#ifndef _DELTA_PRIMITIVES_SPHERE_H_
#define _DELTA_PRIMITIVES_SPHERE_H_


#include "../demolish.h"
#include "../Mesh.h"


namespace demolish {
  namespace primitives {
    class Sphere;
  }
}



class demolish::primitives::Sphere: public demolish::Mesh {
  private:
	iREAL _centre[3];
	iREAL _radius;

  public:
	Sphere(
	  iREAL centre[3],
	  iREAL radius,
	  iREAL h
    );

	Sphere(
	  iREAL centreX,
	  iREAL centreY,
	  iREAL centreZ,
	  iREAL radius,
	  iREAL h
    );

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

