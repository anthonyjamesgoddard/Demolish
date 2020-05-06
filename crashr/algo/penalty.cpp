#include "penalty.h"
#include <algorithm>

int MaxNumberOfNewtonIterations = 120;
std::vector<demolish::ContactPoint> demolish::detection::penalty(
    const iREAL* xCoordinatesOfPointsOfGeometryA,
    const iREAL* yCoordinatesOfPointsOfGeometryA,
    const iREAL* zCoordinatesOfPointsOfGeometryA,
    const int numberOfTrianglesOfGeometryA, const iREAL epsilonA,
    const bool frictionA, const int particleA,

    const iREAL* xCoordinatesOfPointsOfGeometryB,
    const iREAL* yCoordinatesOfPointsOfGeometryB,
    const iREAL* zCoordinatesOfPointsOfGeometryB,
    const int numberOfTrianglesOfGeometryB, const iREAL epsilonB,
    const bool frictionB, const int particleB) {
    std::vector<demolish::ContactPoint> result;
    std::vector<iREAL> distanceVector;
    std::vector<demolish::ContactPoint> cnps;

    int numberOfTrianglesA = numberOfTrianglesOfGeometryA * 3;
    int numberOfTrianglesB = numberOfTrianglesOfGeometryB * 3;

    for (int iA = 0; iA < numberOfTrianglesA; iA += 3) {
        iREAL xPA[10000], yPA[10000], zPA[10000], xPB[10000], yPB[10000],
            zPB[10000], d[10000];
        for (int iB = 0; iB < numberOfTrianglesB; iB += 3) {
            bool failed = false;
            const iREAL MaxError = (epsilonA + epsilonB) / 16.0;
            penaltySolver(xCoordinatesOfPointsOfGeometryA + (iA),
                          yCoordinatesOfPointsOfGeometryA + (iA),
                          zCoordinatesOfPointsOfGeometryA + (iA),
                          xCoordinatesOfPointsOfGeometryB + (iB),
                          yCoordinatesOfPointsOfGeometryB + (iB),
                          zCoordinatesOfPointsOfGeometryB + (iB), xPA[iB],
                          yPA[iB], zPA[iB], xPB[iB], yPB[iB], zPB[iB], MaxError,
                          MaxNumberOfNewtonIterations);

            d[iB] = std::sqrt(((xPB[iB] - xPA[iB]) * (xPB[iB] - xPA[iB])) +
                              ((yPB[iB] - yPA[iB]) * (yPB[iB] - yPA[iB])) +
                              ((zPB[iB] - zPA[iB]) * (zPB[iB] - zPA[iB])));
        }

        iREAL epsilonMargin = 1 * (epsilonA + epsilonB);

        for (int iB = 0; iB < numberOfTrianglesB; iB += 3) {
            bool outside = true;
            if (d[iB] < epsilonMargin) {
                bool fric = bool(frictionA == true && frictionB == true);
                cnps.push_back(demolish::ContactPoint(
                    xPA[iB], yPA[iB], zPA[iB], xPB[iB], yPB[iB], zPB[iB],
                    outside, epsilonA, epsilonB, particleA, particleB, fric));

                distanceVector.push_back(d[iB]);
            }
        }
    }
    if (cnps.size() > 0) {
        int minElementIndex =
            std::min_element(distanceVector.begin(), distanceVector.end()) -
            distanceVector.begin();
        result.push_back(cnps[minElementIndex]);
    }

    return result;
}

void demolish::detection::penaltySolver(
    const iREAL* xCoordinatesOfTriangleA, const iREAL* yCoordinatesOfTriangleA,
    const iREAL* zCoordinatesOfTriangleA, const iREAL* xCoordinatesOfTriangleB,
    const iREAL* yCoordinatesOfTriangleB, const iREAL* zCoordinatesOfTriangleB,
    iREAL& xPA, iREAL& yPA, iREAL& zPA, iREAL& xPB, iREAL& yPB, iREAL& zPB,
    iREAL maxError, int& numberOfNewtonIterationsRequired) {
    iREAL BA[3];
    iREAL CA[3];
    iREAL ED[3];
    iREAL FD[3];
    iREAL hessian[16];
    iREAL x[4];

    BA[0] = xCoordinatesOfTriangleA[1] - xCoordinatesOfTriangleA[0];
    BA[1] = yCoordinatesOfTriangleA[1] - yCoordinatesOfTriangleA[0];
    BA[2] = zCoordinatesOfTriangleA[1] - zCoordinatesOfTriangleA[0];

    CA[0] = xCoordinatesOfTriangleA[2] - xCoordinatesOfTriangleA[0];
    CA[1] = yCoordinatesOfTriangleA[2] - yCoordinatesOfTriangleA[0];
    CA[2] = zCoordinatesOfTriangleA[2] - zCoordinatesOfTriangleA[0];

    ED[0] = xCoordinatesOfTriangleB[1] - xCoordinatesOfTriangleB[0];
    ED[1] = yCoordinatesOfTriangleB[1] - yCoordinatesOfTriangleB[0];
    ED[2] = zCoordinatesOfTriangleB[1] - zCoordinatesOfTriangleB[0];

    FD[0] = xCoordinatesOfTriangleB[2] - xCoordinatesOfTriangleB[0];
    FD[1] = yCoordinatesOfTriangleB[2] - yCoordinatesOfTriangleB[0];
    FD[2] = zCoordinatesOfTriangleB[2] - zCoordinatesOfTriangleB[0];

    hessian[0] = 2. * DOT(BA, BA);
    hessian[1] = 2. * DOT(CA, BA);
    hessian[2] = -2. * DOT(ED, BA);
    hessian[3] = -2. * DOT(FD, BA);

    hessian[4] = hessian[1];  // use symmetry
    hessian[5] = 2. * DOT(CA, CA);
    hessian[6] = -2. * DOT(ED, CA);
    hessian[7] = -2. * DOT(FD, CA);

    hessian[8] = hessian[2];
    hessian[9] = hessian[6];
    hessian[10] = 2. * DOT(ED, ED);
    hessian[11] = 2. * DOT(FD, ED);

    hessian[12] = hessian[3];
    hessian[13] = hessian[7];
    hessian[14] = hessian[11];
    hessian[15] = 2. * DOT(FD, FD);

    iREAL eps = 1E-2;
    iREAL delta = (hessian[0] + hessian[5] + hessian[10] + hessian[15]) * eps;
    iREAL lambda =
        sqrt(0.0125 * (hessian[0] + hessian[5] + hessian[10] + hessian[15]));
    iREAL r = lambda * 1E5;

    // initial guess
    x[0] = 0.33;
    x[1] = 0.33;
    x[2] = 0.33;
    x[3] = 0.33;

    // Newton loop
    for (int i = 0; i < MaxNumberOfNewtonIterations; i++) {
        // Declare loop variables;
        iREAL dx[4];
        iREAL a[16];
        iREAL SUBXY[3];
        iREAL b[4];
        iREAL dh[8];
        iREAL tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, mx[6];

        dh[0] = (-x[0] <= 0) ? 0.0 : -1;
        mx[0] = (-x[0] <= 0) ? 0.0 : -x[0];

        dh[2] = (-x[1] <= 0) ? 0.0 : -1;
        mx[1] = (-x[1] <= 0) ? 0.0 : -x[1];

        dh[1] = dh[3] = (x[0] + x[1] - 1 <= 0) ? 0.0 : 1;
        mx[2] = (x[0] + x[1] - 1 <= 0) ? 0.0 : x[0] + x[1] - 1;

        dh[4] = (-x[2] <= 0) ? 0.0 : -1;
        mx[3] = (-x[2] <= 0) ? 0.0 : -x[2];

        dh[6] = (-x[3] <= 0) ? 0.0 : -1;
        mx[4] = (-x[3] <= 0) ? 0.0 : -x[3];

        dh[5] = dh[7] = (x[2] + x[3] - 1 <= 0) ? 0.0 : 1;
        mx[5] = (x[2] + x[3] - 1 <= 0) ? 0.0 : x[2] + x[3] - 1;

        delta = i < 3 ? delta : 1E5 * delta;

        SUBXY[0] =
            (xCoordinatesOfTriangleA[0] + (BA[0] * x[0]) + (CA[0] * x[1])) -
            (xCoordinatesOfTriangleB[0] + (ED[0] * x[2]) + (FD[0] * x[3]));
        SUBXY[1] =
            (yCoordinatesOfTriangleA[0] + (BA[1] * x[0]) + (CA[1] * x[1])) -
            (yCoordinatesOfTriangleB[0] + (ED[1] * x[2]) + (FD[1] * x[3]));
        SUBXY[2] =
            (zCoordinatesOfTriangleA[0] + (BA[2] * x[0]) + (CA[2] * x[1])) -
            (zCoordinatesOfTriangleB[0] + (ED[2] * x[2]) + (FD[2] * x[3]));

        b[0] = 2 * DOT(SUBXY, BA) + r * (dh[0] * mx[0] + dh[1] * mx[2]);
        a[0] = hessian[0] + r * (dh[0] * dh[0] + dh[1] * dh[1]) + delta;
        a[4] = hessian[4] + r * (dh[3] * dh[1]);
        tmp1 = (hessian[1] + r * (dh[1] * dh[3])) / a[0];
        a[13] = hessian[13] - hessian[12] * tmp1;
        a[9] = hessian[9] - hessian[8] * tmp1;
        a[5] = (hessian[5] + r * (dh[2] * dh[2] + dh[3] * dh[3]) + delta) -
               a[4] * tmp1;
        b[1] = (2 * DOT(SUBXY, CA) + r * (dh[2] * mx[1] + dh[3] * mx[2])) -
               b[0] * tmp1;
        tmp2 = hessian[2] / a[0];
        tmp3 = hessian[3] / a[0];
        tmp4 = ((hessian[6]) - a[4] * tmp2) / a[5];
        a[14] = ((hessian[14] + r * (dh[7] * dh[5])) - hessian[12] * tmp2) -
                a[13] * tmp4;
        a[10] = ((hessian[10] + r * (dh[4] * dh[4] + dh[5] * dh[5]) + delta) -
                 hessian[8] * tmp2) -
                a[9] * tmp4;
        b[2] = ((-2 * DOT(SUBXY, ED) + r * (dh[4] * mx[3] + dh[5] * mx[5])) -
                b[0] * tmp2) -
               b[1] * tmp4;
        tmp5 = (hessian[7] - a[4] * tmp3) / a[5];
        tmp6 = (((hessian[11] + r * (dh[5] * dh[7])) - hessian[8] * tmp3) -
                a[9] * tmp5) /
               a[10];

        dx[3] = ((((-2 * DOT(SUBXY, FD) + r * (dh[6] * mx[4] + dh[7] * mx[5])) -
                   b[2] * tmp6) -
                  b[0] * tmp3) -
                 b[1] * tmp5) /
                ((((hessian[15] + r * (dh[6] * dh[6] + dh[7] * dh[7]) + delta) -
                   hessian[12] * tmp3) -
                  a[13] * tmp5) -
                 a[14] * tmp6);
        dx[2] = (b[2] - (a[14] * dx[3])) / a[10];
        dx[1] = (b[1] - (a[9] * dx[2] + a[13] * dx[3])) / a[5];
        dx[0] =
            (b[0] - (a[4] * dx[1] + hessian[8] * dx[2] + hessian[12] * dx[3])) /
            a[0];

        iREAL error = DOT4(dx, dx) / DOT4(x, x);

        if (error < maxError * maxError) {
            break;
        }

        x[0] = x[0] - dx[0];
        x[1] = x[1] - dx[1];
        x[2] = x[2] - dx[2];
        x[3] = x[3] - dx[3];
    }

    xPA = xCoordinatesOfTriangleA[0] + (BA[0] * x[0]) + (CA[0] * x[1]);
    yPA = yCoordinatesOfTriangleA[0] + (BA[1] * x[0]) + (CA[1] * x[1]);
    zPA = zCoordinatesOfTriangleA[0] + (BA[2] * x[0]) + (CA[2] * x[1]);

    xPB = xCoordinatesOfTriangleB[0] + (ED[0] * x[2]) + (FD[0] * x[3]);
    yPB = yCoordinatesOfTriangleB[0] + (ED[1] * x[2]) + (FD[1] * x[3]);
    zPB = zCoordinatesOfTriangleB[0] + (ED[2] * x[2]) + (FD[2] * x[3]);
}

