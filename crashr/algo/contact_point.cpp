#include "contact_point.h"
#include <iomanip>

crashr::contact_point::contact_point() {}

crashr::contact_point::contact_point(const contact_point& copy)
    : distance(copy.distance),
      indexA(copy.indexA),
      indexB(copy.indexB),
      friction(copy.friction),
      depth(copy.depth) {
    x[0] = copy.x[0];
    x[1] = copy.x[1];
    x[2] = copy.x[2];

    normal[0] = copy.normal[0];
    normal[1] = copy.normal[1];
    normal[2] = copy.normal[2];
}

crashr::contact_point::contact_point(const double PA[3], const double QB[3],
                                       const bool& outside)
    : contact_point(PA[0], PA[1], PA[2], QB[0], QB[1], QB[2], outside) {}

crashr::contact_point::contact_point(const double& xPA, const double& yPA,
                                       const double& zPA,

                                       const double& xQB, const double& yQB,
                                       const double& zQB,

                                       const bool& outside)
    : indexA(-1), indexB(-1) {
    x[0] = (xPA + xQB) / 2.0;
    x[1] = (yPA + yQB) / 2.0;
    x[2] = (zPA + zQB) / 2.0;

    normal[0] = xPA - xQB;
    normal[1] = yPA - yQB;
    normal[2] = zPA - zQB;

    const double normalLength = std::sqrt(
        normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);

    normal[0] /= normalLength;
    normal[1] /= normalLength;
    normal[2] /= normalLength;

    distance = outside ? normalLength : -normalLength;

    // note that this version of the constructor is useless if we need depth
    // information.
    depth = 0;
    friction = true;
}

crashr::contact_point::contact_point(const double& xPA, const double& yPA,
                                       const double& zPA,

                                       const double& xQB, const double& yQB,
                                       const double& zQB,

                                       const bool& outside,

                                       const double& epsilonA,
                                       const double& epsilonB, bool fric)
    : indexA(-1), indexB(-1) {
    x[0] = (xPA + xQB) / 2.0;
    x[1] = (yPA + yQB) / 2.0;
    x[2] = (zPA + zQB) / 2.0;

    friction = fric;
    normal[0] = xPA - xQB;
    normal[1] = yPA - yQB;
    normal[2] = zPA - zQB;

    const double normalLength = std::sqrt(
        normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);

    normal[0] /= normalLength;
    normal[1] /= normalLength;
    normal[2] /= normalLength;

    distance = outside ? normalLength : -normalLength;

    depth = (epsilonA + epsilonB) - normalLength;
}

crashr::contact_point::contact_point(
    const double& xPA, const double& yPA, const double& zPA,

    const double& xQB, const double& yQB, const double& zQB,

    const bool& outside,

    const double& epsilonA, const double& epsilonB,

    const int& particleA, const int& particleB,

    bool fric)
    : indexA(particleA), indexB(particleB), friction(fric) {
    x[0] = (xPA + xQB) / 2.0;
    x[1] = (yPA + yQB) / 2.0;
    x[2] = (zPA + zQB) / 2.0;

    normal[0] = xPA - xQB;
    normal[1] = yPA - yQB;
    normal[2] = zPA - zQB;

    double normalLength = std::sqrt(
        normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);

    friction = fric;
    normal[0] /= normalLength;
    normal[1] /= normalLength;
    normal[2] /= normalLength;

    distance = outside ? normalLength : -normalLength;

    depth = (epsilonA + epsilonB) - normalLength;
}

void crashr::contact_point::printInformation() {
    std::cout << "\n Contact Point information \n " << std::endl;
    std::cout << "location of the contact point        : " << x[0] << " "
              << x[1] << " " << x[2] << std::endl;
    std::cout << "normal from i to j                   : " << normal[0] << " "
              << normal[1] << " " << normal[2] << std::endl;
    std::cout << "distance between particles           : " << distance
              << std::endl;
    std::cout << "the particles involved               : " << indexA << " "
              << indexB << std::endl;
    std::cout << "the depth                            : " << depth
              << std::endl;
    std::cout << "are these parts subject to friction? : " << friction
              << std::endl;
    std::cout << "\n" << std::endl;
}

