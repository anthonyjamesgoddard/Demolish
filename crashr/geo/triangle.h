
#ifndef TRIANGLE
#define TRIANGLE

#include"demolish.h"
#include"Vertex.h"
#include <map>
#include <vector>
#include <array>
#include <cmath>
#include <limits>

namespace demolish {

	  class Triangle;

}

using demolish::Vertex;

class demolish::Triangle {
  public:
	Triangle(
		Vertex& A,
		Vertex& B,
		Vertex& C);

	Triangle(
		iREAL A[3],
		iREAL B[3],
		iREAL C[3]);

	Triangle(
		iREAL Ax,
		iREAL Ay,
		iREAL Az,

		iREAL Bx,
		iREAL By,
		iREAL Bz,

		iREAL Cx,
		iREAL Cy,
		iREAL Cz);

	/*
	 *  Gets Vertex A
	 *
	 *  Returns the A vertex of the triangle
	 *
	 *  @param none
	 *  @returns std::array of three elements of type iREAL
	 */
	demolish::Vertex getVertexA();

	/*
	 *  Gets Vertex B
	 *
	 *  Returns the B vertex of the triangle
	 *
	 *  @param none
	 *  @returns std::array of three elements of type iREAL
	 */
	demolish::Vertex getVertexB();

	/*
	 *  Gets Vertex C
	 *
	 *  Returns the C vertex of the triangle
	 *
	 *  @param none
	 *  @returns std::array of three elements of type iREAL
	 */
	demolish::Vertex getVertexC();

	/*
	 *  Gets Minimum Boundary Vertex
	 *
	 *  Returns the minimum vertex that defines the bounding box of the triangle
	 *
	 *  @param none
	 *  @returns std::array of three elements of type iREAL
	 */
	demolish::Vertex getMinBoundaryVertex();

	/*
	 *  Gets Maximum Boundary Vertex
	 *
	 *  Returns the maximum vertex that defines the bounding box of the triangle
	 *
	 *  @param none
	 *  @returns std::array of three elements of type iREAL
	 */
	demolish::Vertex getMaxBoundaryVertex();

	/*
	 *  Gets Triangle Length
	 *
	 *  Returns maximum line segment length of triangle
	 *
	 *  @param none
	 *  @returns std::array of three elements of type iREAL
	 */
	iREAL getTriangleLength();

	/*
	 *  Gets Width X
	 *
	 *  Returns width of x axis coordinates
	 *
	 *  @param none
	 *  @returns type iREAL
	 */
	iREAL getXw();

	/*
	 *  Gets Width Y
	 *
	 *  Returns width of y axis coordinates
	 *
	 *  @param none
	 *  @returns type iREAL
	 */
	iREAL getYw();

	/*
	 *  Gets Width Y
	 *
	 *  Returns width of y axis coordinates
	 *
	 *  @param none
	 *  @returns type iREAL
	 */
	iREAL getZw();

	/*
	 *  Gets Max X
	 *
	 *  Returns max x axis value
	 *
	 *  @param none
	 *  @returns type iREAL
	 */
	iREAL getMaxXAxis();

	/*
	 *  Gets Max X
	 *
	 *  Returns max x axis value
	 *
	 *  @param none
	 *  @returns type iREAL
	 */
	iREAL getMaxYAxis();

	/*
	 *  Gets Max X
	 *
	 *  Returns max x axis value
	 *
	 *  @param none
	 *  @returns type iREAL
	 */
	iREAL getMaxZAxis();


	/*
	 *  Gets Max X
	 *
	 *  Returns max x axis value
	 *
	 *  @param none
	 *  @returns type iREAL
	 */
	iREAL getMinXAxis();

	/*
	 *  Gets Max Y
	 *
	 *  Returns max y axis value
	 *
	 *  @param none
	 *  @returns type iREAL
	 */
	iREAL getMinYAxis();

	/*
	 *  Gets Max Z
	 *
	 *  Returns max z axis value
	 *
	 *  @param none
	 *  @returns type iREAL
	 */
	iREAL getMinZAxis();

	/*
	 *  Gets XYZ width
	 *
	 *  Returns width on xyz axis.
	 *
	 *  @param none
	 *  @returns type iREAL
	 */
	iREAL getXYZWidth();

	/*
	 *  Gets XY width
	 *
	 *  Returns width on xy axis.
	 *
	 *  @param none
	 *  @returns type iREAL
	 */
	iREAL getXZWidth();

	virtual ~Triangle();
  private:
	Vertex _A, _B, _C;

};

#endif 
