#include"../ContactPoint.h"
#include"sphere.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <limits>
#include <array>

#ifndef _DELTA_FORCES_H_
#define _DELTA_FORCES_H_

#define NNMUL(A, B, C)\
{\
 (C) [0] = (A)[0]*(B)[0]+(A)[3]*(B)[1]+(A)[6]*(B)[2];\
 (C) [1] = (A)[1]*(B)[0]+(A)[4]*(B)[1]+(A)[7]*(B)[2];\
 (C) [2] = (A)[2]*(B)[0]+(A)[5]*(B)[1]+(A)[8]*(B)[2];\
 (C) [3] = (A)[0]*(B)[3]+(A)[3]*(B)[4]+(A)[6]*(B)[5];\
 (C) [4] = (A)[1]*(B)[3]+(A)[4]*(B)[4]+(A)[7]*(B)[5];\
 (C) [5] = (A)[2]*(B)[3]+(A)[5]*(B)[4]+(A)[8]*(B)[5];\
 (C) [6] = (A)[0]*(B)[6]+(A)[3]*(B)[7]+(A)[6]*(B)[8];\
 (C) [7] = (A)[1]*(B)[6]+(A)[4]*(B)[7]+(A)[7]*(B)[8];\
 (C) [8] = (A)[2]*(B)[6]+(A)[5]*(B)[7]+(A)[8]*(B)[8];\
}

namespace crashr {
	namespace resolution {
	  void spring(
		  double normal[3],
		  double conpnt[3],
		  double depth,
		  double vij[3],
		  double positionASpatial[3],
		  double positionBSpatial[3],
		  double positionAReferential[3],
		  double positionBReferential[3],

		  double massA,
		  double massB,
		  double rotationA[9],
		  double rotationB[9],
		  double inverseA[9],
		  double inverseB[9],
		  std::array<double, 3>& f,
		  double &forc);

	  void friction(
		  double normal[3],
		  double vi[3],
		  double force,
		  std::array<double,3>& friction,
		  int materialA,
		  int materialB,
		  bool isSphere);

	  void getContactForces(
		crashr::ContactPoint &conpnt,
		double positionASpatial[3],
		double positionAReferential[3],
		double angularA[3],
		double linearA[3],
		double massA,
		double inverseA[9],
		double rotationA[9],
		int   materialA,

		double positionB[3],
		double positionBReferential[3],
		double angularB[3],
		double linearB[3],
		double massB,
		double inverseB[9],
		double rotationB[9],
		int   materialB,

		std::array<double, 3> &f ,
		std::array<double, 3> &torque,
		bool  isSphere);

	}
}


#endif
