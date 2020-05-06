#include "sphere.h"

std::vector<crashr::contact_point> crashr::detection::spherewithsphere(
    const double xCoordinatesOfPointsOfGeometryA,
    const double yCoordinatesOfPointsOfGeometryA,
    const double zCoordinatesOfPointsOfGeometryA, const double radA,
    const double epsilonA, const bool frictionA, const int particleA,

    const double xCoordinatesOfPointsOfGeometryB,
    const double yCoordinatesOfPointsOfGeometryB,
    const double zCoordinatesOfPointsOfGeometryB, const double radB,
    const double epsilonB, const bool frictionB, const int particleB) {
    std::vector<crashr::contact_point> result;

    double distance = std::sqrt(
        ((xCoordinatesOfPointsOfGeometryB - xCoordinatesOfPointsOfGeometryA) *
         (xCoordinatesOfPointsOfGeometryB - xCoordinatesOfPointsOfGeometryA)) +
        ((yCoordinatesOfPointsOfGeometryB - yCoordinatesOfPointsOfGeometryA) *
         (yCoordinatesOfPointsOfGeometryB - yCoordinatesOfPointsOfGeometryA)) +
        ((zCoordinatesOfPointsOfGeometryB - zCoordinatesOfPointsOfGeometryA) *
         (zCoordinatesOfPointsOfGeometryB - zCoordinatesOfPointsOfGeometryA)));

    if (distance > radA + radB + epsilonA + epsilonB) {
        return result;
    }

    double xd =
        xCoordinatesOfPointsOfGeometryB - xCoordinatesOfPointsOfGeometryA;
    double yd =
        yCoordinatesOfPointsOfGeometryB - yCoordinatesOfPointsOfGeometryA;
    double zd =
        zCoordinatesOfPointsOfGeometryB - zCoordinatesOfPointsOfGeometryA;

    double xnormal = (1.0 / distance) * xd;
    double ynormal = (1.0 / distance) * yd;
    double znormal = (1.0 / distance) * zd;

    double xPA = xCoordinatesOfPointsOfGeometryA + (radA * xnormal);
    double yPA = yCoordinatesOfPointsOfGeometryA + (radA * ynormal);
    double zPA = zCoordinatesOfPointsOfGeometryA + (radA * znormal);

    double xPB = xCoordinatesOfPointsOfGeometryB - (radB * xnormal);
    double yPB = yCoordinatesOfPointsOfGeometryB - (radB * ynormal);
    double zPB = zCoordinatesOfPointsOfGeometryB - (radB * znormal);

    bool outside = true;
    if (distance < radA + radB) outside = false;
    crashr::contact_point newcontact_point(xPA, yPA, zPA, xPB, yPB, zPB,
                                           outside, epsilonA, epsilonB,
                                           (frictionA && frictionB));
    newcontact_point.indexA = particleA;
    newcontact_point.indexB = particleB;
    result.push_back(newcontact_point);
    return result;
}

std::vector<crashr::contact_point> crashr::detection::sphereWithMesh(
    double xCoordinatesOfPointsOfGeometryA,
    double yCoordinatesOfPointsOfGeometryA,
    double zCoordinatesOfPointsOfGeometryA, double radA, double epsilonA,
    bool frictionA, int particleA,

    const double *xCoordinatesOfPointsOfGeometryB,
    const double *yCoordinatesOfPointsOfGeometryB,
    const double *zCoordinatesOfPointsOfGeometryB,
    int numberOfTrianglesOfGeometryB, double epsilonB, bool frictionB,
    int particleB) {
    std::vector<crashr::contact_point> result;

    for (int i = 0; i < numberOfTrianglesOfGeometryB * 3; i += 3) {
        double P[3], Q[3];
        double xPA, yPA, zPA, xPB, yPB, zPB;

        double TP1[3], TP2[3], TP3[3];
        TP1[0] = xCoordinatesOfPointsOfGeometryB[i];
        TP1[1] = yCoordinatesOfPointsOfGeometryB[i];
        TP1[2] = zCoordinatesOfPointsOfGeometryB[i];

        TP2[0] = xCoordinatesOfPointsOfGeometryB[i + 1];
        TP2[1] = yCoordinatesOfPointsOfGeometryB[i + 1];
        TP2[2] = zCoordinatesOfPointsOfGeometryB[i + 1];

        TP3[0] = xCoordinatesOfPointsOfGeometryB[i + 2];
        TP3[1] = yCoordinatesOfPointsOfGeometryB[i + 2];
        TP3[2] = zCoordinatesOfPointsOfGeometryB[i + 2];

        P[0] = xCoordinatesOfPointsOfGeometryA;
        P[1] = yCoordinatesOfPointsOfGeometryA;
        P[2] = zCoordinatesOfPointsOfGeometryA;

        // std::cout << TP1[0] << " " << TP1[1] << " " << TP1[2] << std::endl;
        // std::cout << TP2[0] << " " << TP2[1] << " " << TP2[2] << std::endl;
        // std::cout << TP3[0] << " " << TP3[1] << " " << TP3[2] << std::endl;
        double distance = crashr::detection::pt(TP1, TP2, TP3, P, Q) - radA;
        if (distance > epsilonA + epsilonB) continue;
        // std::cout << distance << std::endl;
        double xnormal = (Q[0] - P[0]) / (distance + radA);
        double ynormal = (Q[1] - P[1]) / (distance + radA);
        double znormal = (Q[2] - P[2]) / (distance + radA);

        xPA = P[0] + (radA * xnormal);
        yPA = P[1] + (radA * ynormal);
        zPA = P[2] + (radA * znormal);

        xPB = Q[0];
        yPB = Q[1];
        zPB = Q[2];

        bool outside = true;
        if (distance < 0) outside = false;
        crashr::contact_point newcontact_point(xPA, yPA, zPA, xPB, yPB, zPB,
                                               outside, epsilonA, epsilonB,
                                               (frictionA && frictionB));

        newcontact_point.indexA = particleA;
        newcontact_point.indexB = particleB;
        result.push_back(newcontact_point);
        break;
    }
    return result;
}
