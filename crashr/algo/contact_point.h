#pragma once

#include <cmath>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

namespace crashr {
/**
 * Simple struct representing a contact point
 */
struct contact_point {
    /**
     * Position in space
     */
    double x[3];

    /**
     * Normal onto next surface. Always normalised.
     */
    double normal[3];

    /**
     * Distance to next surface along normal. We use the sign to indicate
     * whether contact point is inside (negative) or outside (positive) of the
     * corresponding shapes.
     */
    double distance;

    /**
     * Allows us to tie a contact point to an object via an index
     */
    int indexA;
    int indexB;

    /**
     * Tells us how far the objects have overlapped
     */

    double depth;

    bool friction;

    contact_point();
    contact_point(const contact_point& copy);

    /**
     * This constructor is given two points on two triangles that are close to
     * each other. The points are PA and PB. The operation determines the
     * contact point at x,y,z (which is half the distance between the two
     * points PA and PB) and the corresponding normal xN,yN,zN.
     */
    contact_point(const double& xPA, const double& yPA, const double& zPA,

                 const double& xQB, const double& yQB, const double& zQB,

                 const bool& outside);

    contact_point(const double PA[3], const double QB[3], const bool& outside);

    contact_point(const double& xPA, const double& yPA, const double& zPA,

                 const double& xQB, const double& yQB, const double& zQB,

                 const bool& outside,

                 const double& epsilonA, const double& epsilonB,

                 bool fric);

    contact_point(const double& xPA, const double& yPA, const double& zPA,

                 const double& xQB, const double& yQB, const double& zQB,

                 const bool& outside,

                 const double& epsilonA, const double& epsilonB,

                 const int& particleA, const int& particleB,

                 bool fric);

    void printInformation();
};
}  // namespace crashr
