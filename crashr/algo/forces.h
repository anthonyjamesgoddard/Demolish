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

namespace demolish {
	namespace resolution {
	  void spring(
		  iREAL normal[3],
		  iREAL conpnt[3],
		  iREAL depth,
		  iREAL vij[3],
		  iREAL positionASpatial[3],
		  iREAL positionBSpatial[3],
		  iREAL positionAReferential[3],
		  iREAL positionBReferential[3],

		  iREAL massA,
		  iREAL massB,
		  iREAL rotationA[9],
		  iREAL rotationB[9],
		  iREAL inverseA[9],
		  iREAL inverseB[9],
		  std::array<iREAL, 3>& f,
		  iREAL &forc);

	  void friction(
		  iREAL normal[3],
		  iREAL vi[3],
		  iREAL force,
		  std::array<iREAL,3>& friction,
		  int materialA,
		  int materialB,
		  bool isSphere);

	  void getContactForces(
		demolish::ContactPoint &conpnt,
		iREAL positionASpatial[3],
		iREAL positionAReferential[3],
		iREAL angularA[3],
		iREAL linearA[3],
		iREAL massA,
		iREAL inverseA[9],
		iREAL rotationA[9],
		int   materialA,

		iREAL positionB[3],
		iREAL positionBReferential[3],
		iREAL angularB[3],
		iREAL linearB[3],
		iREAL massB,
		iREAL inverseB[9],
		iREAL rotationB[9],
		int   materialB,

		std::array<iREAL, 3> &f ,
		std::array<iREAL, 3> &torque,
		bool  isSphere);

	}
}


#endif
