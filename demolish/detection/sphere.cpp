#include "sphere.h"

std::vector<demolish::ContactPoint> demolish::detection::spherewithsphere(
  const iREAL   xCoordinatesOfPointsOfGeometryA,
  const iREAL   yCoordinatesOfPointsOfGeometryA,
  const iREAL   zCoordinatesOfPointsOfGeometryA,
  const iREAL   radA,
  const iREAL   epsilonA,
  const bool    frictionA,
  const int 	  	particleA,

  const iREAL   xCoordinatesOfPointsOfGeometryB,
  const iREAL   yCoordinatesOfPointsOfGeometryB,
  const iREAL   zCoordinatesOfPointsOfGeometryB,
  const iREAL   radB,
  const iREAL   epsilonB,
  const bool    frictionB,
  const int 	  	particleB)
{
  std::vector<demolish::ContactPoint> result;

  iREAL distance = std::sqrt(((xCoordinatesOfPointsOfGeometryB-xCoordinatesOfPointsOfGeometryA)*(xCoordinatesOfPointsOfGeometryB-xCoordinatesOfPointsOfGeometryA))+((yCoordinatesOfPointsOfGeometryB-yCoordinatesOfPointsOfGeometryA)*(yCoordinatesOfPointsOfGeometryB-yCoordinatesOfPointsOfGeometryA))+((zCoordinatesOfPointsOfGeometryB-zCoordinatesOfPointsOfGeometryA)*(zCoordinatesOfPointsOfGeometryB-zCoordinatesOfPointsOfGeometryA)));

  if(distance>radA+radB+epsilonA+epsilonB)
  {
      return result;
  }
  iREAL xd = xCoordinatesOfPointsOfGeometryB - xCoordinatesOfPointsOfGeometryA;
  iREAL yd = yCoordinatesOfPointsOfGeometryB - yCoordinatesOfPointsOfGeometryA;
  iREAL zd = zCoordinatesOfPointsOfGeometryB - zCoordinatesOfPointsOfGeometryA;

  iREAL xnormal = (1.0/distance) * xd;
  iREAL ynormal = (1.0/distance) * yd;
  iREAL znormal = (1.0/distance) * zd;

  iREAL xPA = xCoordinatesOfPointsOfGeometryA + (radA * xnormal);
  iREAL yPA = yCoordinatesOfPointsOfGeometryA + (radA * ynormal);
  iREAL zPA = zCoordinatesOfPointsOfGeometryA + (radA * znormal);

  iREAL xPB = xCoordinatesOfPointsOfGeometryB - (radB * xnormal);
  iREAL yPB = yCoordinatesOfPointsOfGeometryB - (radB * ynormal);
  iREAL zPB = zCoordinatesOfPointsOfGeometryB - (radB * znormal);

  bool outside = false;
  demolish::ContactPoint newContactPoint(xPA, yPA, zPA, xPB, yPB, zPB,outside);

  result.push_back( newContactPoint );
}
