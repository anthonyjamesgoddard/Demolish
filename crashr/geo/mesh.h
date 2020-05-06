#ifndef GEOMETRY_STRUCTURES_MESH_H_
#define GEOMETRY_STRUCTURES_MESH_H_

#include "Triangle.h"
#include "Vertex.h"

#include "algo.h"
#include "material.h"
#include "operators/mesh.h"
#include "operators/physics.h"
#include "operators/vertex.h"

namespace crashr {
class Mesh;
}

class crashr::Mesh {
public:
    Mesh();

    Mesh(std::vector<std::array<int, 3>>& triangleFaces,
         std::vector<Vertex>& uniqueVertices);

    Mesh(std::vector<double>& xCoordinates, std::vector<double>& yCoordinates,
         std::vector<double>& zCoordinates);

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
    void flatten(std::vector<double>& xCoordinates,
                 std::vector<double>& yCoordinates,
                 std::vector<double>& zCoordinates);

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
    void replace(std::vector<double>& xCoordinates,
                 std::vector<double>& yCoordinates,
                 std::vector<double>& zCoordinates);

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
    void shiftMesh(double centre[3]);

    void rotateX(double alphaX);

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
    void rotateY(double alphaY);

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
    void rotateZ(double alphaZ);

    std::vector<Vertex> getVertices();
    std::vector<std::array<int, 3>> getTriangles();
    /*
     *  Compute Diagonal
     *
     *  Returns max diagonal in mesh
     *
     *
     *  @param none
     *  @returns double
     */
    double computeDiagonal();

    double* getXCoordinates();

    double* getYCoordinates();

    double* getZCoordinates();

    double* getPrevXCoordinates();

    double* getPrevYCoordinates();

    double* getPrevZCoordinates();

    /*
     *  Get Width of the X Coordinates
     *
     *  Returns width of x coordinates
     *
     *
     *  @param none
     *  @returns double value
     */
    double* getRefXCoordinates();

    /*
     *  Get Y Coordinates
     *
     *  Returns Y coordinates as SoA data structure.
     *
     *
     *  @param none
     *  @returns vector of double values
     */
    double* getRefYCoordinates();

    /*
     *  Get Z Coordinates
     *
     *  Returns Z coordinates as SoA data structure.
     *
     *
     *  @param none
     *  @returns vector of double values
     */
    double* getRefZCoordinates();

    /*
     *  Get Width of the X Coordinates
     *
     *  Returns width of x coordinates
     *
     *
     *  @param none
     *  @returns double value
     */
    double computeXw();

    /*
     *  Get Width of the Y Coordinates
     *
     *  Returns width of Y coordinates
     *
     *
     *  @param none
     *  @returns double value
     */
    double computeYw();

    /*
     *  Get Width of the Z Coordinates
     *
     *  Returns width of Z coordinates
     *
     *
     *  @param none
     *  @returns double value
     */
    double computeZw();

    /*
     *  Get Max Value on X Axis
     *
     *  Returns max value on X coordinates
     *
     *
     *  @param none
     *  @returns double value
     */
    double computeMaxXAxis();

    /*
     *  Get Max Value on Y Axis
     *
     *  Returns max value on Y coordinates
     *
     *
     *  @param none
     *  @returns double value
     */
    double computeMaxYAxis();

    /*
     *  Get Max Value on Z Axis
     *
     *  Returns max value on Z coordinates
     *
     *
     *  @param none
     *  @returns double value
     */
    double computeMaxZAxis();

    /*
     *  Get Min Value on X Axis
     *
     *  Returns min value on X coordinates
     *
     *
     *  @param none
     *  @returns double value
     */
    double computeMinXAxis();

    /*
     *  Get Min Value on Y Axis
     *
     *  Returns min value on Y coordinates
     *
     *
     *  @param none
     *  @returns double value
     */
    double computeMinYAxis();

    /*
     *  Get Min Value on Z Axis
     *
     *  Returns min value on Z coordinates
     *
     *
     *  @param none
     *  @returns double value
     */
    double computeMinZAxis();

    /*
     *  Get H Min
     *
     *  Returns min value of line segment length of mesh
     *
     *
     *  @param none
     *  @returns double value
     */
    double computeHMin();

    /*
     *  Get Min Boundary Vertex
     *
     *  Returns min vertex of mesh boundary
     *
     *
     *  @param none
     *  @returns xyz vertex
     */
    crashr::Vertex computeBoundaryMinVertex();

    /*
     *  Get Max Boundary Vertex
     *
     *  Returns max vertex of mesh boundary
     *
     *
     *  @param none
     *  @returns xyz vertex
     */
    crashr::Vertex computeBoundaryMaxVertex();

    /*
     *  Get XY Width
     *
     *  Returns width on XY coordinates.
     *
     *
     *  @param none
     *  @returns double
     */
    double computeXZw();

    /*
     *  Get Diameter Width
     *
     *  Returns diameter.
     *
     *
     *  @param none
     *  @returns double
     */
    double computeDiameter();

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
    void computeCenterOfGeometry(double centreOfGeometry[3]);

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
    void computeCenterOfMass(double& centreOfMassX, double& centreOfMassY,
                             double& centreOfMassZ, double& refcentreOfMassX,
                             double& refcentreOfMassY, double& refcentreOfMassZ);

    /*
     *  Get X Coordinates
     *
     *  Returns vector of x axis coordinates of mess as SoA structure.
     *
     *
     *  @param none
     *  @returns vector
     */
    std::vector<double> getXCoordinatesAsVector();

    /*
     *  Get X Coordinates
     *
     *  Returns vector of x axis coordinates of mess as SoA structure.
     *
     *
     *  @param none
     *  @returns vector
     */
    std::vector<double> getYCoordinatesAsVector();

    /*
     *  Get X Coordinates
     *
     *  Returns vector of x axis coordinates of mess as SoA structure.
     *
     *
     *  @param none
     *  @returns vector
     */
    std::vector<double> getZCoordinatesAsVector();

    void computeExplode(double length);

    /*
     *  Get Mass
     *
     *  Returns mass using the passed material.
     *
     *
     *  @param material
     *  @returns double
     */
    double computeMass(crashr::material::MaterialType material);

    /*
     *  Get Volume
     *
     *  Returns volume.
     *
     *
     *  @param none
     *  @returns double
     */
    double computeVolume();

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
    void computeInertia(crashr::material::MaterialType material, double& mass,
                        double center[3], double inertia[9]);

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
    void computeInverseInertia(double inertia[9], double inverse[9],
                               bool isObject);

    /*
     *  Get XYZ Width
     *
     *  Returns width on XYZ coordinates.
     *
     *
     *  @param none
     *  @returns double
     */
    double computeXYZw();

    double getMaxMeshSize();
    double getMinMeshSize();
    double getAvgMeshSize();

    void setCurrentCoordinatesEqualToPrevCoordinates();
    void setPreviousCoordinatesEqualToCurrCoordinates();

    crashr::Vertex getBoundaryMinVertex();
    crashr::Vertex getBoundaryMaxVertex();

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
    void compressFromVectors(std::vector<double>& xCoordinates,
                             std::vector<double>& yCoordinates,
                             std::vector<double>& zCoordinates);

    /*
     *  Print arrays to screen
     *
     *
     *  @returns void
     */

    void toString();

    std::vector<std::array<int, 3>> _triangleFaces;
    std::vector<crashr::Vertex> _uniqueVertices;

    std::vector<double> _prevxCoordinates;
    std::vector<double> _prevyCoordinates;
    std::vector<double> _prevzCoordinates;

    std::vector<double> _xCoordinates;
    std::vector<double> _yCoordinates;
    std::vector<double> _zCoordinates;

    std::vector<double> _refxCoordinates;
    std::vector<double> _refyCoordinates;
    std::vector<double> _refzCoordinates;

    crashr::Vertex _minBoundary;
    crashr::Vertex _maxBoundary;

    // dimensions
    double _wx;
    double _wy;
    double _wz;

    double _maxMeshSize;
    double _minMeshSize;
    double _avgMeshSize;

#define TRACE(A) ((A)[0] + (A)[4] + (A)[8])

#define simplex_1(J, a, b, c, d) ((J) / 6.)
};

namespace crashr {
namespace operators {
void shiftMesh(std::vector<double>& xCoordinates,
               std::vector<double>& yCoordinates,
               std::vector<double>& zCoordinates,
               std::vector<crashr::Vertex>& verts, double center[3]);

void scaleXYZ(std::vector<double>& xCoordinates,
              std::vector<double>& yCoordinates,
              std::vector<double>& zCoordinates,
              std::vector<crashr::Vertex>& verts, double scale,
              double position[3]);

void rotateX(std::vector<double>& xCoordinates, std::vector<double>& yCoordinates,
             std::vector<double>& zCoordinates, double alphaX);

void rotateY(std::vector<double>& xCoordinates, std::vector<double>& yCoordinates,
             std::vector<double>& zCoordinates, double alphaY);

void rotateZ(std::vector<double>& xCoordinates, std::vector<double>& yCoordinates,
             std::vector<double>& zCoordinates, double alphaZ);

}  // namespace operators
}  // namespace crashr
#endif
