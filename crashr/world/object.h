

#ifndef OBJECT
#define OBJECT

#include <vector>
#include <array>
#include <string>

#include "material.h"
#include "Mesh.h"

namespace crashr {
    class Object;
}

class crashr::Object
{
  public:
	Object();

	/*
	 * Mesh object with mesh unspecified
	 */
	Object(
	  int                           				particleID,
	  std::array<double, 3>         				    centre,
	  crashr::material::MaterialType 	            material,
	  bool                          				isObstacle,
	  bool                          				isFriction,
	  bool                          				isConvex,
	  double 										epsilon,
	  std::array<double, 3> linear,
	  std::array<double, 3> angular
	);

	/*
	 * Mesh object with mesh specified
	 */
	Object(
	  int                           				particleID,
	  crashr::Mesh*				                mesh,
	  std::array<double, 3>         				    centre,
	  crashr::material::MaterialType 	            material,
	  bool                          				isObstacle,
	  bool                          				isFriction,
	  bool                          				isConvex,
	  double 										epsilon,
	  std::array<double, 3> 						    linear,
	  std::array<double, 3> 						    angular
	);

	/*
	 * Sphere object
	 */
	Object(
	  double										    rad,
	  int                           				particleID,
	  std::array<double, 3>         				    centre,
	  crashr::material::MaterialType 	            material,
	  bool                          				isObstacle,
	  bool                          				isFriction,
	  double 										epsilon,
	  std::array<double, 3> 						    linear,
	  std::array<double, 3> 						    angular
	);

    void setParticleID(int id);

    void setCentre(
    		  double centre[3]);

    void setCentre(std::array<double, 3>& centre);

    void setRad(
    		  double rad);

    void setMass(
    		  double mass);

    void setEpsilon(
    		  double epsilon);

    void setInertia(
    		  double inertia[9]);

    void setInverse(
    		  double inverse[9]);

    void setCentreOfMass(
    		  double	centreOfMass[3]);

    void setLinearVelocity(
    		  std::array<double, 3>  linearVelocity);

    void setAngularVelocity(
    		  std::array<double, 3>  angularVelocity);

    void setPrevLinearVelocity(
    		  std::array<double, 3>  linearVelocity);

    void setPrevAngularVelocity(
    		  std::array<double, 3>  angularVelocity);
    void setPrevRefAngularVelocity(
    		  std::array<double, 3>  angularVelocity);

    void setMesh(
    		  crashr::Mesh& mesh);

    void setLocation(
          std::array<double,3> newlocation);

    void setPrevLocation(
          std::array<double,3> newlocation);

    void setMesh(
		  std::vector<double> xCoordinates,
		  std::vector<double> yCoordinates,
		  std::vector<double> zCoordinates);

    std::string getComponent();

    double getRad();

	double getDiameter();

    double getMass();

    double getEpsilon();

	double getHaloDiameter();

	int getNumberOfTriangles();

	int getGlobalParticleId();

	int getLocalParticleId();

    bool getIsObstacle();

    bool getIsFriction();

    double computeVolume();

    std::array<double, 3> getLocation();
    std::array<double, 3> getPrevLocation();
    std::array<double, 3> getReferenceLocation();

    std::array<double, 9> getInertia();

    std::array<double, 9> getOrientation();
    std::array<double, 9> getPrevOrientation();

    void setOrientation(std::array<double, 9> orientation);
    void setPrevOrientation(std::array<double, 9> orientation);

    std::array<double, 9> getInverse();

    std::array<double, 3> getCentreOfMass();

    std::array<double, 3> getLinearVelocity();
    std::array<double, 3> getPrevLinearVelocity();
    std::array<double, 3> getAngularVelocity();
    std::array<double, 3> getPrevAngularVelocity();
    std::array<double, 3> getPrevRefAngularVelocity();
    std::array<double, 3> getReferenceAngularVelocity();

    void setReferenceAngularVelocity(std::array<double,3>  ang);

    crashr::material::MaterialType getMaterial();

    crashr::Mesh* 	getMesh();

	void computeInertia(
			crashr::material::MaterialType material,
			double& mass,
			double center[3],
			double inertia[9]);

	void computeInverseInertia(
			double inertia[9],
			double inverse[9],
			bool isObject);

	double computeMass(
			crashr::material::MaterialType material);

	crashr::Vertex        getMinBoundaryVertex();
	crashr::Vertex        getMaxBoundaryVertex();

	bool getIsConvex();
    bool getIsSphere();

    virtual ~Object();


    std::array<double, 3> 	_prevLinearVelocity;
    std::array<double, 3> 	_prevAngularVelocity;
    std::array<double, 3>    _prevLocation;

    std::array<double, 3> 	_linearVelocity;
    std::array<double, 3> 	_angularVelocity;
    std::array<double, 3> 	_location;

    std::array<double, 3>    _refAngularVelocity;
    std::array<double, 3>    _referenceLocation;


    std::array<double, 3>    _prevRefAngularVelocity;

    std::array<double, 3> 	_centreOfMass;

  private:
    std::string           	_component;
    int                   	_globalParticleID;
    int                  	_localParticleID;

    double                	_rad;
    double				 	_haloDiameter;
    double				 	_diameter;
    double               	_mass;
    double 				 	_epsilon;

    //dimensions
    double                	_wx;
    double                	_wy;
    double                	_wz;

	crashr::Mesh*      			    _mesh;
    crashr::material::MaterialType 	_material;

    bool                  	_isObstacle;
    bool                  	_isFriction;
    bool                  	_isConvex;
    bool                    _isSphere;

    std::array<double, 9>    _orientation;
    std::array<double, 9>    _prevOrientation;

    std::array<double, 9> 	_inertia;
    std::array<double, 9> 	_inverse;

    crashr::Vertex 	_minBoundBox;
    crashr::Vertex 	_maxBoundBox;
};

#endif
