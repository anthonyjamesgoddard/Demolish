

#ifndef OBJECT
#define OBJECT

#include <vector>
#include <array>
#include <string>

#include "material.h"
#include "Mesh.h"

namespace demolish {
    class Object;
}

class demolish::Object
{
  public:
	Object();

	/*
	 * Mesh object with mesh unspecified
	 */
	Object(
	  int                           				particleID,
	  std::array<iREAL, 3>         				    centre,
	  demolish::material::MaterialType 	            material,
	  bool                          				isObstacle,
	  bool                          				isFriction,
	  bool                          				isConvex,
	  iREAL 										epsilon,
	  std::array<iREAL, 3> linear,
	  std::array<iREAL, 3> angular
	);

	/*
	 * Mesh object with mesh specified
	 */
	Object(
	  int                           				particleID,
	  demolish::Mesh*				    mesh,
	  std::array<iREAL, 3>         				    centre,
	  demolish::material::MaterialType 	            material,
	  bool                          				isObstacle,
	  bool                          				isFriction,
	  bool                          				isConvex,
	  iREAL 										epsilon,
	  std::array<iREAL, 3> 						    linear,
	  std::array<iREAL, 3> 						    angular
	);

	/*
	 * Sphere object
	 */
	Object(
	  iREAL										    rad,
	  int                           				particleID,
	  std::array<iREAL, 3>         				    centre,
	  demolish::material::MaterialType 	            material,
	  bool                          				isObstacle,
	  bool                          				isFriction,
	  iREAL 										epsilon,
	  std::array<iREAL, 3> 						    linear,
	  std::array<iREAL, 3> 						    angular
	);

    void setParticleID(int id);

    void setCentre(
    		  iREAL centre[3]);

    void setCentre(std::array<iREAL, 3>& centre);

    void setRad(
    		  iREAL rad);

    void setMass(
    		  iREAL mass);

    void setEpsilon(
    		  iREAL epsilon);

    void setInertia(
    		  iREAL inertia[9]);

    void setInverse(
    		  iREAL inverse[9]);

    void setCentreOfMass(
    		  iREAL	centreOfMass[3]);

    void setLinearVelocity(
    		  std::array<iREAL, 3>  linearVelocity);

    void setAngularVelocity(
    		  std::array<iREAL, 3>  angularVelocity);

    void setMesh(
    		  demolish::Mesh& mesh);


    void setLocation(
          std::array<iREAL,3> newlocation);

    void setMesh(
		  std::vector<iREAL> xCoordinates,
		  std::vector<iREAL> yCoordinates,
		  std::vector<iREAL> zCoordinates);

    std::string getComponent();

    iREAL getRad();

	iREAL getDiameter();

    iREAL getMass();

    iREAL getEpsilon();

	iREAL getHaloDiameter();

	int 	getNumberOfTriangles();

	int 	getGlobalParticleId();

	int 	getLocalParticleId();

    bool getIsObstacle();

	/*
	 *  Get Is Friction
	 *
	 *  Gets bool on whether body applies friction.
	 *
	 *  @param none
	 *  @returns bool
	 */
    bool getIsFriction();

	/*
	 *  Get Volume
	 *
	 *  Gets volume of object
	 *
	 *  @param none
	 *  @returns iREAL
	 */
    iREAL computeVolume();

	/*
	 *  Get Center
	 *
	 *  Gets center of geometry of object
	 *
	 *  @param none
	 *  @returns vertex
	 */
    std::array<iREAL, 3> getLocation();

	/*
	 *  Get Inertia
	 *
	 *  Gets inertia of object
	 *
	 *  @param none
	 *  @returns inertia
	 */
    std::array<iREAL, 9> getInertia();

	/*
	 *  Get Inverse Inertia
	 *
	 *  Gets inverse inertia of object
	 *
	 *  @param none
	 *  @returns inverse
	 */
    std::array<iREAL, 9> getInverse();

	/*
	 *  Get Center of Mass
	 *
	 *  Gets center of mass of object
	 *
	 *  @param none
	 *  @returns vertex
	 */
    std::array<iREAL, 3> getCentreOfMass();

	/*
	 *  Get Linear Velocity
	 *
	 *  Gets linear velocity of object
	 *
	 *  @param none
	 *  @returns velocity
	 */
    std::array<iREAL, 3> getLinearVelocity();

	/*
	 *  Get Angular Velocity
	 *
	 *  Gets angular velocity of object
	 *
	 *  @param none
	 *  @returns velocity
	 */
    std::array<iREAL, 3> getAngularVelocity();

	/*
	 *  Get Material
	 *
	 *  Gets material of object
	 *
	 *  @param none
	 *  @returns material
	 */
    demolish::material::MaterialType getMaterial();

	/*
	 *  Get Mesh
	 *
	 *  Gets mesh of object
	 *
	 *  @param none
	 *  @returns mesh
	 */
    demolish::Mesh 	getMesh();

	/*
	 *  Compute Inertia
	 *
	 *  Computes inertia of object
	 *	This modifies local data.
	 *
	 *
	 *  @param none
	 *  @returns inertia
	 */
	void computeInertia(
			demolish::material::MaterialType material,
			iREAL& mass,
			iREAL center[3],
			iREAL inertia[9]);

	/*
	 *  Compute Inverse Inertia
	 *
	 *  Computes inverse inertia of object
	 *	This modifies local data.
	 *
	 *
	 *  @param none
	 *  @returns inverse
	 */
	void computeInverseInertia(
			iREAL inertia[9],
			iREAL inverse[9],
			bool isObject);

	/*
	 *  Compute Mass
	 *
	 *  Computes mass of object
	 *	This modifies local data.
	 *
	 *
	 *  @param none
	 *  @returns mass
	 */
	iREAL computeMass(
			demolish::material::MaterialType material);

	demolish::Vertex        getMinBoundaryVertex();
	demolish::Vertex        getMaxBoundaryVertex();

	bool getIsConvex();
    bool getIsSphere();

    virtual ~Object();

    std::array<iREAL, 3> 	_linearVelocity;
    std::array<iREAL, 3> 	_angularVelocity;

    std::array<iREAL, 3> 	_location;
    std::array<iREAL, 3> 	_centreOfMass;          //centre of mass 

  private:
    std::string           	_component;
    int                   	_globalParticleID;
    int                  	_localParticleID;

    iREAL                	_rad;
    iREAL				 	_haloDiameter;
    iREAL				 	_diameter;
    iREAL               	_mass;
    iREAL 				 	_epsilon;

    //dimensions
    iREAL                	_wx;
    iREAL                	_wy;
    iREAL                	_wz;

	demolish::Mesh*      			    _mesh;
    demolish::material::MaterialType 	_material;

    bool                  	_isObstacle;
    bool                  	_isFriction;
    bool                  	_isConvex;
    bool                    _isSphere;

    std::array<iREAL, 9> 	_inertia;
    std::array<iREAL, 9> 	_inverse;

    demolish::Vertex 	_minBoundBox;
    demolish::Vertex 	_maxBoundBox;
};

#endif
