

#ifndef DELTA_CONTACT_DETECTION_POINT_H_
#define DELTA_CONTACT_DETECTION_POINT_H_

#include "../ContactPoint.h"
#include<vector>

namespace demolish{
	namespace detection {

	std::vector<demolish::ContactPoint> pointToGeometry(
		iREAL   xCoordinatesOfPointOfGeometryA,
		iREAL   yCoordinatesOfPointOfGeometryA,
		iREAL   zCoordinatesOfPointOfGeometryA,
		int 		particleA,
		iREAL   epsilonA,

		const iREAL   *xCoordinatesOfPointsOfGeometryB,
		const iREAL   *yCoordinatesOfPointsOfGeometryB,
		const iREAL   *zCoordinatesOfPointsOfGeometryB,
		int   			numberOfTrianglesOfGeometryB,
		int				particleB,
		iREAL   			epsilonB);

	iREAL pt(iREAL TP1[3], iREAL TP2[3], iREAL TP3[3], iREAL cPoint[3], iREAL tq[3]);

	} 
} 

#endif 
