#include "../ContactPoint.h"
#include <vector>
#include <limits>
#include <float.h>
#include "../algo.h"


namespace crashr {
    namespace detection {
	  std::vector<crashr::ContactPoint> penalty(
		const double*    xCoordinatesOfPointsOfGeometryA,
		const double*    yCoordinatesOfPointsOfGeometryA,
		const double*    zCoordinatesOfPointsOfGeometryA,
		const int       numberOfTrianglesOfGeometryA,
		const double     epsilonA,
		const bool      frictionA,
		const int 	    particleA,

		const double*    xCoordinatesOfPointsOfGeometryB,
		const double*    yCoordinatesOfPointsOfGeometryB,
		const double*    zCoordinatesOfPointsOfGeometryB,
		const int       numberOfTrianglesOfGeometryB,
		const double     epsilonB,
		const bool      frictionB,
		const int       particleB
		);

	  void penaltySolver(
		const double			*xCoordinatesOfTriangleA,
		const double			*yCoordinatesOfTriangleA,
		const double			*zCoordinatesOfTriangleA,
		const double			*xCoordinatesOfTriangleB,
		const double			*yCoordinatesOfTriangleB,
		const double			*zCoordinatesOfTriangleB,
		double&				xPA,
		double&				yPA,
		double&				zPA,
		double&				xPB,
		double&				yPB,
		double&				zPB,
		double				maxError,
		int&          		numberOfNewtonIterationsRequired);
	}
}
