#ifndef GEOMETRY_STRUCTURES_MESH_H_
#define GEOMETRY_STRUCTURES_MESH_H_

#include "Triangle.h"
#include "Vertex.h"

#include "algo.h"
#include "material.h"
#include "operators/mesh.h"
#include "operators/physics.h"
#include "operators/vertex.h"

namespace demolish {
class Mesh;
}

class demolish::Mesh {
public:
    Mesh();

    Mesh(std::vector<std::array<int, 3>>& triangleFaces,
         std::vector<Vertex>& uniqueVertices);

    Mesh(std::vector<iREAL>& xCoordinates, std::vector<iREAL>& yCoordinates,
         std::vector<iREAL>& zCoordinates);

    /*
     *  Flatten Data Structure
     *
     *  Returns the SoA data structure of the object oriented
     *  structure of triangles.
     *
     *  @param xCoordinates : x axis elements array of mesh
     *  @param yCoordinates : y axis elements array of mesh
     *  @param zCoordinates : z axis elements array of mesh
     *  @returns void but through parameters by reference
     */
    void flatten(std::vector<iREAL>& xCoordinates,
                 std::vector<iREAL>& yCoordinates,
                 std::vector<iREAL>& zCoordinates);

    /*
     *  Flatten Data Structure
     *
     *  Returns the SoA data structure of the object oriented
     *  structure of triangles.
     *
     *  @param xCoordinates : x axis elements array of mesh
     *  @param yCoordinates : y axis elements array of mesh
     *  @param zCoordinates : z axis elements array of mesh
     *  @returns void but through parameters by reference
     */
    void flatten();

    /*
     *  Replace Data Structure
     *
     *  Set SoA data structure with SoA passed.
     *  This modifies the local data.
     *
     *
     *  @param xCoordinates : x axis elements array of mesh
     *  @param yCoordinates : y axis elements array of mesh
     *  @param zCoordinates : z axis elements array of mesh
     *  @returns void
     */
    void replace(std::vector<iREAL>& xCoordinates,
                 std::vector<iREAL>& yCoordinates,
                 std::vector<iREAL>& zCoordinates);

    /*
     *  Move Mesh To Position
     *
     *  Set center of geometry to position.
     *  This modifies the local data.
     *
     *
     *  @param centre : centre of geometry
     *  @returns void
     */
    void shiftMesh(iREAL centre[3]);

    void rotateX(iREAL alphaX);

    /*
     *  Rotate Y
     *
     *  Rotate along Y axis by value.
     *  This modifies the local data.
     *
     *
     *  @param alphaY : rotation value 0-1 that correspond to 0 to 360 degrees.
     *  @returns void
     */
    void rotateY(iREAL alphaY);

    /*
     *  Rotate Z
     *
     *  Rotate along Z axis by value.
     *  This modifies the local data.
     *
     *
     *  @param alphaZ : rotation value 0-1 that correspond to 0 to 360 degrees.
     *  @returns void
     */
    void rotateZ(iREAL alphaZ);

    std::vector<Vertex> getVertices();
    std::vector<std::array<int, 3>> getTriangles();
    /*
     *  Compute Diagonal
     *
     *  Returns max diagonal in mesh
     *
     *
     *  @param none
     *  @returns iREAL
     */
    iREAL computeDiagonal();

    iREAL* getXCoordinates();

    iREAL* getYCoordinates();

    iREAL* getZCoordinates();

    iREAL* getPrevXCoordinates();

    iREAL* getPrevYCoordinates();

    iREAL* getPrevZCoordinates();

    /*
     *  Get Width of the X Coordinates
     *
     *  Returns width of x coordinates
     *
     *
     *  @param none
     *  @returns iREAL value
     */
    iREAL* getRefXCoordinates();

    /*
     *  Get Y Coordinates
     *
     *  Returns Y coordinates as SoA data structure.
     *
     *
     *  @param none
     *  @returns vector of iREAL values
     */
    iREAL* getRefYCoordinates();

    /*
     *  Get Z Coordinates
     *
     *  Returns Z coordinates as SoA data structure.
     *
     *
     *  @param none
     *  @returns vector of iREAL values
     */
    iREAL* getRefZCoordinates();

    /*
     *  Get Width of the X Coordinates
     *
     *  Returns width of x coordinates
     *
     *
     *  @param none
     *  @returns iREAL value
     */
    iREAL computeXw();

    /*
     *  Get Width of the Y Coordinates
     *
     *  Returns width of Y coordinates
     *
     *
     *  @param none
     *  @returns iREAL value
     */
    iREAL computeYw();

    /*
     *  Get Width of the Z Coordinates
     *
     *  Returns width of Z coordinates
     *
     *
     *  @param none
     *  @returns iREAL value
     */
    iREAL computeZw();

    /*
     *  Get Max Value on X Axis
     *
     *  Returns max value on X coordinates
     *
     *
     *  @param none
     *  @returns iREAL value
     */
    iREAL computeMaxXAxis();

    /*
     *  Get Max Value on Y Axis
     *
     *  Returns max value on Y coordinates
     *
     *
     *  @param none
     *  @returns iREAL value
     */
    iREAL computeMaxYAxis();

    /*
     *  Get Max Value on Z Axis
     *
     *  Returns max value on Z coordinates
     *
     *
     *  @param none
     *  @returns iREAL value
     */
    iREAL computeMaxZAxis();

    /*
     *  Get Min Value on X Axis
     *
     *  Returns min value on X coordinates
     *
     *
     *  @param none
     *  @returns iREAL value
     */
    iREAL computeMinXAxis();

    /*
     *  Get Min Value on Y Axis
     *
     *  Returns min value on Y coordinates
     *
     *
     *  @param none
     *  @returns iREAL value
     */
    iREAL computeMinYAxis();

    /*
     *  Get Min Value on Z Axis
     *
     *  Returns min value on Z coordinates
     *
     *
     *  @param none
     *  @returns iREAL value
     */
    iREAL computeMinZAxis();

    /*
     *  Get H Min
     *
     *  Returns min value of line segment length of mesh
     *
     *
     *  @param none
     *  @returns iREAL value
     */
    iREAL computeHMin();

    /*
     *  Get Min Boundary Vertex
     *
     *  Returns min vertex of mesh boundary
     *
     *
     *  @param none
     *  @returns xyz vertex
     */
    demolish::Vertex computeBoundaryMinVertex();

    /*
     *  Get Max Boundary Vertex
     *
     *  Returns max vertex of mesh boundary
     *
     *
     *  @param none
     *  @returns xyz vertex
     */
    demolish::Vertex computeBoundaryMaxVertex();

    /*
     *  Get XY Width
     *
     *  Returns width on XY coordinates.
     *
     *
     *  @param none
     *  @returns iREAL
     */
    iREAL computeXZw();

    /*
     *  Get Diameter Width
     *
     *  Returns diameter.
     *
     *
     *  @param none
     *  @returns iREAL
     */
    iREAL computeDiameter();

    /*
     *  Get Triangle Faces
     *
     *  Returns vector of triangle faces as
     *  an array of integer index pointers to unique vertices.
     *  The returned index pointers point to unique vertices as
     *  returned in "getUniqueVertices()" function and correspond
     *  to each of the three points of the triangle face.
     *
     *
     *  @param none
     *  @returns vector of arrays of index pointers
     */
    std::vector<std::array<int, 3>> getTriangleFaces();

    /*
     *  Get Unique Vertices
     *
     *  Returns vector of mesh unique vertices.
     *
     *
     *  @param none
     *  @returns vector of unique xyz vertices
     */
    std::vector<Vertex> getUniqueVertices();

    /*
     *  Get Center of Geometry
     *
     *  Returns center of Geometry through parameter.
     *
     *
     *  @param centreOfGeometry
     *  @returns void
     */
    void computeCenterOfGeometry(iREAL centreOfGeometry[3]);

    /*
     *  Get Center of Mass
     *
     *  Returns spatial and referential center of mass by reference.
     *
     *
     *  @param centreOfMassX
     *  @param centreOfMassY
     *  @param centreOfMassZ
     *  @param refcentreOfMassX
     *  @param refcentreOfMassY
     *  @param refcentreOfMassZ
     *
     *  @returns void
     */
    void computeCenterOfMass(iREAL& centreOfMassX, iREAL& centreOfMassY,
                             iREAL& centreOfMassZ, iREAL& refcentreOfMassX,
                             iREAL& refcentreOfMassY, iREAL& refcentreOfMassZ);

    /*
     *  Get X Coordinates
     *
     *  Returns vector of x axis coordinates of mess as SoA structure.
     *
     *
     *  @param none
     *  @returns vector
     */
    std::vector<iREAL> getXCoordinatesAsVector();

    /*
     *  Get X Coordinates
     *
     *  Returns vector of x axis coordinates of mess as SoA structure.
     *
     *
     *  @param none
     *  @returns vector
     */
    std::vector<iREAL> getYCoordinatesAsVector();

    /*
     *  Get X Coordinates
     *
     *  Returns vector of x axis coordinates of mess as SoA structure.
     *
     *
     *  @param none
     *  @returns vector
     */
    std::vector<iREAL> getZCoordinatesAsVector();

    void computeExplode(iREAL length);

    /*
     *  Get Mass
     *
     *  Returns mass using the passed material.
     *
     *
     *  @param material
     *  @returns iREAL
     */
    iREAL computeMass(demolish::material::MaterialType material);

    /*
     *  Get Volume
     *
     *  Returns volume.
     *
     *
     *  @param none
     *  @returns iREAL
     */
    iREAL computeVolume();

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
    void computeInertia(demolish::material::MaterialType material, iREAL& mass,
                        iREAL center[3], iREAL inertia[9]);

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
    void computeInverseInertia(iREAL inertia[9], iREAL inverse[9],
                               bool isObject);

    /*
     *  Get XYZ Width
     *
     *  Returns width on XYZ coordinates.
     *
     *
     *  @param none
     *  @returns iREAL
     */
    iREAL computeXYZw();

    iREAL getMaxMeshSize();
    iREAL getMinMeshSize();
    iREAL getAvgMeshSize();

    void setCurrentCoordinatesEqualToPrevCoordinates();
    void setPreviousCoordinatesEqualToCurrCoordinates();

    demolish::Vertex getBoundaryMinVertex();
    demolish::Vertex getBoundaryMaxVertex();

    virtual ~Mesh();

private:
    /*
     *  Compress from vectors
     *
     *  Compresses SoA data structure into triangle
     *  faces pointer and unique vertices.
     *  This modifies the local data.
     *
     *  @returns void
     */
    void compressFromVectors();

    /*
     *  Compress from vectors
     *
     *  Compresses SoA data structure into triangle
     *  faces pointer and unique vertices.
     *  This modifies the local data.
     *
     *  @returns void
     */
    void compressFromVectors(std::vector<iREAL>& xCoordinates,
                             std::vector<iREAL>& yCoordinates,
                             std::vector<iREAL>& zCoordinates);

    /*
     *  Print arrays to screen
     *
     *
     *  @returns void
     */

    void toString();

    std::vector<std::array<int, 3>> _triangleFaces;
    std::vector<demolish::Vertex> _uniqueVertices;

    std::vector<iREAL> _prevxCoordinates;
    std::vector<iREAL> _prevyCoordinates;
    std::vector<iREAL> _prevzCoordinates;

    std::vector<iREAL> _xCoordinates;
    std::vector<iREAL> _yCoordinates;
    std::vector<iREAL> _zCoordinates;

    std::vector<iREAL> _refxCoordinates;
    std::vector<iREAL> _refyCoordinates;
    std::vector<iREAL> _refzCoordinates;

    demolish::Vertex _minBoundary;
    demolish::Vertex _maxBoundary;

    // dimensions
    iREAL _wx;
    iREAL _wy;
    iREAL _wz;

    iREAL _maxMeshSize;
    iREAL _minMeshSize;
    iREAL _avgMeshSize;

#define TRACE(A) ((A)[0] + (A)[4] + (A)[8])

#define simplex_1(J, a, b, c, d) ((J) / 6.)
};

namespace demolish {
namespace operators {
void shiftMesh(std::vector<iREAL>& xCoordinates,
               std::vector<iREAL>& yCoordinates,
               std::vector<iREAL>& zCoordinates,
               std::vector<demolish::Vertex>& verts, iREAL center[3]);

void scaleXYZ(std::vector<iREAL>& xCoordinates,
              std::vector<iREAL>& yCoordinates,
              std::vector<iREAL>& zCoordinates,
              std::vector<demolish::Vertex>& verts, iREAL scale,
              iREAL position[3]);

void rotateX(std::vector<iREAL>& xCoordinates, std::vector<iREAL>& yCoordinates,
             std::vector<iREAL>& zCoordinates, iREAL alphaX);

void rotateY(std::vector<iREAL>& xCoordinates, std::vector<iREAL>& yCoordinates,
             std::vector<iREAL>& zCoordinates, iREAL alphaY);

void rotateZ(std::vector<iREAL>& xCoordinates, std::vector<iREAL>& yCoordinates,
             std::vector<iREAL>& zCoordinates, iREAL alphaZ);

}  // namespace operators
}  // namespace demolish
#endif
