

#ifndef DEMOLISH_CONTACT_DETECTION_POINT_H_
#define DEMOLISH_CONTACT_DETECTION_POINT_H_

#include "../ContactPoint.h"
#include<vector>

namespace crashr{
	namespace detection {

	std::vector<crashr::ContactPoint> pointToGeometry(
		double   xCoordinatesOfPointOfGeometryA,
		double   yCoordinatesOfPointOfGeometryA,
		double   zCoordinatesOfPointOfGeometryA,
		int 		particleA,
		double   epsilonA,

		const double   *xCoordinatesOfPointsOfGeometryB,
		const double   *yCoordinatesOfPointsOfGeometryB,
		const double   *zCoordinatesOfPointsOfGeometryB,
		int   			numberOfTrianglesOfGeometryB,
		int				particleB,
		double   			epsilonB);

	double pt(double TP1[3], double TP2[3], double TP3[3], double cPoint[3], double tq[3]);

	} 
} 

#endif 
