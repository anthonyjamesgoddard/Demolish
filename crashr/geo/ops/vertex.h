
#ifndef VERTEX
#define VERTEX

#include "../demolish.h"
#include "../Vertex.h"
#include <vector>
#include <array>
#include <cmath>
#include <limits>

namespace demolish {
    namespace operators {
		iREAL computeXYZw(
			std::vector<iREAL> xCoordinates,
			std::vector<iREAL> yCoordinates,
			std::vector<iREAL> zCoordinates);
		iREAL computeXZw(
			std::vector<iREAL> xCoordinates,
			std::vector<iREAL> yCoordinates,
			std::vector<iREAL> zCoordinates);
		iREAL computeXw(
			std::vector<iREAL> xCoordinates,
			std::vector<iREAL> yCoordinates,
			std::vector<iREAL> zCoordinates);
		iREAL computeYw(
			std::vector<iREAL> xCoordinates,
			std::vector<iREAL> yCoordinates,
			std::vector<iREAL> zCoordinates);
		iREAL computeZw(
			std::vector<iREAL> xCoordinates,
			std::vector<iREAL> yCoordinates,
			std::vector<iREAL> zCoordinates);

		demolish::Vertex computeBoundaryMinVertex(
			std::vector<iREAL> xCoordinates,
			std::vector<iREAL> yCoordinates,
			std::vector<iREAL> zCoordinates);

		demolish::Vertex computeBoundaryMaxVertex(
			std::vector<iREAL> xCoordinates,
			std::vector<iREAL> yCoordinates,
			std::vector<iREAL> zCoordinates);

		std::array<iREAL, 6> computeBbox(
			std::vector<iREAL> xCoordinates,
			std::vector<iREAL> yCoordinates,
			std::vector<iREAL> zCoordinates);

		iREAL computeDiagonal(
			std::vector<iREAL> xCoordinates,
			std::vector<iREAL> yCoordinates,
			std::vector<iREAL> zCoordinates);

		iREAL computeDistanceAB(
		    demolish::Vertex A,
		    demolish::Vertex B);

		iREAL computeMin(
			  std::vector<iREAL> coordinates);

		iREAL computeMax(
			  std::vector<iREAL> coordinates);

   } 
} 

#endif 
