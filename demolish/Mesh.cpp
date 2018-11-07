

#include "Mesh.h"

#include <vector>
#include <map>
#include <cmath>
#include <array>
#include <string>
#include <sstream>
#include <functional>
#include <limits>
#include <iostream>
#include <iomanip>
#include <functional>
#include <unordered_set>

demolish::Mesh::Mesh()
{

}

demolish::Mesh::Mesh(
	std::vector<std::array<int, 3>> 		&triangleFaces,
	std::vector<Vertex>                  	&uniqueVertices)
{
  _triangleFaces = triangleFaces;
  _uniqueVertices = uniqueVertices;

  demolish::Mesh::flatten();
  for(int i=0;i<_yCoordinates.size();i++)
      std::cout << _yCoordinates[i] << std::endl;
}

demolish::Mesh::Mesh(
	std::vector<iREAL>& xCoordinates,
	std::vector<iREAL>& yCoordinates,
	std::vector<iREAL>& zCoordinates)
{
  _maxMeshSize = 0;
  _minMeshSize = 1E99;

  iREAL min = 1E99;
  iREAL max = 0;

  //#pragma omp parallel for
  for(int i=0; i<xCoordinates.size(); i+=3)
  {
	_xCoordinates.push_back(xCoordinates[i]);
	_yCoordinates.push_back(yCoordinates[i]);
	_zCoordinates.push_back(zCoordinates[i]);

	_xCoordinates.push_back(xCoordinates[i+1]);
	_yCoordinates.push_back(yCoordinates[i+1]);
	_zCoordinates.push_back(zCoordinates[i+1]);

	_xCoordinates.push_back(xCoordinates[i+2]);
	_yCoordinates.push_back(yCoordinates[i+2]);
	_zCoordinates.push_back(zCoordinates[i+2]);

	///////////////////////////////////////////////////

	//#pragma omp parallel for
	iREAL A[3], B[3], C[3];
	A[0] = xCoordinates[i];
	A[1] = yCoordinates[i];
	A[2] = zCoordinates[i];

	B[0] = xCoordinates[i+1];
	B[1] = yCoordinates[i+1];
	B[2] = zCoordinates[i+1];

	C[0] = xCoordinates[i+2];
	C[1] = yCoordinates[i+2];
	C[2] = zCoordinates[i+2];

	iREAL AB = sqrt((A[0]-B[0])*(A[0]-B[0])+(A[1]-B[1])*(A[1]-B[1])+(A[2]-B[2])*(A[2]-B[2]));
	iREAL BC = sqrt((B[0]-C[0])*(B[0]-C[0])+(B[1]-C[1])*(B[1]-C[1])+(B[2]-C[2])*(B[2]-C[2]));
	iREAL CA = sqrt((C[0]-A[0])*(C[0]-A[0])+(C[1]-A[1])*(C[1]-A[1])+(C[2]-A[2])*(C[2]-A[2]));

	iREAL hmin = std::min(std::min(AB, BC), CA);
	iREAL hmax = std::max(std::max(AB, BC), CA);

	if (hmin < min) min = hmin;
	if (hmax > max) max = hmax;

	_avgMeshSize += hmax - hmin;
  }

  if(min == 1E99) min = 0.0;

  _minMeshSize = min;
  _maxMeshSize = max;
  _avgMeshSize = _avgMeshSize / xCoordinates.size();

  compressFromVectors();
}

void demolish::Mesh::compressFromVectors()
{
  _uniqueVertices.clear();
  _triangleFaces.clear();

  //#pragma omp parallel for
  for(int i=0; i<_xCoordinates.size(); i+=3)
  {
	iREAL xA = _xCoordinates[i];
	iREAL yA = _yCoordinates[i];
	iREAL zA = _zCoordinates[i];

	iREAL xB = _xCoordinates[i+1];
	iREAL yB = _yCoordinates[i+1];
	iREAL zB = _zCoordinates[i+1];

	iREAL xC = _xCoordinates[i+2];
	iREAL yC = _yCoordinates[i+2];
	iREAL zC = _zCoordinates[i+2];

	std::map<unsigned int, demolish::Vertex> 	                hashToVerticesMap;
	std::map<unsigned int, unsigned int> 		    hashToUniqueVertexPositionMap;

	std::hash<std::string> v_hash;

	std::ostringstream ssA;
	ssA << xA << yA << zA;
	std::string A(ssA.str());
	unsigned int uniqueIDA = v_hash(A);

	if(hashToVerticesMap.count(uniqueIDA) == 0)
	{
	  hashToVerticesMap[uniqueIDA] = demolish::Vertex(xA, yA, zA);
	  _uniqueVertices.push_back(hashToVerticesMap[uniqueIDA]);
	  hashToUniqueVertexPositionMap[uniqueIDA] = _uniqueVertices.size()-1;
	}

	std::ostringstream ssB;
	ssB << xB << yB << zB;
	std::string B(ssB.str());
	unsigned int uniqueIDB = v_hash(B);

	if(hashToVerticesMap.count(uniqueIDB) == 0)
	{
	  hashToVerticesMap[uniqueIDB] = demolish::Vertex(xA, yA, zA);
	  _uniqueVertices.push_back(hashToVerticesMap[uniqueIDB]);
	  hashToUniqueVertexPositionMap[uniqueIDB] = _uniqueVertices.size()-1;
	}

	std::ostringstream ssC;
	ssC << xC << yC << zC;
	std::string C(ssC.str());
	unsigned int uniqueIDC = v_hash(C);

	if(hashToVerticesMap.count(uniqueIDC) == 0)
	{
	  hashToVerticesMap[uniqueIDC] = demolish::Vertex(xC, yC, zC);
	  _uniqueVertices.push_back(hashToVerticesMap[uniqueIDC]);
	  hashToUniqueVertexPositionMap[uniqueIDC] = _uniqueVertices.size()-1;
	}

	int a = hashToUniqueVertexPositionMap[uniqueIDA];
	int b = hashToUniqueVertexPositionMap[uniqueIDB];
	int c = hashToUniqueVertexPositionMap[uniqueIDC];
	std::array<int, 3> loc = {a, b, c};

    //#pragma omp critical
	_triangleFaces.push_back(loc);
  }
//  printf("compressed vertices: %i\n", _uniqueVertices.size());
}

void demolish::Mesh::compressFromVectors(
	std::vector<iREAL>& xCoordinates,
	std::vector<iREAL>& yCoordinates,
	std::vector<iREAL>& zCoordinates)
{
  std::hash<std::string> v_hash;
  std::map<unsigned int, std::array<iREAL,3>> vertices;

  //#pragma omp parallel for
  for(int i=0; i<xCoordinates.size(); i+=3)
  {
	iREAL xA = xCoordinates[i];
	iREAL yA = yCoordinates[i];
	iREAL zA = zCoordinates[i];

	iREAL xB = xCoordinates[i+1];
	iREAL yB = yCoordinates[i+1];
	iREAL zB = zCoordinates[i+1];

	iREAL xC = xCoordinates[i+2];
	iREAL yC = yCoordinates[i+2];
	iREAL zC = zCoordinates[i+2];

	std::map<unsigned int, Vertex> 	            hashToVerticesMap;
	std::map<unsigned int, unsigned int> 		hashToVertexPositionMap;

	std::ostringstream ssA;
	ssA << xA << yA << zA;
	std::string A(ssA.str());
	unsigned int uniqueIDA = v_hash(A);

	if(hashToVerticesMap.count(uniqueIDA) == 0)
	{
	  hashToVerticesMap[uniqueIDA] = demolish::Vertex(xA, yA, zA);
	  _uniqueVertices.push_back(hashToVerticesMap[uniqueIDA]);
	  hashToVertexPositionMap[uniqueIDA] = _uniqueVertices.size()-1;
	}

	std::ostringstream ssB;
	ssB << xB << yB << zB;
	std::string B(ssB.str());
	unsigned int uniqueIDB = v_hash(B);

	if(hashToVerticesMap.count(uniqueIDB) == 0)
	{
	  hashToVerticesMap[uniqueIDB] = demolish::Vertex(xB, yB, zB);
	  _uniqueVertices.push_back(hashToVerticesMap[uniqueIDB]);
	  hashToVertexPositionMap[uniqueIDB] = _uniqueVertices.size()-1;
	}

	std::ostringstream ssC;
	ssC << xC << yC << zC;
	std::string C(ssC.str());
	unsigned int uniqueIDC = v_hash(C);

	if(hashToVerticesMap.count(uniqueIDC) == 0)
	{
	  hashToVerticesMap[uniqueIDC] = demolish::Vertex(xC, yC, zC);
	  _uniqueVertices.push_back(hashToVerticesMap[uniqueIDC]);
	  hashToVertexPositionMap[uniqueIDC] = _uniqueVertices.size()-1;
	}

	int a = hashToVertexPositionMap[uniqueIDA];
	int b = hashToVertexPositionMap[uniqueIDB];
	int c = hashToVertexPositionMap[uniqueIDC];
	std::array<int, 3> loc = {a, b, c};

    //#pragma omp critical
	_triangleFaces.push_back(loc);
  }
}

void demolish::Mesh::flatten()
{
  _xCoordinates.clear();
  _yCoordinates.clear();
  _zCoordinates.clear();

  _maxMeshSize = 0;
  _minMeshSize = 1E99;

  iREAL min = 1E99;
  iREAL max = 0;

  //#pragma omp parallel for
  for(int i=0; i<_triangleFaces.size(); i++)
  {
    int idxA = _triangleFaces[i][0];
    int idxB = _triangleFaces[i][1];
    int idxC = _triangleFaces[i][2];

	demolish::Vertex A = _uniqueVertices[idxA];
	demolish::Vertex B = _uniqueVertices[idxB];
	demolish::Vertex C = _uniqueVertices[idxC];
	//std::cout << _triangleFaces[i][0] << " " << _triangleFaces[i][1] << " " << _triangleFaces[i][2] << std::endl;

	_xCoordinates.push_back(A[0]);
	_yCoordinates.push_back(A[1]);
	_zCoordinates.push_back(A[2]);

	_xCoordinates.push_back(B[0]);
	_yCoordinates.push_back(B[1]);
	_zCoordinates.push_back(B[2]);

	_xCoordinates.push_back(C[0]);
	_yCoordinates.push_back(C[1]);
	_zCoordinates.push_back(C[2]);

	iREAL AB = sqrt((A[0]-B[0])*(A[0]-B[0])+(A[1]-B[1])*(A[1]-B[1])+(A[2]-B[2])*(A[2]-B[2]));
	iREAL BC = sqrt((B[0]-C[0])*(B[0]-C[0])+(B[1]-C[1])*(B[1]-C[1])+(B[2]-C[2])*(B[2]-C[2]));
	iREAL CA = sqrt((C[0]-A[0])*(C[0]-A[0])+(C[1]-A[1])*(C[1]-A[1])+(C[2]-A[2])*(C[2]-A[2]));

	iREAL hmin = std::min(std::min(AB, BC), CA);
	iREAL hmax = std::max(std::max(AB, BC), CA);

	if (hmin < min) min = hmin;
	if (hmax > max) max = hmax;

	_avgMeshSize += hmax - hmin;
  }

  if(min == 1E99) min = 0.0;

  _minMeshSize = min;
  _maxMeshSize = max;
  _avgMeshSize = _avgMeshSize / _xCoordinates.size();
}

std::vector<demolish::Vertex> demolish::Mesh::getVertices()
{
    return _uniqueVertices;
}

std::vector<std::array<int, 3>> demolish::Mesh::getTriangles()
{
    return _triangleFaces;
}

void demolish::Mesh::flatten(
	std::vector<iREAL>& xCoordinates,
	std::vector<iREAL>& yCoordinates,
	std::vector<iREAL>& zCoordinates)
{
  _maxMeshSize = 0;
  _minMeshSize = 1E99;

  iREAL min = 1E99;
  iREAL max = 0;

  //#pragma omp parallel for
  for(int i=0; i<_triangleFaces.size(); i++)
  {
    int idxA = _triangleFaces[i][0]; 
    int idxB = _triangleFaces[i][1]; 
    int idxC = _triangleFaces[i][2]; 
	demolish::Vertex A = _uniqueVertices[idxA];
	demolish::Vertex B = _uniqueVertices[idxB];
	demolish::Vertex C = _uniqueVertices[idxC];

	xCoordinates.push_back(A[0]);
	yCoordinates.push_back(A[1]);
	zCoordinates.push_back(A[2]);

	xCoordinates.push_back(B[0]);
	yCoordinates.push_back(B[1]);
	zCoordinates.push_back(B[2]);

	xCoordinates.push_back(C[0]);
	yCoordinates.push_back(C[1]);
	zCoordinates.push_back(C[2]);


	iREAL AB = sqrt((A[0]-B[0])*(A[0]-B[0])+(A[1]-B[1])*(A[1]-B[1])+(A[2]-B[2])*(A[2]-B[2]));
	iREAL BC = sqrt((B[0]-C[0])*(B[0]-C[0])+(B[1]-C[1])*(B[1]-C[1])+(B[2]-C[2])*(B[2]-C[2]));
	iREAL CA = sqrt((C[0]-A[0])*(C[0]-A[0])+(C[1]-A[1])*(C[1]-A[1])+(C[2]-A[2])*(C[2]-A[2]));

	iREAL hmin = std::min(std::min(AB, BC), CA);
	iREAL hmax = std::max(std::max(AB, BC), CA);

	if (hmin < min) min = hmin;
	if (hmax > max) max = hmax;

	_avgMeshSize += hmax - hmin;
  }

  if(min == 1E99) min = 0.0;

  _minMeshSize = min;
  _maxMeshSize = max;
  _avgMeshSize = _avgMeshSize / _xCoordinates.size();
}

void demolish::Mesh::replace (
	std::vector<iREAL>& xCoordinates,
	std::vector<iREAL>& yCoordinates,
	std::vector<iREAL>& zCoordinates)
{
  _xCoordinates.clear();
  _yCoordinates.clear();
  _zCoordinates.clear();

  //#pragma omp parallel for
  for(int i=0; i<xCoordinates.size(); i+=3)
  {
	_xCoordinates.push_back(xCoordinates[i]);
	_yCoordinates.push_back(yCoordinates[i]);
	_zCoordinates.push_back(zCoordinates[i]);

	_xCoordinates.push_back(xCoordinates[i+1]);
	_yCoordinates.push_back(yCoordinates[i+1]);
	_zCoordinates.push_back(zCoordinates[i+1]);

	_xCoordinates.push_back(xCoordinates[i+2]);
	_yCoordinates.push_back(yCoordinates[i+2]);
	_zCoordinates.push_back(zCoordinates[i+2]);
  }

  compressFromVectors();
}

std::vector<iREAL> demolish::Mesh::getXCoordinatesAsVector()
{
  return _xCoordinates;
}

std::vector<iREAL> demolish::Mesh::getYCoordinatesAsVector()
{
  return _yCoordinates;
}

std::vector<iREAL> demolish::Mesh::getZCoordinatesAsVector()
{
  return _zCoordinates;
}

iREAL*  demolish::Mesh::getXCoordinates()
{
  return _xCoordinates.data();
}

iREAL*  demolish::Mesh::getYCoordinates()
{
  return _yCoordinates.data();
}

iREAL*  demolish::Mesh::getZCoordinates()
{
  return _zCoordinates.data();
}

void  demolish::Mesh::moveMeshToPosition(iREAL center[3])
{
  iREAL currentPosition[3] = {0,0,0};
  computeCenterOfGeometry(currentPosition);
  demolish::operators::moveMeshFromPositionToOrigin(_xCoordinates,
                                                    _yCoordinates,
                                                    _zCoordinates,
                                                    currentPosition);

  demolish::operators::moveMeshFromOriginToPosition(_xCoordinates,
                                                    _yCoordinates,
                                                    _zCoordinates,
                                                    center);
}

void demolish::Mesh::moveMeshFromPositionToOrigin(iREAL center[3])
{
  demolish::operators::moveMeshFromPositionToOrigin(_xCoordinates,
                                                    _yCoordinates,
                                                    _zCoordinates,
                                                    center);
}

void demolish::Mesh::moveMeshFromOriginToPosition(iREAL center[3])
{
  demolish::operators::moveMeshFromOriginToPosition(_xCoordinates,
                                                    _yCoordinates,
                                                    _zCoordinates,
                                                    center);
}

void demolish::Mesh::scaleXYZ(iREAL scale)
{
  iREAL currentPosition[3] = {0,0,0};
  computeCenterOfGeometry(currentPosition);
  demolish::operators::moveMeshFromPositionToOrigin(_xCoordinates, _yCoordinates, _zCoordinates, currentPosition);
  demolish::operators::scaleXYZ(_xCoordinates, _yCoordinates, _zCoordinates, scale, currentPosition);
}

void demolish::Mesh::rotateX(iREAL alphaX)
{
  demolish::operators::rotateX(
	  _xCoordinates, _yCoordinates, _zCoordinates, alphaX);
}

void demolish::Mesh::rotateY(iREAL alphaY)
{
  demolish::operators::rotateY(
	  _xCoordinates, _yCoordinates, _zCoordinates, alphaY);
}

void demolish::Mesh::rotateZ(iREAL alphaZ)
{
  demolish::operators::rotateZ(
	  _xCoordinates, _yCoordinates, _zCoordinates, alphaZ);
}




iREAL demolish::Mesh::computeDiameter()
{
  return demolish::operators::computeXYZw(
	  _xCoordinates, _yCoordinates, _zCoordinates);
}

iREAL demolish::Mesh::computeXYZw()
{
  return demolish::operators::computeXYZw(
	  _xCoordinates, _yCoordinates, _zCoordinates);
}

iREAL demolish::Mesh::computeXZw()
{
  return demolish::operators::computeXZw(
	  _xCoordinates, _yCoordinates, _zCoordinates);
}

iREAL demolish::Mesh::computeXw()
{
  return demolish::operators::computeXw(
	  _xCoordinates, _yCoordinates, _zCoordinates);
}

iREAL demolish::Mesh::computeYw()
{
  return demolish::operators::computeYw(
	  _xCoordinates, _yCoordinates, _zCoordinates);
}

iREAL demolish::Mesh::computeZw()
{
  return demolish::operators::computeZw(
	  _xCoordinates, _yCoordinates, _zCoordinates);
}

demolish::Vertex demolish::Mesh::computeBoundaryMinVertex()
{
  return demolish::operators::computeBoundaryMinVertex(
	  _xCoordinates, _yCoordinates, _zCoordinates);
}

demolish::Vertex demolish::Mesh::computeBoundaryMaxVertex()
{
  return demolish::operators::computeBoundaryMaxVertex(
	  _xCoordinates, _yCoordinates, _zCoordinates);
}

iREAL demolish::Mesh::computeDiagonal()
{
  return demolish::operators::computeDiagonal(
	  _xCoordinates, _yCoordinates, _zCoordinates);
}

void demolish::Mesh::computeCenterOfGeometry(
	iREAL centreOfGeometry[3])
{
  centreOfGeometry[0] = 0.0;
  centreOfGeometry[1] = 0.0;
  centreOfGeometry[2] = 0.0;

  unsigned nVertices = _xCoordinates.size();

  for(unsigned i=0;i<nVertices;i++)
  {
	centreOfGeometry[0] += (_xCoordinates[i]);
	centreOfGeometry[1] += (_yCoordinates[i]);
	centreOfGeometry[2] += (_zCoordinates[i]);
  }

  centreOfGeometry[0] = centreOfGeometry[0]/(nVertices);
  centreOfGeometry[1] = centreOfGeometry[1]/(nVertices);
  centreOfGeometry[2] = centreOfGeometry[2]/(nVertices);
}

void demolish::Mesh::computeCenterOfMass(
  iREAL&               centreOfMassX,
  iREAL&               centreOfMassY,
  iREAL&               centreOfMassZ,
  iREAL&               refcentreOfMassX,
  iREAL&               refcentreOfMassY,
  iREAL&               refcentreOfMassZ
) {
  centreOfMassX = 0.0;
  centreOfMassY = 0.0;
  centreOfMassZ = 0.0;

  unsigned nVertices = _xCoordinates.size();

  //#pragma omp parallel for
  for(unsigned i=0;i<nVertices;i++)
  {
    centreOfMassX += _xCoordinates[i];
    centreOfMassY += _yCoordinates[i];
    centreOfMassZ += _zCoordinates[i];
  }

  centreOfMassX = centreOfMassX/(nVertices*3);
  centreOfMassY = centreOfMassY/(nVertices*3);
  centreOfMassZ = centreOfMassZ/(nVertices*3);

  refcentreOfMassX = centreOfMassX;
  refcentreOfMassY = centreOfMassY;
  refcentreOfMassZ = centreOfMassZ;
}

void demolish::Mesh::computeExplode(
	                iREAL length
) {
  std::vector<iREAL> exCoordinates, eyCoordinates, ezCoordinates;

  //#pragma omp parallel for
  for(unsigned i=0; i<_xCoordinates.size(); i+=3)
  {
    iREAL A[3], B[3], C[3];
    A[0] = _xCoordinates[i];
    A[1] = _yCoordinates[i];
    A[2] = _zCoordinates[i];

    B[0] = _xCoordinates[i+1];
    B[1] = _yCoordinates[i+1];
    B[2] = _zCoordinates[i+1];

    C[0] = _xCoordinates[i+2];
    C[1] = _yCoordinates[i+2];
    C[2] = _zCoordinates[i+2];

    iREAL V[3], W[3], N[3];
    V[0] = B[0] - A[0];
    V[1] = B[1] - A[1];
    V[2] = B[2] - A[2];

    W[0] = C[0] - B[0];
    W[1] = C[1] - B[1];
    W[2] = C[2] - B[2];

    N[0] = (V[1]*W[2])-(V[2]*W[1]);
    N[1] = (V[2]*W[0])-(V[0]*W[2]);
    N[2] = (V[0]*W[1])-(V[1]*W[0]);

    iREAL mag = std::sqrt((N[0]*N[0])+(N[1]*N[1])+(N[2]*N[2]));
    N[0] = N[0]/mag;
    N[1] = N[1]/mag;
    N[2] = N[2]/mag;
    
   // #pragma omp critical
    {
        exCoordinates.push_back(_xCoordinates[i] + length * N[0]);
        eyCoordinates.push_back(_yCoordinates[i] + length * N[1]);
        ezCoordinates.push_back(_zCoordinates[i] + length * N[2]);

        exCoordinates.push_back(_xCoordinates[i+1] + length * N[0]);
        eyCoordinates.push_back(_yCoordinates[i+1] + length * N[1]);
        ezCoordinates.push_back(_zCoordinates[i+1] + length * N[2]);

        exCoordinates.push_back(_xCoordinates[i+2] + length * N[0]);
        eyCoordinates.push_back(_yCoordinates[i+2] + length * N[1]);
        ezCoordinates.push_back(_zCoordinates[i+2] + length * N[2]);
    }
  }

  _xCoordinates.insert(_xCoordinates.end(), exCoordinates.begin(), exCoordinates.end());
  _yCoordinates.insert(_yCoordinates.end(), eyCoordinates.begin(), eyCoordinates.end());
  _zCoordinates.insert(_zCoordinates.end(), ezCoordinates.begin(), ezCoordinates.end());
}

iREAL demolish::Mesh::computeHMin()
{
  iREAL min = 1E99;

  //#pragma omp parallel for
  for(unsigned i=0; i<_xCoordinates.size(); i+=3)
  {
	iREAL A[3], B[3], C[3];
	A[0] = _xCoordinates[i];
	A[1] = _yCoordinates[i];
	A[2] = _zCoordinates[i];

	B[0] = _xCoordinates[i+1];
	B[1] = _yCoordinates[i+1];
	B[2] = _zCoordinates[i+1];

	C[0] = _xCoordinates[i+2];
	C[1] = _yCoordinates[i+2];
	C[2] = _zCoordinates[i+2];

	iREAL AB = sqrt((A[0]-B[0])*(A[0]-B[0])+(A[1]-B[1])*(A[1]-B[1])+(A[2]-B[2])*(A[2]-B[2]));
	iREAL BC = sqrt((B[0]-C[0])*(B[0]-C[0])+(B[1]-C[1])*(B[1]-C[1])+(B[2]-C[2])*(B[2]-C[2]));
	iREAL CA = sqrt((C[0]-A[0])*(C[0]-A[0])+(C[1]-A[1])*(C[1]-A[1])+(C[2]-A[2])*(C[2]-A[2]));

	if (std::min(std::min(AB, BC), CA) < min)
	{
      //#pragma omp critical
	  min = std::min(std::min(AB, BC), CA);
	}
  }

  if(min == 1E99) min = 0.0;
  return min;
}

/*
 *gets the inertia using simplex integration from solfec
 */
void demolish::Mesh::computeInertia(
		demolish::material::MaterialType material,
		iREAL& mass,
		iREAL center[3],
		iREAL inertia[9])
{
  demolish::operators::computeInertia(
		_xCoordinates,
		_yCoordinates,
		_zCoordinates,
		material,
		mass,
		center,
		inertia);
}

iREAL demolish::Mesh::computeMass(
    demolish::material::MaterialType material)
{
  return demolish::operators::computeMass(
	  _xCoordinates, _yCoordinates, _zCoordinates, material);
}

void demolish::Mesh::computeInverseInertia(
    iREAL inertia[9],
    iREAL inverse[9],
    bool isObject)
{
  demolish::operators::computeInverseInertia(inertia, inverse, isObject);
}

iREAL demolish::Mesh::computeVolume()
{
  return demolish::operators::computeVolume(
	  _xCoordinates, _yCoordinates, _zCoordinates);
}

std::vector<std::array<int, 3>> demolish::Mesh::getTriangleFaces()
{
  return _triangleFaces;
}

std::vector<demolish::Vertex> demolish::Mesh::getUniqueVertices()
{
  return _uniqueVertices;
}

iREAL demolish::Mesh::getMaxMeshSize()
{
  return _maxMeshSize;
}

iREAL demolish::Mesh::getMinMeshSize()
{
  return _minMeshSize;
}

iREAL demolish::Mesh::getAvgMeshSize()
{
  return _avgMeshSize;
}

demolish::Vertex demolish::Mesh::getBoundaryMinVertex()
{
  return _minBoundary;
}

demolish::Vertex demolish::Mesh::getBoundaryMaxVertex()
{
  return _maxBoundary;
}

void demolish::Mesh::toString()
{
  for(int i=0; i<_xCoordinates.size(); i+=3)
  {
	std::cout << _xCoordinates[i] << _yCoordinates[i] << _zCoordinates[i];
	std::cout << _xCoordinates[i + 1] << _yCoordinates[i + 1] << _zCoordinates[i + 1];
	std::cout << _xCoordinates[i + 2] << _yCoordinates[i + 2] << _zCoordinates[i + 2];
  }
}

demolish::Mesh::Mesh::~Mesh() {

}
