
#include "Triangle.h"

crashr::Triangle::Triangle(
	Vertex& A,
	Vertex& B,
	Vertex& C)
{
  _A = A;
  _B = B;
  _C = C;
}

crashr::Triangle::Triangle(
	double A[3],
	double B[3],
	double C[3])
{
  _A.set(A[0], A[1], A[2]);
  _B.set(B[0], B[1], B[2]);
  _C.set(C[0], C[1], C[2]);
}

crashr::Triangle::Triangle(
	double Ax,
	double Ay,
	double Az,

	double Bx,
	double By,
	double Bz,

	double Cx,
	double Cy,
	double Cz)
{
  _A.set(Ax, Ay, Az);
  _B.set(Bx, By, Bz);
  _C.set(Cx, Cy, Cz);
}

Vertex crashr::Triangle::getVertexA()
{
  return _A;
}

Vertex crashr::Triangle::getVertexB()
{
  return _B;
}

Vertex crashr::Triangle::getVertexC()
{
  return _C;
}

double crashr::Triangle::getTriangleLength()
{
  double xw = crashr::Triangle::getXw();
  double yw = crashr::Triangle::getYw();
  double zw = crashr::Triangle::getZw();

  double tmp = xw > yw ? xw : yw;
  double width = tmp>zw ? tmp : zw;

  return getXYZWidth();
}

double crashr::Triangle::getXYZWidth()
{
  double xw = crashr::Triangle::getXw();
  double yw = crashr::Triangle::getYw();
  double zw = crashr::Triangle::getZw();

  double tmp = xw > yw ? xw : yw;
  double width = tmp>zw ? tmp : zw;

  return width;
}

double crashr::Triangle::getXZWidth()
{
  double xw = crashr::Triangle::getXw();
  double zw = crashr::Triangle::getZw();
  double width = xw>zw ? xw : zw;

  return width;
}

double crashr::Triangle::getXw()
{
  Vertex min = crashr::Triangle::getMinBoundaryVertex();
  Vertex max = crashr::Triangle::getMaxBoundaryVertex();

  return std::abs(min.getX() - max.getX());
}

double crashr::Triangle::getYw()
{
  Vertex min = crashr::Triangle::getMinBoundaryVertex();
  Vertex max = crashr::Triangle::getMaxBoundaryVertex();

  return std::abs(min.getY() - max.getY());
}

double crashr::Triangle::getZw()
{
  Vertex min = crashr::Triangle::getMinBoundaryVertex();
  Vertex max = crashr::Triangle::getMaxBoundaryVertex();

  return std::abs(min.getZ() - max.getZ());
}

Vertex crashr::Triangle::getMinBoundaryVertex()
{
  Vertex vertex(getMinXAxis(),getMinYAxis(),getMinZAxis());
  return vertex;
}

Vertex crashr::Triangle::getMaxBoundaryVertex()
{
  Vertex vertex(getMaxXAxis(),getMaxYAxis(),getMaxZAxis());
  return vertex;
}

double crashr::Triangle::getMaxXAxis()
{
  double x[3] = {_A.getX(), _B.getX(), _C.getX()};

  double max = std::numeric_limits<double>::min();

  for(unsigned i=0;i<3;i++)
  {
	if (max < x[i]) max = x[i];
  }
  return max;
}

double crashr::Triangle::getMaxYAxis()
{
  double y[3] = {_A.getY(), _B.getY(), _C.getY()};

  double max = std::numeric_limits<double>::min();

  for(unsigned i=0;i<3;i++)
  {
	if (max < y[i]) max = y[i];
  }
  return max;
}

double crashr::Triangle::getMaxZAxis()
{
  double z[3] = {_A.getZ(), _B.getZ(), _C.getZ()};

  double max = std::numeric_limits<double>::min();

  for(unsigned i=0; i<3; i++)
  {
	if (max < z[i]) max = z[i];
  }
  return max;
}

double crashr::Triangle::getMinXAxis()
{
  double x[3] = {_A.getX(), _B.getX(), _C.getX()};

  double min = std::numeric_limits<double>::max();

  for(unsigned i=0; i<3; i++)
  {
	if (min > x[i]) min = x[i];
  }
  return min;
}

double crashr::Triangle::getMinYAxis()
{
  double y[3] = {_A.getY(), _B.getY(), _C.getY()};

  double min = std::numeric_limits<double>::max();

  for(unsigned i=0; i<3; i++)
  {
	if (min > y[i]) min = y[i];
  }
  return min;
}

double crashr::Triangle::getMinZAxis()
{
  double z[3] = {_A.getZ(), _B.getZ(), _C.getZ()};

  double min = std::numeric_limits<double>::max();

  for(unsigned i=0; i<3; i++)
  {
	if (min > z[i]) min = z[i];
  }
  return min;
}

crashr::Triangle::~Triangle() {

}

