#ifndef TRIANGLE
#define TRIANGLE

#include <array>
#include <cmath>
#include <limits>
#include <map>
#include <vector>
#include "geo/vertex.h"

namespace crashr {
class Triangle;
}

using crashr::Vertex;

class crashr::Triangle {
public:
    Triangle(Vertex& A, Vertex& B, Vertex& C);

    Triangle(double A[3], double B[3], double C[3]);

    Triangle(double Ax, double Ay, double Az,

             double Bx, double By, double Bz,

             double Cx, double Cy, double Cz);

    /*
     *  Gets Vertex A
     *
     *  Returns the A vertex of the triangle
     *
     *  @param none
     *  @returns std::array of three elements of type double
     */
    crashr::Vertex getVertexA();

    /*
     *  Gets Vertex B
     *
     *  Returns the B vertex of the triangle
     *
     *  @param none
     *  @returns std::array of three elements of type double
     */
    crashr::Vertex getVertexB();

    /*
     *  Gets Vertex C
     *
     *  Returns the C vertex of the triangle
     *
     *  @param none
     *  @returns std::array of three elements of type double
     */
    crashr::Vertex getVertexC();

    /*
     *  Gets Minimum Boundary Vertex
     *
     *  Returns the minimum vertex that defines the bounding box of the triangle
     *
     *  @param none
     *  @returns std::array of three elements of type double
     */
    crashr::Vertex getMinBoundaryVertex();

    /*
     *  Gets Maximum Boundary Vertex
     *
     *  Returns the maximum vertex that defines the bounding box of the triangle
     *
     *  @param none
     *  @returns std::array of three elements of type double
     */
    crashr::Vertex getMaxBoundaryVertex();

    /*
     *  Gets Triangle Length
     *
     *  Returns maximum line segment length of triangle
     *
     *  @param none
     *  @returns std::array of three elements of type double
     */
    double getTriangleLength();

    /*
     *  Gets Width X
     *
     *  Returns width of x axis coordinates
     *
     *  @param none
     *  @returns type double
     */
    double getXw();

    /*
     *  Gets Width Y
     *
     *  Returns width of y axis coordinates
     *
     *  @param none
     *  @returns type double
     */
    double getYw();

    /*
     *  Gets Width Y
     *
     *  Returns width of y axis coordinates
     *
     *  @param none
     *  @returns type double
     */
    double getZw();

    /*
     *  Gets Max X
     *
     *  Returns max x axis value
     *
     *  @param none
     *  @returns type double
     */
    double getMaxXAxis();

    /*
     *  Gets Max X
     *
     *  Returns max x axis value
     *
     *  @param none
     *  @returns type double
     */
    double getMaxYAxis();

    /*
     *  Gets Max X
     *
     *  Returns max x axis value
     *
     *  @param none
     *  @returns type double
     */
    double getMaxZAxis();

    /*
     *  Gets Max X
     *
     *  Returns max x axis value
     *
     *  @param none
     *  @returns type double
     */
    double getMinXAxis();

    /*
     *  Gets Max Y
     *
     *  Returns max y axis value
     *
     *  @param none
     *  @returns type double
     */
    double getMinYAxis();

    /*
     *  Gets Max Z
     *
     *  Returns max z axis value
     *
     *  @param none
     *  @returns type double
     */
    double getMinZAxis();

    /*
     *  Gets XYZ width
     *
     *  Returns width on xyz axis.
     *
     *  @param none
     *  @returns type double
     */
    double getXYZWidth();

    /*
     *  Gets XY width
     *
     *  Returns width on xy axis.
     *
     *  @param none
     *  @returns type double
     */
    double getXZWidth();

    virtual ~Triangle();

private:
    Vertex _A, _B, _C;
};

#endif
