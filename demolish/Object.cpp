#include "Object.h"

#include <stdio.h>
#include "algo.h"

demolish::Object::Object()
{
}

demolish::Object::Object(
    int                           			particleID,
    std::array<iREAL, 3>         			centre,
    demolish::material::MaterialType           material,
    bool                          			isObstacle,
    bool                          			isFriction,
	bool                          			isConvex,
	iREAL 									epsilon,
	std::array<iREAL, 3> 					linear,
	std::array<iREAL, 3> 					angular)
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

demolish::Object::Object(
int                           			particleID,
demolish::Mesh*			mesh,
std::array<iREAL, 3>         			centre,
demolish::material::MaterialType material,
bool                          			isObstacle,
bool                          			isFriction,
bool                          			isConvex,
iREAL 									epsilon,
std::array<iREAL, 3> 					linear,
std::array<iREAL, 3> 					angular)
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

  this-> _mesh			= 	mesh;

  iREAL po[3] = {centre[0], centre[1], centre[2]};
  mesh->moveMeshToPosition(po);

  iREAL mass, centerOfMass[3], inertia[9], inverse[9];

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

  this->_diameter		=	mesh->computeDiameter();
  this->_rad				= 	_diameter/2;
  this->_haloDiameter 	= 	(_diameter+epsilon*2) * 1.1;
  this->_mass			=	mass;

  this->_minBoundBox 	=	mesh->getBoundaryMinVertex();
  this->_maxBoundBox 	=	mesh->getBoundaryMinVertex();

  //dimensions
  _wx = 0;
  _wy = 0;
  _wz = 0;
}

//sphere object
demolish::Object::Object(
iREAL									rad,
int                           			particleID,
std::array<iREAL, 3>         			centre,
demolish::material::MaterialType 	material,
bool                          			isObstacle,
bool                          			isFriction,
iREAL 									epsilon,
std::array<iREAL, 3> 					linear,
std::array<iREAL, 3> 					angular)
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
  this->_mass			=	(4.0/3.0)*M_PI*rad*rad*rad*demolish::material::materialToDensitymap[material];
  this->_mesh			= 	nullptr;

  this->_minBoundBox 	=	{centre[0] - _rad, centre[1] - _rad, centre[2] - _rad};
  this->_maxBoundBox 	=	{centre[0] + _rad, centre[1] + _rad, centre[2] + _rad};

  //dimensions
  _wx = 0;
  _wy = 0;
  _wz = 0;
}

std::string demolish::Object::getComponent()
{
  return _component;
}

void demolish::Object::setParticleID(int id)
{
  _globalParticleID = id;
}

void demolish::Object::setMesh(
	  std::vector<iREAL> xCoordinates,
	  std::vector<iREAL> yCoordinates,
	  std::vector<iREAL> zCoordinates)
{
  _mesh = new demolish::Mesh(xCoordinates, yCoordinates, zCoordinates);
}

demolish::Mesh demolish::Object::getMesh()
{
  return *_mesh;
}

void demolish::Object::setMesh(
	  demolish::Mesh& mesh)
{
  _mesh = &mesh;

  iREAL mass, centerOfMass[3], inertia[9], inverse[9];

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

iREAL demolish::Object::getHaloDiameter()
{
  return _haloDiameter;
}

int demolish::Object::getNumberOfTriangles()
{
  return (int)_mesh->getTriangleFaces().size();
}

int demolish::Object::getGlobalParticleId()
{
  return _globalParticleID;
}

int demolish::Object::getLocalParticleId()
{
  return _localParticleID;
}

void demolish::Object::setLocation(std::array<iREAL,3> newlocation)
{
    _location = newlocation;
}

iREAL demolish::Object::getDiameter()
{
  return _rad*2;
}

std::array<iREAL, 3> demolish::Object::getLocation()
{
  return _location;
}

void demolish::Object::setCentre(iREAL centre[3])
{
  this->_location[0] = centre[0];
  this->_location[1] = centre[1];
  this->_location[2] = centre[2];
}


void demolish::Object::setCentre(std::array<iREAL,3>& centre)
{
    this->_location = centre;
}

iREAL demolish::Object::getEpsilon()
{
  return _epsilon;
}

void demolish::Object::setEpsilon(iREAL epsilon)
{
  _epsilon = epsilon;
}

iREAL demolish::Object::getRad()
{
  return _rad;
}

void demolish::Object::setRad(iREAL rad)
{
  this->_minBoundBox 	=	{_location[0] - _rad, _location[1] - _rad, _location[2] - _rad};
  this->_maxBoundBox 	=	{_location[0] + _rad, _location[1] + _rad, _location[2] + _rad};

  _rad = rad;
  this->_haloDiameter 	= 	(_diameter+_epsilon*2) * 1.1;
  this->_diameter		=	rad*2;
}

iREAL demolish::Object::getMass()
{

  return _mass;
}

void demolish::Object::setMass(iREAL mass)
{
  _mass = mass;
}

demolish::material::MaterialType demolish::Object::getMaterial()
{
  return _material;
}

bool demolish::Object::getIsObstacle()
{
  return _isObstacle;
}

bool demolish::Object::getIsFriction()
{
  return _isFriction;
}

std::array<iREAL, 9> demolish::Object::getInertia()
{
  return _inertia;
}

void demolish::Object::setInertia(iREAL inertia[9])
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

std::array<iREAL, 9> demolish::Object::getInverse()
{
  return _inverse;
}

void demolish::Object::setInverse(iREAL inverse[9])
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

std::array<iREAL, 3> demolish::Object::getCentreOfMass()
{
  return _centreOfMass;
}

void demolish::Object::setCentreOfMass(iREAL centreOfMass[3])
{
  _centreOfMass[0] = centreOfMass[0];
  _centreOfMass[1] = centreOfMass[1];
  _centreOfMass[2] = centreOfMass[2];
}

void demolish::Object::setLinearVelocity(std::array<iREAL, 3>  linearVelocity)
{
  this->_linearVelocity[0] = linearVelocity[0];
  this->_linearVelocity[1] = linearVelocity[1];
  this->_linearVelocity[2] = linearVelocity[2];
}

void demolish::Object::setAngularVelocity(std::array<iREAL, 3>  angularVelocity)
{
  this->_angularVelocity[0] = angularVelocity[0];
  this->_angularVelocity[1] = angularVelocity[1];
  this->_angularVelocity[2] = angularVelocity[2];
}

std::array<iREAL, 3> demolish::Object::getLinearVelocity()
{
  return _linearVelocity;
}

std::array<iREAL, 3> demolish::Object::getAngularVelocity()
{
  return _angularVelocity;
}

iREAL demolish::Object::computeVolume()
{
  std::vector<iREAL> xCoordinates;
  std::vector<iREAL> yCoordinates;
  std::vector<iREAL> zCoordinates;
  this->getMesh().flatten(xCoordinates, yCoordinates, zCoordinates);

  return this->getMesh().computeVolume();
}

/*
 * gets the inertia using simplex integration from solfec
 */
void demolish::Object::computeInertia(
		demolish::material::MaterialType material,
		iREAL& mass,
		iREAL center[3],
		iREAL inertia[9])
{
  this->getMesh().computeInertia(material, mass, center, inertia);
  this->setInertia(inertia);
  this->setMass(mass);
}

iREAL demolish::Object::computeMass(
		demolish::material::MaterialType material)
{
  iREAL mass = this->getMesh().computeMass(material);
  this->setMass(mass);
  return mass;
}

void demolish::Object::computeInverseInertia(
	  iREAL inertia[9],
	  iREAL inverse[9],
	  bool 	isObject)
{
  demolish::operators::computeInverseInertia(inertia, inverse, isObject);
  this->setInverse(inverse);
}

bool demolish::Object::getIsConvex()
{
  return _isConvex;
}

bool demolish::Object::getIsSphere()
{
  return _isSphere;
}
demolish::Vertex demolish::Object::getMinBoundaryVertex()
{
  return _minBoundBox;
}

demolish::Vertex demolish::Object::getMaxBoundaryVertex()
{
  return _maxBoundBox;
}

demolish::Object::~Object() {

}


