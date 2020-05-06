#include <vector>
#include <complex>
#include <limits>
#include <iostream>

#include "../ContactPoint.h"
#include "point.h"
namespace crashr {
	namespace detection {
	  std::vector<crashr::ContactPoint> spherewithsphere(
		const double   xCoordinatesOfPointsOfGeometryA,
		const double   yCoordinatesOfPointsOfGeometryA,
		const double   zCoordinatesOfPointsOfGeometryA,
		const double   radB,
		const double   epsilonA,
		const bool    frictionA,
		const int 	  particleA,

		const double   xCoordinatesOfPointsOfGeometryB,
		const double   yCoordinatesOfPointsOfGeometryB,
		const double   zCoordinatesOfPointsOfGeometryB,
		const double   radA,
		const double   epsilonB,
		const bool    frictionB,
		const int 	  particleB
		);
    
      std::vector<crashr::ContactPoint> sphereWithMesh(
		const double   xCoordinatesOfPointsOfGeometryA,
		const double   yCoordinatesOfPointsOfGeometryA,
		const double   zCoordinatesOfPointsOfGeometryA,
		const double   radA,
		const double   epsilonA,
		const bool    frictionA,
		const int	  particleA,

		const double   *xCoordinatesOfPointsOfGeometryB,
		const double   *yCoordinatesOfPointsOfGeometryB,
		const double   *zCoordinatesOfPointsOfGeometryB,
		const int	  numberOfTrianglesOfGeometryB,
		const double   epsilonB,
		const bool 	  frictionB,
		const int 	  particleB
		);

    }
}
