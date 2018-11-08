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

  bool outside = true;
  if(distance<radA + radB) outside = false;
  demolish::ContactPoint newContactPoint(xPA, yPA, zPA, xPB, yPB, zPB,outside);
  newContactPoint.indexA = particleA;
  newContactPoint.indexB = particleB;
  result.push_back( newContactPoint );
  return result;
}


std::vector<demolish::ContactPoint> demolish::detection::sphereWithMesh(
  iREAL   xCoordinatesOfPointsOfGeometryA,
  iREAL   yCoordinatesOfPointsOfGeometryA,
  iREAL   zCoordinatesOfPointsOfGeometryA,
  iREAL   radA,
  iREAL   epsilonA,
  bool    frictionA,
  int 	  particleA,

  const iREAL   *xCoordinatesOfPointsOfGeometryB,
  const iREAL   *yCoordinatesOfPointsOfGeometryB,
  const iREAL   *zCoordinatesOfPointsOfGeometryB,
  int   			numberOfTrianglesOfGeometryB,
  iREAL   		epsilonB,
  bool    		frictionB,
  int 			particleB)
{
  std::vector<demolish::ContactPoint> result;

  for(int i=0; i<numberOfTrianglesOfGeometryB*3; i+=3)
  {
	iREAL P[3], Q[3];
	iREAL xPA, yPA, zPA, xPB, yPB, zPB;

	iREAL TP1[3], TP2[3], TP3[3];
	TP1[0] = xCoordinatesOfPointsOfGeometryB[i];
	TP1[1] = yCoordinatesOfPointsOfGeometryB[i];
	TP1[2] = zCoordinatesOfPointsOfGeometryB[i];

	TP2[0] = xCoordinatesOfPointsOfGeometryB[i+1];
	TP2[1] = yCoordinatesOfPointsOfGeometryB[i+1];
	TP2[2] = zCoordinatesOfPointsOfGeometryB[i+1];

	TP3[0] = xCoordinatesOfPointsOfGeometryB[i+2];
	TP3[1] = yCoordinatesOfPointsOfGeometryB[i+2];
	TP3[2] = zCoordinatesOfPointsOfGeometryB[i+2];

	P[0] = xCoordinatesOfPointsOfGeometryA;
	P[1] = yCoordinatesOfPointsOfGeometryA;
	P[2] = zCoordinatesOfPointsOfGeometryA;

   // std::cout << TP1[0] << " " << TP1[1] << " " << TP1[2] << std::endl;
   // std::cout << TP2[0] << " " << TP2[1] << " " << TP2[2] << std::endl;
   // std::cout << TP3[0] << " " << TP3[1] << " " << TP3[2] << std::endl;
	iREAL distance = demolish::detection::pt(TP1, TP2, TP3, P, Q) - radA;
    if(distance > epsilonA + epsilonB) continue;
    //std::cout << distance << std::endl;
	iREAL xnormal = (Q[0] - P[0])/(distance+radA);
	iREAL ynormal = (Q[1] - P[1])/(distance+radA);
	iREAL znormal = (Q[2] - P[2])/(distance+radA);

	xPA = P[0] + (radA * xnormal);
	yPA = P[1] + (radA * ynormal);
	zPA = P[2] + (radA * znormal);

	xPB = Q[0];
	yPB = Q[1];
	zPB = Q[2];

    bool outside = true;
    if(distance <0) outside = false;
	demolish::ContactPoint newContactPoint(xPA,yPA, zPA,
                                    xPB, yPB, zPB,
                                    outside);
    

    newContactPoint.indexA = particleA;
    newContactPoint.indexB = particleB;
    result.push_back( newContactPoint );
	
  }
  return result;
}
