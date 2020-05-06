
#ifndef DELTA_DYNAMICS_DYNAMICS_H_
#define DELTA_DYNAMICS_DYNAMICS_H_


#include"../demolish.h"

namespace demolish {
  namespace dynamics {

	/*
	* Update Angular Velocity
	*
	* Returns the updated angular velocity.
	*
	* @param refAngular is the referential angular velocity
	* @param rotation is the rotation matrix
	* @param inertia is inertia
	* @param inverse is the inverse inertia
	* @param mass is the mass of the particle
	* @param torque is the applied torque
	* @param step is the step size
	* @return void
	*/
    void updateAngular(
        iREAL *refAngular,
        iREAL *rotation,
        iREAL *inertia,
        iREAL *inverse,
        iREAL *torque,
        iREAL step);

	/*
	* Update Rotational Matrix
	*
	* Returns the updated rotational matrix.
	*
	* @param angular is the angular velocity
	* @param refAngular is the referential angular velocity
	* @param rotation is the rotational matrix
	* @param step is the step size
	* @return void
	*/
    void updateRotationMatrix(
        iREAL *angular,
        iREAL *refAngular,
        iREAL *rotation,
        iREAL step);

	/*
	* Update Vertices
	*
	* Returns the updated vertices of the mesh according to the new orientation matrix.
	*
	* @param x is x coordinates of the mesh
	* @param y is y coordinates of the mesh
	* @param z is z coordinates of the mesh
	* @param refx is referential x coordinates of the mesh
	* @param refy is referential y coordinates of the mesh
	* @param refz is referential z coordinates of the mesh
	* @param rotation is the rotational matrix
	* @param position is the center of mass
	* @param refposition is the referential center of mass
	* @return void
	*/
    void updateVertices(
        iREAL* x,
        iREAL* y,
        iREAL* z,
        iREAL* refx,
        iREAL* refy,
        iREAL* refz,
        iREAL* rotation,
        iREAL* position,
        iREAL* refposition);
  }
}
#endif
