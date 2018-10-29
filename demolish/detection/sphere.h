#include <vector>
#include <complex>
#include <limits>
#include <iostream>

#include "../ContactPoint.h"

namespace demolish {
	namespace detection {
	  std::vector<demolish::ContactPoint> spherewithsphere(
		const iREAL   xCoordinatesOfPointsOfGeometryA,
		const iREAL   yCoordinatesOfPointsOfGeometryA,
		const iREAL   zCoordinatesOfPointsOfGeometryA,
		const iREAL   radB,
		const iREAL   epsilonA,
		const bool    frictionA,
		const int 	  particleA,

		const iREAL   xCoordinatesOfPointsOfGeometryB,
		const iREAL   yCoordinatesOfPointsOfGeometryB,
		const iREAL   zCoordinatesOfPointsOfGeometryB,
		const iREAL   radA,
		const iREAL   epsilonB,
		const bool    frictionB,
		const int 	  particleB
		);
    }
}
