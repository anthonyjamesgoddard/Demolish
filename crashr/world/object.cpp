#include "Object.h"

#include <stdio.h>
#include "algo.h"

crashr::Object::Object()
{
}

crashr::Object::Object(
    int                           			particleID,
    std::array<double, 3>         			centre,
    crashr::material::MaterialType           material,
    bool                          			isObstacle,
    bool                          			isFriction,
	bool                          			isConvex,
	double 									epsilon,
	std::array<double, 3> 					linear,
	std::array<double, 3> 					angular)
{
  this->_globalParticleID = particleID;

  this->_location[0] = centre[0];
  this->_location[1] = centre[1];
  this->_location[2] = centre[2];

  this->_material 	= material;
  this->_isObstacle 	= isObstacle;
  this->_isFriction	= isFriction;

  this->_linearVelocity[0] = linear[0];
  this->_linearVelocity[1] = linear[1];
  this->_linearVelocity[2] = linear[2];

  this->_angularVelocity[0] = angular[0];
  this->_angularVelocity[1] = angular[1];
  this->_angularVelocity[2] = angular[2];

  this->_epsilon = epsilon;
  this->_haloDiameter 		= 	(_diameter+epsilon*2) * 1.1;
  this->_diameter			=	_rad/2;
  this->_rad					= 	_diameter/2;

  this->_localParticleID 	= 0;
  this->_isConvex 			= isConvex;

  this->_mesh			= 	nullptr;
  this->_mass			=	0;

  _wx = 0;
  _wy = 0;
  _wz = 0;
}

crashr::Object::Object(
int                           			particleID,
crashr::Mesh*			mesh,
std::array<double, 3>         			centre,
crashr::material::MaterialType material,
bool                          			isObstacle,
bool                          			isFriction,
bool                          			isConvex,
double 									epsilon,
std::array<double, 3> 					linear,
std::array<double, 3> 					angular)
{
  this->_globalParticleID = particleID;
  this->_localParticleID = 0;

  this->_isConvex = isConvex;

  this->_location[0] = centre[0];
  this->_location[1] = centre[1];
  this->_location[2] = centre[2];

  
  
  this->_material 	    = material;
  this->_isObstacle 	= isObstacle;
  this->_isFriction 	= isFriction;
  
  this->_isSphere       = false;

  this->_epsilon        = epsilon;

  this->_linearVelocity[0] = linear[0];
  this->_linearVelocity[1] = linear[1];
  this->_linearVelocity[2] = linear[2];

  this->_angularVelocity[0] = angular[0];
  this->_angularVelocity[1] = angular[1];
  this->_angularVelocity[2] = angular[2];

  this->_refAngularVelocity[0] = angular[0];
  this->_refAngularVelocity[1] = angular[1];
  this->_refAngularVelocity[2] = angular[2];


  this-> _mesh			= 	mesh;


    this->_orientation[0] = 1.0;
  this->_orientation[1] = 0;
  this->_orientation[2] = 0;
  this->_orientation[3] = 0;
  this->_orientation[4] = 1.0;
  this->_orientation[5] = 0;
  this->_orientation[6] = 0;
  this->_orientation[7] = 0;
  this->_orientation[8] = 1.0;

  double mass, centerOfMass[3], inertia[9], inverse[9];
  
  mesh->computeInertia(_material, mass, centerOfMass, inertia);
  mesh->computeInverseInertia(inertia, inverse, _isObstacle);

  _inertia[0] = inertia[0];
  _inertia[1] = inertia[1];
  _inertia[2] = inertia[2];
  _inertia[3] = inertia[3];
  _inertia[4] = inertia[4];
  _inertia[5] = inertia[5];
  _inertia[6] = inertia[6];
  _inertia[7] = inertia[7];
  _inertia[8] = inertia[8];

  _inverse[0] = inverse[0];
  _inverse[1] = inverse[1];
  _inverse[2] = inverse[2];
  _inverse[3] = inverse[3];
  _inverse[4] = inverse[4];
  _inverse[5] = inverse[5];
  _inverse[6] = inverse[6];
  _inverse[7] = inverse[7];
  _inverse[8] = inverse[8];

  _centreOfMass[0] = centerOfMass[0];
  _centreOfMass[1] = centerOfMass[1];
  _centreOfMass[2] = centerOfMass[2];
 

  this->_referenceLocation[0] = centerOfMass[0];
  this->_referenceLocation[1] = centerOfMass[1];
  this->_referenceLocation[2] = centerOfMass[2];

  this->_diameter		=	mesh->computeDiameter();
  this->_rad				= 	_diameter/2;
  this->_haloDiameter 	= 	(_diameter+epsilon*2) * 1.1;
  this->_mass			=	mass;

  this->_minBoundBox 	=	mesh->getBoundaryMinVertex();
  this->_maxBoundBox 	=	mesh->getBoundaryMinVertex();


  // first we shift the mesh such that the origin is 
  // where to centre of mass is. Then we shift the
  // object such that the centre of mass is equal to 
  // location.

  double minusLocation[3] = {-_location[0],-_location[1],-_location[2]}; 

  
  mesh->shiftMesh(centerOfMass);
  mesh->shiftMesh(minusLocation);
  //dimensions
  _wx = 0;
  _wy = 0;
  _wz = 0;
}

// ****************************************************
//  sphere object
// ****************************************************

crashr::Object::Object(
double									rad,
int                           			particleID,
std::array<double, 3>         			centre,
crashr::material::MaterialType 	material,
bool                          			isObstacle,
bool                          			isFriction,
double 									epsilon,
std::array<double, 3> 					linear,
std::array<double, 3> 					angular)
{
  this->_isSphere           = true;
  this->_rad					= rad;
  this->_globalParticleID 	= particleID;
  this->_localParticleID 	= 0;

  this->_location[0] 	= centre[0];
  this->_location[1] 	= centre[1];
  this->_location[2] 	= centre[2];

  this->_centreOfMass[0] = _location[0];
  this->_centreOfMass[1] = _location[1];
  this->_centreOfMass[2] = _location[2];

  this->_material 		= material;
  this->_isObstacle 		= isObstacle;
  this->_isFriction 		= isFriction;

  this->_epsilon 		= epsilon;

  this->_linearVelocity[0] = linear[0];
  this->_linearVelocity[1] = linear[1];
  this->_linearVelocity[2] = linear[2];

  this->_angularVelocity[0] = angular[0];
  this->_angularVelocity[1] = angular[1];
  this->_angularVelocity[2] = angular[2];

  this->_haloDiameter 	= 	(_diameter+epsilon*2) * 1.1;
  this->_diameter		=	rad*2;
  this->_mass			=	(4.0/3.0)*M_PI*rad*rad*rad*crashr::material::materialToDensitymap[material];
  this->_mesh			= 	nullptr;

  this->_minBoundBox 	=	{centre[0] - _rad, centre[1] - _rad, centre[2] - _rad};
  this->_maxBoundBox 	=	{centre[0] + _rad, centre[1] + _rad, centre[2] + _rad};

  //dimensions
  _wx = 0;
  _wy = 0;
  _wz = 0;
}

std::string crashr::Object::getComponent()
{
  return _component;
}

void crashr::Object::setParticleID(int id)
{
  _globalParticleID = id;
}

void crashr::Object::setMesh(
	  std::vector<double> xCoordinates,
	  std::vector<double> yCoordinates,
	  std::vector<double> zCoordinates)
{
  _mesh = new crashr::Mesh(xCoordinates, yCoordinates, zCoordinates);
}

crashr::Mesh* crashr::Object::getMesh()
{
  return _mesh;
}

void crashr::Object::setMesh(
	  crashr::Mesh& mesh)
{
  _mesh = &mesh;

  double mass, centerOfMass[3], inertia[9], inverse[9];

  _mesh->computeInertia(_material, mass, centerOfMass, inertia);
  _mesh->computeInverseInertia(inertia, inverse, _isObstacle);

  _inertia[0] = inertia[0];
  _inertia[1] = inertia[1];
  _inertia[2] = inertia[2];
  _inertia[3] = inertia[3];
  _inertia[4] = inertia[4];
  _inertia[5] = inertia[5];
  _inertia[6] = inertia[6];
  _inertia[7] = inertia[7];
  _inertia[8] = inertia[8];

  _inverse[0] = inertia[0];
  _inverse[1] = inertia[1];
  _inverse[2] = inertia[2];
  _inverse[3] = inertia[3];
  _inverse[4] = inertia[4];
  _inverse[5] = inertia[5];
  _inverse[6] = inertia[6];
  _inverse[7] = inertia[7];
  _inverse[8] = inertia[8];

  _centreOfMass[0] = centerOfMass[0];
  _centreOfMass[1] = centerOfMass[1];
  _centreOfMass[2] = centerOfMass[2];

  _mass = mass;
}

double crashr::Object::getHaloDiameter()
{
  return _haloDiameter;
}

int crashr::Object::getNumberOfTriangles()
{
  return (int)_mesh->getTriangleFaces().size();
}

int crashr::Object::getGlobalParticleId()
{
  return _globalParticleID;
}

int crashr::Object::getLocalParticleId()
{
  return _localParticleID;
}


void crashr::Object::setLocation(std::array<double,3> newlocation)
{
    _location = newlocation;
}

void crashr::Object::setPrevLocation(std::array<double,3> newlocation)
{
    _prevLocation = newlocation;
}

double crashr::Object::getDiameter()
{
  return _rad*2;
}


void crashr::Object::setOrientation(std::array<double, 9> orientation)
{
    _orientation = orientation;
}

void crashr::Object::setPrevOrientation(std::array<double, 9> orientation)
{
    _prevOrientation = orientation;
}

std::array<double, 3> crashr::Object::getLocation()
{
  return _location;
}

std::array<double, 3> crashr::Object::getPrevLocation()
{
  return _prevLocation;
}

std::array<double, 3> crashr::Object::getReferenceLocation()
{
    return _referenceLocation;
}

void crashr::Object::setCentre(double centre[3])
{
  this->_location[0] = centre[0];
  this->_location[1] = centre[1];
  this->_location[2] = centre[2];
}


void crashr::Object::setCentre(std::array<double,3>& centre)
{
    this->_location = centre;
}

double crashr::Object::getEpsilon()
{
  return _epsilon;
}

void crashr::Object::setEpsilon(double epsilon)
{
  _epsilon = epsilon;
}

double crashr::Object::getRad()
{
  return _rad;
}

void crashr::Object::setRad(double rad)
{
  this->_minBoundBox 	=	{_location[0] - _rad, _location[1] - _rad, _location[2] - _rad};
  this->_maxBoundBox 	=	{_location[0] + _rad, _location[1] + _rad, _location[2] + _rad};

  _rad = rad;
  this->_haloDiameter 	= 	(_diameter+_epsilon*2) * 1.1;
  this->_diameter		=	rad*2;
}

double crashr::Object::getMass()
{

  return _mass;
}

void crashr::Object::setMass(double mass)
{
  _mass = mass;
}

crashr::material::MaterialType crashr::Object::getMaterial()
{
  return _material;
}

bool crashr::Object::getIsObstacle()
{
  return _isObstacle;
}

bool crashr::Object::getIsFriction()
{
  return _isFriction;
}

std::array<double, 9> crashr::Object::getInertia()
{
  return _inertia;
}

std::array<double, 9> crashr::Object::getOrientation()
{
    return _orientation;
}

std::array<double, 9> crashr::Object::getPrevOrientation()
{
    return _prevOrientation;
}

void crashr::Object::setInertia(double inertia[9])
{
  _inertia[0] = inertia[0];
  _inertia[1] = inertia[1];
  _inertia[2] = inertia[2];
  _inertia[3] = inertia[3];
  _inertia[4] = inertia[4];
  _inertia[5] = inertia[5];
  _inertia[6] = inertia[6];
  _inertia[7] = inertia[7];
  _inertia[8] = inertia[8];
}

std::array<double, 9> crashr::Object::getInverse()
{
  return _inverse;
}

void crashr::Object::setInverse(double inverse[9])
{
  _inverse[0] = inverse[0];
  _inverse[1] = inverse[1];
  _inverse[2] = inverse[2];
  _inverse[3] = inverse[3];
  _inverse[4] = inverse[4];
  _inverse[5] = inverse[5];
  _inverse[6] = inverse[6];
  _inverse[7] = inverse[7];
  _inverse[8] = inverse[8];
}

std::array<double, 3> crashr::Object::getCentreOfMass()
{
  return _centreOfMass;
}

void crashr::Object::setCentreOfMass(double centreOfMass[3])
{
  _centreOfMass[0] = centreOfMass[0];
  _centreOfMass[1] = centreOfMass[1];
  _centreOfMass[2] = centreOfMass[2];
}

void crashr::Object::setLinearVelocity(std::array<double, 3>  linearVelocity)
{
  this->_linearVelocity[0] = linearVelocity[0];
  this->_linearVelocity[1] = linearVelocity[1];
  this->_linearVelocity[2] = linearVelocity[2];
}

void crashr::Object::setAngularVelocity(std::array<double, 3>  angularVelocity)
{
  this->_angularVelocity[0] = angularVelocity[0];
  this->_angularVelocity[1] = angularVelocity[1];
  this->_angularVelocity[2] = angularVelocity[2];
}

void crashr::Object::setPrevLinearVelocity(std::array<double, 3>  linearVelocity)
{
  this->_prevLinearVelocity = linearVelocity;
}

void crashr::Object::setPrevAngularVelocity(std::array<double, 3>  angularVelocity)
{
  this->_prevAngularVelocity = angularVelocity;
}

std::array<double, 3> crashr::Object::getLinearVelocity()
{
  return _linearVelocity;
}

std::array<double, 3> crashr::Object::getAngularVelocity()
{
  return _angularVelocity;
}

std::array<double, 3> crashr::Object::getPrevLinearVelocity()
{
  return _prevLinearVelocity;
}

std::array<double, 3> crashr::Object::getPrevAngularVelocity()
{
  return _prevAngularVelocity;
}

std::array<double, 3> crashr::Object::getPrevRefAngularVelocity()
{
  return _prevRefAngularVelocity;
}
std::array<double, 3> crashr::Object::getReferenceAngularVelocity()
{
    return _refAngularVelocity;
}

void crashr::Object::setReferenceAngularVelocity(std::array<double, 3> ang)
{
    _refAngularVelocity = ang;
}

void crashr::Object::setPrevRefAngularVelocity(std::array<double, 3> ang)
{
    _prevRefAngularVelocity = ang;
}
double crashr::Object::computeVolume()
{
  std::vector<double> xCoordinates;
  std::vector<double> yCoordinates;
  std::vector<double> zCoordinates;
  this->getMesh()->flatten(xCoordinates, yCoordinates, zCoordinates);

  return this->getMesh()->computeVolume();
}

/*
 * gets the inertia using simplex integration from solfec
 */
void crashr::Object::computeInertia(
		crashr::material::MaterialType material,
		double& mass,
		double center[3],
		double inertia[9])
{
  this->getMesh()->computeInertia(material, mass, center, inertia);
  this->setInertia(inertia);
  this->setMass(mass);
}

double crashr::Object::computeMass(
		crashr::material::MaterialType material)
{
  double mass = this->getMesh()->computeMass(material);
  this->setMass(mass);
  return mass;
}

void crashr::Object::computeInverseInertia(
	  double inertia[9],
	  double inverse[9],
	  bool 	isObject)
{
  crashr::operators::computeInverseInertia(inertia, inverse, isObject);
  this->setInverse(inverse);
}

bool crashr::Object::getIsConvex()
{
  return _isConvex;
}

bool crashr::Object::getIsSphere()
{
  return _isSphere;
}
crashr::Vertex crashr::Object::getMinBoundaryVertex()
{
  return _minBoundBox;
}

crashr::Vertex crashr::Object::getMaxBoundaryVertex()
{
  return _maxBoundBox;
}

crashr::Object::~Object() {

}


