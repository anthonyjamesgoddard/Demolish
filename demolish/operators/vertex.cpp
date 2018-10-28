

#include "vertex.h"


iREAL demolish::operators::computeXYZw(
	std::vector<iREAL> xCoordinates,
	std::vector<iREAL> yCoordinates,
	std::vector<iREAL> zCoordinates)
{
  iREAL xw = demolish::operators::computeXw(xCoordinates, yCoordinates, zCoordinates);
  iREAL yw = demolish::operators::computeYw(xCoordinates, yCoordinates, zCoordinates);
  iREAL zw = demolish::operators::computeZw(xCoordinates, yCoordinates, zCoordinates);

  iREAL tmp = xw > yw ? xw : yw;

  return tmp>zw ? tmp : zw;
}

iREAL demolish::operators::computeXZw(
	std::vector<iREAL> xCoordinates,
	std::vector<iREAL> yCoordinates,
	std::vector<iREAL> zCoordinates)
{
  iREAL xw = demolish::operators::computeXw(xCoordinates, yCoordinates, zCoordinates);
  iREAL zw = demolish::operators::computeZw(xCoordinates, yCoordinates, zCoordinates);

  return xw>zw ? xw : zw;
}

iREAL demolish::operators::computeXw(
	std::vector<iREAL> xCoordinates,
	std::vector<iREAL> yCoordinates,
	std::vector<iREAL> zCoordinates)
{
  demolish::Vertex min = demolish::operators::computeBoundaryMinVertex(xCoordinates, yCoordinates, zCoordinates);
  demolish::Vertex max = demolish::operators::computeBoundaryMaxVertex(xCoordinates, yCoordinates, zCoordinates);

  return std::abs(min.getX() - max.getX());
}

iREAL demolish::operators::computeYw(
	std::vector<iREAL> xCoordinates,
	std::vector<iREAL> yCoordinates,
	std::vector<iREAL> zCoordinates)
{
  demolish::Vertex min = demolish::operators::computeBoundaryMinVertex(xCoordinates, yCoordinates, zCoordinates);
  demolish::Vertex max = demolish::operators::computeBoundaryMaxVertex(xCoordinates, yCoordinates, zCoordinates);

  return std::abs(min.getY() - max.getY());
}

iREAL demolish::operators::computeZw(
	std::vector<iREAL> xCoordinates,
	std::vector<iREAL> yCoordinates,
	std::vector<iREAL> zCoordinates)
{
  demolish::Vertex min = demolish::operators::computeBoundaryMinVertex(xCoordinates, yCoordinates, zCoordinates);
  demolish::Vertex max = demolish::operators::computeBoundaryMaxVertex(xCoordinates, yCoordinates, zCoordinates);

  return std::abs(min.getZ() - max.getZ());
}

std::array<iREAL, 6> demolish::operators::computeBbox(
	std::vector<iREAL> xCoordinates,
	std::vector<iREAL> yCoordinates,
	std::vector<iREAL> zCoordinates)
{
  demolish::Vertex vertexMin = computeBoundaryMinVertex(xCoordinates, yCoordinates, zCoordinates);
  demolish::Vertex vertexMax = computeBoundaryMaxVertex(xCoordinates, yCoordinates, zCoordinates);

  std::array<iREAL, 6> bbox = {vertexMin.getX(), vertexMin.getY(), vertexMin.getZ(),
							   vertexMax.getX(), vertexMax.getY(), vertexMax.getZ()};
  return bbox;
}

demolish::Vertex demolish::operators::computeBoundaryMinVertex(
	std::vector<iREAL> xCoordinates,
	std::vector<iREAL> yCoordinates,
	std::vector<iREAL> zCoordinates)
{
  demolish::Vertex vertex = {computeMin(xCoordinates),
								computeMin(yCoordinates),
								computeMin(zCoordinates)};
  return vertex;
}

demolish::Vertex demolish::operators::computeBoundaryMaxVertex(
	std::vector<iREAL> xCoordinates,
	std::vector<iREAL> yCoordinates,
	std::vector<iREAL> zCoordinates)
{
  demolish::Vertex vertex = {computeMax(xCoordinates),
							computeMax(yCoordinates),
							computeMax(zCoordinates)};

  return vertex;
}

iREAL demolish::operators::computeDiagonal(
	std::vector<iREAL> xCoordinates,
	std::vector<iREAL> yCoordinates,
	std::vector<iREAL> zCoordinates)
{
  Vertex minPoint, maxPoint;

  minPoint = computeBoundaryMinVertex(xCoordinates, yCoordinates, zCoordinates);
  maxPoint = computeBoundaryMaxVertex(xCoordinates, yCoordinates, zCoordinates);

  return computeDistanceAB(minPoint,maxPoint);
}

iREAL demolish::operators::computeDistanceAB(
    demolish::Vertex A,
    demolish::Vertex B)
{
  return std::sqrt(((B.getX()-A.getX())*(B.getX()-A.getX()))
                  +((B.getY()-A.getY())*(B.getY()-A.getY()))
                  +((B.getZ()-A.getZ())*(B.getZ()-A.getZ())));
}

iREAL demolish::operators::computeMin(
	  std::vector<iREAL> coordinates)
{
  iREAL min = std::numeric_limits<iREAL>::max();

  for(unsigned i=0; i<coordinates.size(); i++)
  {
	if (coordinates[i] < min) min = coordinates[i];
  }
  return min;
}

iREAL demolish::operators::computeMax(
	  std::vector<iREAL> coordinates)
{
  iREAL max = std::numeric_limits<iREAL>::min();

  for(unsigned i=0; i<coordinates.size(); i++)
  {
     if (coordinates[i] > max) max = coordinates[i];
  }
  return max;
}
