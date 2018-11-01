
#include "Triangle.h"

demolish::Triangle::Triangle(
	Vertex& A,
	Vertex& B,
	Vertex& C)
{
  _A = A;
  _B = B;
  _C = C;
}

demolish::Triangle::Triangle(
	iREAL A[3],
	iREAL B[3],
	iREAL C[3])
{
  _A.set(A[0], A[1], A[2]);
  _B.set(B[0], B[1], B[2]);
  _C.set(C[0], C[1], C[2]);
}

demolish::Triangle::Triangle(
	iREAL Ax,
	iREAL Ay,
	iREAL Az,

	iREAL Bx,
	iREAL By,
	iREAL Bz,

	iREAL Cx,
	iREAL Cy,
	iREAL Cz)
{
  _A.set(Ax, Ay, Az);
  _B.set(Bx, By, Bz);
  _C.set(Cx, Cy, Cz);
}

Vertex demolish::Triangle::getVertexA()
{
  return _A;
}

Vertex demolish::Triangle::getVertexB()
{
  return _B;
}

Vertex demolish::Triangle::getVertexC()
{
  return _C;
}

iREAL demolish::Triangle::getTriangleLength()
{
  iREAL xw = demolish::Triangle::getXw();
  iREAL yw = demolish::Triangle::getYw();
  iREAL zw = demolish::Triangle::getZw();

  iREAL tmp = xw > yw ? xw : yw;
  iREAL width = tmp>zw ? tmp : zw;

  return getXYZWidth();
}

iREAL demolish::Triangle::getXYZWidth()
{
  iREAL xw = demolish::Triangle::getXw();
  iREAL yw = demolish::Triangle::getYw();
  iREAL zw = demolish::Triangle::getZw();

  iREAL tmp = xw > yw ? xw : yw;
  iREAL width = tmp>zw ? tmp : zw;

  return width;
}

iREAL demolish::Triangle::getXZWidth()
{
  iREAL xw = demolish::Triangle::getXw();
  iREAL zw = demolish::Triangle::getZw();
  iREAL width = xw>zw ? xw : zw;

  return width;
}

iREAL demolish::Triangle::getXw()
{
  Vertex min = demolish::Triangle::getMinBoundaryVertex();
  Vertex max = demolish::Triangle::getMaxBoundaryVertex();

  return std::abs(min.getX() - max.getX());
}

iREAL demolish::Triangle::getYw()
{
  Vertex min = demolish::Triangle::getMinBoundaryVertex();
  Vertex max = demolish::Triangle::getMaxBoundaryVertex();

  return std::abs(min.getY() - max.getY());
}

iREAL demolish::Triangle::getZw()
{
  Vertex min = demolish::Triangle::getMinBoundaryVertex();
  Vertex max = demolish::Triangle::getMaxBoundaryVertex();

  return std::abs(min.getZ() - max.getZ());
}

Vertex demolish::Triangle::getMinBoundaryVertex()
{
  Vertex vertex(getMinXAxis(),getMinYAxis(),getMinZAxis());
  return vertex;
}

Vertex demolish::Triangle::getMaxBoundaryVertex()
{
  Vertex vertex(getMaxXAxis(),getMaxYAxis(),getMaxZAxis());
  return vertex;
}

iREAL demolish::Triangle::getMaxXAxis()
{
  iREAL x[3] = {_A.getX(), _B.getX(), _C.getX()};

  iREAL max = std::numeric_limits<iREAL>::min();

  for(unsigned i=0;i<3;i++)
  {
	if (max < x[i]) max = x[i];
  }
  return max;
}

iREAL demolish::Triangle::getMaxYAxis()
{
  iREAL y[3] = {_A.getY(), _B.getY(), _C.getY()};

  iREAL max = std::numeric_limits<iREAL>::min();

  for(unsigned i=0;i<3;i++)
  {
	if (max < y[i]) max = y[i];
  }
  return max;
}

iREAL demolish::Triangle::getMaxZAxis()
{
  iREAL z[3] = {_A.getZ(), _B.getZ(), _C.getZ()};

  iREAL max = std::numeric_limits<iREAL>::min();

  for(unsigned i=0; i<3; i++)
  {
	if (max < z[i]) max = z[i];
  }
  return max;
}

iREAL demolish::Triangle::getMinXAxis()
{
  iREAL x[3] = {_A.getX(), _B.getX(), _C.getX()};

  iREAL min = std::numeric_limits<iREAL>::max();

  for(unsigned i=0; i<3; i++)
  {
	if (min > x[i]) min = x[i];
  }
  return min;
}

iREAL demolish::Triangle::getMinYAxis()
{
  iREAL y[3] = {_A.getY(), _B.getY(), _C.getY()};

  iREAL min = std::numeric_limits<iREAL>::max();

  for(unsigned i=0; i<3; i++)
  {
	if (min > y[i]) min = y[i];
  }
  return min;
}

iREAL demolish::Triangle::getMinZAxis()
{
  iREAL z[3] = {_A.getZ(), _B.getZ(), _C.getZ()};

  iREAL min = std::numeric_limits<iREAL>::max();

  for(unsigned i=0; i<3; i++)
  {
	if (min > z[i]) min = z[i];
  }
  return min;
}

demolish::Triangle::~Triangle() {

}

