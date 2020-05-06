

#ifndef PHYSICS
#define PHYSICS

#include "../material.h"
#include "../algo.h"
#include "../crashr.h"
#include <vector>

namespace crashr {
	namespace operators {

		/*
		 *  Get Volume
		 *
		 *  return volume of geomety
		 *  @param none
		 *  @return double
		 */
		double computeVolume(
			std::vector<double>& xCoordinates,
			std::vector<double>& yCoordinates,
			std::vector<double>& zCoordinates);

		/*
		 *  Get Inertia Matrix
		 *
		 *  Returns inertia by reference.
		 *
		 *
		 *  @param material
	  	 *  @param mass
		 *  @param center
		 *  @param inertia
		 *  @returns void
		 */
		void computeInertia(
			std::vector<double>& xCoordinates,
			std::vector<double>& yCoordinates,
			std::vector<double>& zCoordinates,
			crashr::material::MaterialType material,
			double& mass,
			double center[3],
			double inertia[9]);

		/*
		 *  Get Mass
		 *
		 *  Returns mass of mesh give a material.
		 *
		 *
		 *  @param xCoordinates
		 *  @param yCoordinates
		 *  @param zCoordinates
		 *  @param material
		 *  @returns double
		 */
		double computeMass(
			std::vector<double>& xCoordinates,
			std::vector<double>& yCoordinates,
			std::vector<double>& zCoordinates,
			crashr::material::MaterialType material);

		/*
		 *  Get Inverse Inertia Matrix
		 *
		 *  Returns inverse inertia by reference.
		 *
		 *
		 *  @param inertia
		 *  @param inverse
		 *  @param isObject
		 *  @returns void
		 */
		void computeInverseInertia(
			double inertia[9],
			double inverse[9],
			bool isObject);

		/*
		 * simplex integration from solfec
		 */
		double simplex_J(
			double *a, double *b, double *c, double *d);
  } 
} 

#endif 
