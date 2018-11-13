#include "../ContactPoint.h"
#include <vector>
#include <limits>
#include <float.h>
#include "../algo.h"


namespace demolish {
    namespace detection {
	  std::vector<demolish::ContactPoint> penalty(
		const iREAL*    xCoordinatesOfPointsOfGeometryA,
		const iREAL*    yCoordinatesOfPointsOfGeometryA,
		const iREAL*    zCoordinatesOfPointsOfGeometryA,
		const int       numberOfTrianglesOfGeometryA,
		const iREAL     epsilonA,
		const bool      frictionA,
		const int 	    particleA,

		const iREAL*    xCoordinatesOfPointsOfGeometryB,
		const iREAL*    yCoordinatesOfPointsOfGeometryB,
		const iREAL*    zCoordinatesOfPointsOfGeometryB,
		const int       numberOfTrianglesOfGeometryB,
		const iREAL     epsilonB,
		const bool      frictionB,
		const int       particleB
		);

	  void penaltySolver(
		const iREAL			*xCoordinatesOfTriangleA,
		const iREAL			*yCoordinatesOfTriangleA,
		const iREAL			*zCoordinatesOfTriangleA,
		const iREAL			*xCoordinatesOfTriangleB,
		const iREAL			*yCoordinatesOfTriangleB,
		const iREAL			*zCoordinatesOfTriangleB,
		iREAL&				xPA,
		iREAL&				yPA,
		iREAL&				zPA,
		iREAL&				xPB,
		iREAL&				yPB,
		iREAL&				zPB,
		iREAL				maxError,
		int&          		numberOfNewtonIterationsRequired);
	}
}
