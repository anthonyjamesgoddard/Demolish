#pragma once

#include "geo/mesh.h"

namespace crashr {
namespace primitives {
class Cube;
}
}  // namespace crashr

/**
 * A cube
 */
class crashr::primitives::Cube : public crashr::Mesh {
private:
    const double _centre[3];
    const double _h;

    double* _xCoordinates;
    double* _yCoordinates;
    double* _zCoordinates;

    void discretise();

public:
    Cube(double centre[3], double h);

    Cube(double centreX, double centreY, double centreZ, double h);

    virtual ~Cube();

    double getCentreX() const;
    double getCentreY() const;
    double getCentreZ() const;

    double getBoundingSphereRadius() const;

    int getNumberOfTriangles() const;
    const double* getXCoordinates() const;
    const double* getYCoordinates() const;
    const double* getZCoordinates() const;
};

