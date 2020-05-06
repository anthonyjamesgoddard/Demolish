#pragma once
#include "geo/mesh.h"

namespace crashr {
namespace primitives {
class Sphere;
}
}  // namespace crashr

class crashr::primitives::Sphere : public crashr::Mesh {
private:
    double _centre[3];
    double _radius;

public:
    Sphere(double centre[3], double radius, double h);

    Sphere(double centreX, double centreY, double centreZ, double radius,
           double h);

    double getCentreX() const;
    double getCentreY() const;
    double getCentreZ() const;

    double getBoundingSphereRadius() const;

    int getNumberOfTriangles() const;
    const double* getXCoordinates() const;
    const double* getYCoordinates() const;
    const double* getZCoordinates() const;
};

#endif

