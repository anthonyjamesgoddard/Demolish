

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
	  demolish::Mesh*				                mesh,
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

    void setPrevLinearVelocity(
    		  std::array<iREAL, 3>  linearVelocity);

    void setPrevAngularVelocity(
    		  std::array<iREAL, 3>  angularVelocity);
    void setPrevRefAngularVelocity(
    		  std::array<iREAL, 3>  angularVelocity);

    void setMesh(
    		  demolish::Mesh& mesh);

    void setLocation(
          std::array<iREAL,3> newlocation);

    void setPrevLocation(
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

	int getNumberOfTriangles();

	int getGlobalParticleId();

	int getLocalParticleId();

    bool getIsObstacle();

    bool getIsFriction();

    iREAL computeVolume();

    std::array<iREAL, 3> getLocation();
    std::array<iREAL, 3> getPrevLocation();
    std::array<iREAL, 3> getReferenceLocation();

    std::array<iREAL, 9> getInertia();

    std::array<iREAL, 9> getOrientation();
    std::array<iREAL, 9> getPrevOrientation();

    void setOrientation(std::array<iREAL, 9> orientation);
    void setPrevOrientation(std::array<iREAL, 9> orientation);

    std::array<iREAL, 9> getInverse();

    std::array<iREAL, 3> getCentreOfMass();

    std::array<iREAL, 3> getLinearVelocity();
    std::array<iREAL, 3> getPrevLinearVelocity();
    std::array<iREAL, 3> getAngularVelocity();
    std::array<iREAL, 3> getPrevAngularVelocity();
    std::array<iREAL, 3> getPrevRefAngularVelocity();
    std::array<iREAL, 3> getReferenceAngularVelocity();

    void setReferenceAngularVelocity(std::array<iREAL,3>  ang);

    demolish::material::MaterialType getMaterial();

    demolish::Mesh* 	getMesh();

	void computeInertia(
			demolish::material::MaterialType material,
			iREAL& mass,
			iREAL center[3],
			iREAL inertia[9]);

	void computeInverseInertia(
			iREAL inertia[9],
			iREAL inverse[9],
			bool isObject);

	iREAL computeMass(
			demolish::material::MaterialType material);

	demolish::Vertex        getMinBoundaryVertex();
	demolish::Vertex        getMaxBoundaryVertex();

	bool getIsConvex();
    bool getIsSphere();

    virtual ~Object();


    std::array<iREAL, 3> 	_prevLinearVelocity;
    std::array<iREAL, 3> 	_prevAngularVelocity;
    std::array<iREAL, 3>    _prevLocation;

    std::array<iREAL, 3> 	_linearVelocity;
    std::array<iREAL, 3> 	_angularVelocity;
    std::array<iREAL, 3> 	_location;

    std::array<iREAL, 3>    _refAngularVelocity;
    std::array<iREAL, 3>    _referenceLocation;


    std::array<iREAL, 3>    _prevRefAngularVelocity;

    std::array<iREAL, 3> 	_centreOfMass;

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

    std::array<iREAL, 9>    _orientation;
    std::array<iREAL, 9>    _prevOrientation;

    std::array<iREAL, 9> 	_inertia;
    std::array<iREAL, 9> 	_inverse;

    demolish::Vertex 	_minBoundBox;
    demolish::Vertex 	_maxBoundBox;
};

#endif
