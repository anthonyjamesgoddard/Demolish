
#ifndef _DEMOLISH_CONTACTPOINT
#define _DEMOLISH_CONTACTPOINT

#include"demolish.h"

#include <string>
#include <cmath>
#include <limits>
#include <cmath>
#include <sstream>

namespace demolish {
  struct ContactPoint;
}


/**
 * Simple struct representing a contact point
 */
struct demolish::ContactPoint {
  /**
   * Position in space
   */
  iREAL 	x[3];

  /**
   * Normal onto next surface. Always normalised.
   */
  iREAL 	normal[3];

  /**
   * Distance to next surface along normal. We use the sign to indicate whether contact
   * point is inside (negative) or outside (positive) of the corresponding
   * shapes.
   */
  iREAL 	distance;

  /**
   * Allows us to tie a contact point to an object via an index
   */
  int 	    indexA;
  int 	    indexB;


  /**
   * Tells us how far the objects have overlapped
   */

  iREAL depth;

  
  bool friction;

  ContactPoint();
  ContactPoint(const ContactPoint& copy);

  /**
   * This constructor is given two points on two triangles that are close to
   * each other. The points are PA and PB. The operation determines the
   * contact point at x,y,z (which is half the distance between the two
   * points PA and PB) and the corresponding normal xN,yN,zN.
   */
  ContactPoint(
    const iREAL&  	xPA,
	const iREAL&  	yPA,
	const iREAL&  	zPA,

	const iREAL&  	xQB,
	const iREAL&  	yQB,
	const iREAL&  	zQB,

    const bool&     outside
  );

  ContactPoint(
    const iREAL PA[3],
	const iREAL QB[3],
    const bool&     outside
  );
    
  ContactPoint(  
    const iREAL&  	xPA,
	const iREAL&  	yPA,
	const iREAL&  	zPA,

	const iREAL&  	xQB,
	const iREAL&  	yQB,
	const iREAL&  	zQB,

    const bool&     outside,

    const iREAL&    epsilonA,
    const iREAL&    epsilonB,
    
    bool            fric);

  ContactPoint(  
    const iREAL&  	xPA,
	const iREAL&  	yPA,
	const iREAL&  	zPA,

	const iREAL&  	xQB,
	const iREAL&  	yQB,
	const iREAL&  	zQB,

    const bool&     outside,

    const iREAL&     epsilonA,
    const iREAL&     epsilonB,

    const int        particleA,
    const int        particleB,

    bool             fric
    );

};

#endif
