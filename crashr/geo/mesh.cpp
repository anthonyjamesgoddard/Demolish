#include "geo/mesh.h"

#include <array>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

crashr::Mesh::Mesh() {}

crashr::Mesh::Mesh(std::vector<std::array<int, 3>>& triangleFaces,
                     std::vector<Vertex>& uniqueVertices) {
    _triangleFaces = triangleFaces;
    _uniqueVertices = uniqueVertices;

    crashr::Mesh::flatten();
}

crashr::Mesh::Mesh(std::vector<double>& xCoordinates,
                     std::vector<double>& yCoordinates,
                     std::vector<double>& zCoordinates) {
    _maxMeshSize = 0;
    _minMeshSize = 1E99;

    double min = 1E99;
    double max = 0;

    //#pragma omp parallel for
    for (int i = 0; i < xCoordinates.size(); i += 3) {
        _xCoordinates.push_back(xCoordinates[i]);
        _yCoordinates.push_back(yCoordinates[i]);
        _zCoordinates.push_back(zCoordinates[i]);

        _xCoordinates.push_back(xCoordinates[i + 1]);
        _yCoordinates.push_back(yCoordinates[i + 1]);
        _zCoordinates.push_back(zCoordinates[i + 1]);

        _xCoordinates.push_back(xCoordinates[i + 2]);
        _yCoordinates.push_back(yCoordinates[i + 2]);
        _zCoordinates.push_back(zCoordinates[i + 2]);

        ///////////////////////////////////////////////////

        //#pragma omp parallel for
        double A[3], B[3], C[3];
        A[0] = xCoordinates[i];
        A[1] = yCoordinates[i];
        A[2] = zCoordinates[i];

        B[0] = xCoordinates[i + 1];
        B[1] = yCoordinates[i + 1];
        B[2] = zCoordinates[i + 1];

        C[0] = xCoordinates[i + 2];
        C[1] = yCoordinates[i + 2];
        C[2] = zCoordinates[i + 2];

        double AB =
            sqrt((A[0] - B[0]) * (A[0] - B[0]) + (A[1] - B[1]) * (A[1] - B[1]) +
                 (A[2] - B[2]) * (A[2] - B[2]));
        double BC =
            sqrt((B[0] - C[0]) * (B[0] - C[0]) + (B[1] - C[1]) * (B[1] - C[1]) +
                 (B[2] - C[2]) * (B[2] - C[2]));
        double CA =
            sqrt((C[0] - A[0]) * (C[0] - A[0]) + (C[1] - A[1]) * (C[1] - A[1]) +
                 (C[2] - A[2]) * (C[2] - A[2]));

        double hmin = std::min(std::min(AB, BC), CA);
        double hmax = std::max(std::max(AB, BC), CA);

        if (hmin < min) min = hmin;
        if (hmax > max) max = hmax;

        _avgMeshSize += hmax - hmin;
    }

    if (min == 1E99) min = 0.0;

    _minMeshSize = min;
    _maxMeshSize = max;
    _avgMeshSize = _avgMeshSize / xCoordinates.size();

    compressFromVectors();
}

void crashr::Mesh::compressFromVectors() {
    _uniqueVertices.clear();
    _triangleFaces.clear();

    //#pragma omp parallel for
    for (int i = 0; i < _xCoordinates.size(); i += 3) {
        double xA = _xCoordinates[i];
        double yA = _yCoordinates[i];
        double zA = _zCoordinates[i];

        double xB = _xCoordinates[i + 1];
        double yB = _yCoordinates[i + 1];
        double zB = _zCoordinates[i + 1];

        double xC = _xCoordinates[i + 2];
        double yC = _yCoordinates[i + 2];
        double zC = _zCoordinates[i + 2];

        std::map<unsigned int, crashr::Vertex> hashToVerticesMap;
        std::map<unsigned int, unsigned int> hashToUniqueVertexPositionMap;

        std::hash<std::string> v_hash;

        std::ostringstream ssA;
        ssA << xA << yA << zA;
        std::string A(ssA.str());
        unsigned int uniqueIDA = v_hash(A);

        if (hashToVerticesMap.count(uniqueIDA) == 0) {
            hashToVerticesMap[uniqueIDA] = crashr::Vertex(xA, yA, zA);
            _uniqueVertices.push_back(hashToVerticesMap[uniqueIDA]);
            hashToUniqueVertexPositionMap[uniqueIDA] =
                _uniqueVertices.size() - 1;
        }

        std::ostringstream ssB;
        ssB << xB << yB << zB;
        std::string B(ssB.str());
        unsigned int uniqueIDB = v_hash(B);

        if (hashToVerticesMap.count(uniqueIDB) == 0) {
            hashToVerticesMap[uniqueIDB] = crashr::Vertex(xA, yA, zA);
            _uniqueVertices.push_back(hashToVerticesMap[uniqueIDB]);
            hashToUniqueVertexPositionMap[uniqueIDB] =
                _uniqueVertices.size() - 1;
        }

        std::ostringstream ssC;
        ssC << xC << yC << zC;
        std::string C(ssC.str());
        unsigned int uniqueIDC = v_hash(C);

        if (hashToVerticesMap.count(uniqueIDC) == 0) {
            hashToVerticesMap[uniqueIDC] = crashr::Vertex(xC, yC, zC);
            _uniqueVertices.push_back(hashToVerticesMap[uniqueIDC]);
            hashToUniqueVertexPositionMap[uniqueIDC] =
                _uniqueVertices.size() - 1;
        }

        int a = hashToUniqueVertexPositionMap[uniqueIDA];
        int b = hashToUniqueVertexPositionMap[uniqueIDB];
        int c = hashToUniqueVertexPositionMap[uniqueIDC];
        std::array<int, 3> loc = {a, b, c};

        //#pragma omp critical
        _triangleFaces.push_back(loc);
    }
    //  printf("compressed vertices: %i\n", _uniqueVertices.size());
}

void crashr::Mesh::compressFromVectors(std::vector<double>& xCoordinates,
                                         std::vector<double>& yCoordinates,
                                         std::vector<double>& zCoordinates) {
    std::hash<std::string> v_hash;
    std::map<unsigned int, std::array<double, 3>> vertices;

    //#pragma omp parallel for
    for (int i = 0; i < xCoordinates.size(); i += 3) {
        double xA = xCoordinates[i];
        double yA = yCoordinates[i];
        double zA = zCoordinates[i];

        double xB = xCoordinates[i + 1];
        double yB = yCoordinates[i + 1];
        double zB = zCoordinates[i + 1];

        double xC = xCoordinates[i + 2];
        double yC = yCoordinates[i + 2];
        double zC = zCoordinates[i + 2];

        std::map<unsigned int, Vertex> hashToVerticesMap;
        std::map<unsigned int, unsigned int> hashToVertexPositionMap;

        std::ostringstream ssA;
        ssA << xA << yA << zA;
        std::string A(ssA.str());
        unsigned int uniqueIDA = v_hash(A);

        if (hashToVerticesMap.count(uniqueIDA) == 0) {
            hashToVerticesMap[uniqueIDA] = crashr::Vertex(xA, yA, zA);
            _uniqueVertices.push_back(hashToVerticesMap[uniqueIDA]);
            hashToVertexPositionMap[uniqueIDA] = _uniqueVertices.size() - 1;
        }

        std::ostringstream ssB;
        ssB << xB << yB << zB;
        std::string B(ssB.str());
        unsigned int uniqueIDB = v_hash(B);

        if (hashToVerticesMap.count(uniqueIDB) == 0) {
            hashToVerticesMap[uniqueIDB] = crashr::Vertex(xB, yB, zB);
            _uniqueVertices.push_back(hashToVerticesMap[uniqueIDB]);
            hashToVertexPositionMap[uniqueIDB] = _uniqueVertices.size() - 1;
        }

        std::ostringstream ssC;
        ssC << xC << yC << zC;
        std::string C(ssC.str());
        unsigned int uniqueIDC = v_hash(C);

        if (hashToVerticesMap.count(uniqueIDC) == 0) {
            hashToVerticesMap[uniqueIDC] = crashr::Vertex(xC, yC, zC);
            _uniqueVertices.push_back(hashToVerticesMap[uniqueIDC]);
            hashToVertexPositionMap[uniqueIDC] = _uniqueVertices.size() - 1;
        }

        int a = hashToVertexPositionMap[uniqueIDA];
        int b = hashToVertexPositionMap[uniqueIDB];
        int c = hashToVertexPositionMap[uniqueIDC];
        std::array<int, 3> loc = {a, b, c};

        //#pragma omp critical
        _triangleFaces.push_back(loc);
    }
}

void crashr::Mesh::flatten() {
    _xCoordinates.clear();
    _yCoordinates.clear();
    _zCoordinates.clear();

    _maxMeshSize = 0;
    _minMeshSize = 1E99;

    double min = 1E99;
    double max = 0;

    //#pragma omp parallel for
    for (int i = 0; i < _triangleFaces.size(); i++) {
        int idxA = _triangleFaces[i][0];
        int idxB = _triangleFaces[i][1];
        int idxC = _triangleFaces[i][2];

        crashr::Vertex A = _uniqueVertices[idxA];
        crashr::Vertex B = _uniqueVertices[idxB];
        crashr::Vertex C = _uniqueVertices[idxC];

        _xCoordinates.push_back(A[0]);
        _yCoordinates.push_back(A[1]);
        _zCoordinates.push_back(A[2]);

        _xCoordinates.push_back(B[0]);
        _yCoordinates.push_back(B[1]);
        _zCoordinates.push_back(B[2]);

        _xCoordinates.push_back(C[0]);
        _yCoordinates.push_back(C[1]);
        _zCoordinates.push_back(C[2]);

        _refxCoordinates.push_back(A[0]);
        _refyCoordinates.push_back(A[1]);
        _refzCoordinates.push_back(A[2]);

        _refxCoordinates.push_back(B[0]);
        _refyCoordinates.push_back(B[1]);
        _refzCoordinates.push_back(B[2]);

        _refxCoordinates.push_back(C[0]);
        _refyCoordinates.push_back(C[1]);
        _refzCoordinates.push_back(C[2]);

        double AB =
            sqrt((A[0] - B[0]) * (A[0] - B[0]) + (A[1] - B[1]) * (A[1] - B[1]) +
                 (A[2] - B[2]) * (A[2] - B[2]));
        double BC =
            sqrt((B[0] - C[0]) * (B[0] - C[0]) + (B[1] - C[1]) * (B[1] - C[1]) +
                 (B[2] - C[2]) * (B[2] - C[2]));
        double CA =
            sqrt((C[0] - A[0]) * (C[0] - A[0]) + (C[1] - A[1]) * (C[1] - A[1]) +
                 (C[2] - A[2]) * (C[2] - A[2]));

        double hmin = std::min(std::min(AB, BC), CA);
        double hmax = std::max(std::max(AB, BC), CA);

        if (hmin < min) min = hmin;
        if (hmax > max) max = hmax;

        _avgMeshSize += hmax - hmin;
    }

    if (min == 1E99) min = 0.0;

    _minMeshSize = min;
    _maxMeshSize = max;
    _avgMeshSize = _avgMeshSize / _xCoordinates.size();
}

std::vector<crashr::Vertex> crashr::Mesh::getVertices() {
    return _uniqueVertices;
}

std::vector<std::array<int, 3>> crashr::Mesh::getTriangles() {
    return _triangleFaces;
}

void crashr::Mesh::flatten(std::vector<double>& xCoordinates,
                             std::vector<double>& yCoordinates,
                             std::vector<double>& zCoordinates) {
    _maxMeshSize = 0;
    _minMeshSize = 1E99;

    double min = 1E99;
    double max = 0;

    //#pragma omp parallel for
    for (int i = 0; i < _triangleFaces.size(); i++) {
        int idxA = _triangleFaces[i][0];
        int idxB = _triangleFaces[i][1];
        int idxC = _triangleFaces[i][2];
        crashr::Vertex A = _uniqueVertices[idxA];
        crashr::Vertex B = _uniqueVertices[idxB];
        crashr::Vertex C = _uniqueVertices[idxC];

        xCoordinates.push_back(A[0]);
        yCoordinates.push_back(A[1]);
        zCoordinates.push_back(A[2]);

        xCoordinates.push_back(B[0]);
        yCoordinates.push_back(B[1]);
        zCoordinates.push_back(B[2]);

        xCoordinates.push_back(C[0]);
        yCoordinates.push_back(C[1]);
        zCoordinates.push_back(C[2]);

        double AB =
            sqrt((A[0] - B[0]) * (A[0] - B[0]) + (A[1] - B[1]) * (A[1] - B[1]) +
                 (A[2] - B[2]) * (A[2] - B[2]));
        double BC =
            sqrt((B[0] - C[0]) * (B[0] - C[0]) + (B[1] - C[1]) * (B[1] - C[1]) +
                 (B[2] - C[2]) * (B[2] - C[2]));
        double CA =
            sqrt((C[0] - A[0]) * (C[0] - A[0]) + (C[1] - A[1]) * (C[1] - A[1]) +
                 (C[2] - A[2]) * (C[2] - A[2]));

        double hmin = std::min(std::min(AB, BC), CA);
        double hmax = std::max(std::max(AB, BC), CA);

        if (hmin < min) min = hmin;
        if (hmax > max) max = hmax;

        _avgMeshSize += hmax - hmin;
    }

    if (min == 1E99) min = 0.0;

    _minMeshSize = min;
    _maxMeshSize = max;
    _avgMeshSize = _avgMeshSize / _xCoordinates.size();
}

void crashr::Mesh::replace(std::vector<double>& xCoordinates,
                             std::vector<double>& yCoordinates,
                             std::vector<double>& zCoordinates) {
    _xCoordinates.clear();
    _yCoordinates.clear();
    _zCoordinates.clear();

    //#pragma omp parallel for
    for (int i = 0; i < xCoordinates.size(); i += 3) {
        _xCoordinates.push_back(xCoordinates[i]);
        _yCoordinates.push_back(yCoordinates[i]);
        _zCoordinates.push_back(zCoordinates[i]);

        _xCoordinates.push_back(xCoordinates[i + 1]);
        _yCoordinates.push_back(yCoordinates[i + 1]);
        _zCoordinates.push_back(zCoordinates[i + 1]);

        _xCoordinates.push_back(xCoordinates[i + 2]);
        _yCoordinates.push_back(yCoordinates[i + 2]);
        _zCoordinates.push_back(zCoordinates[i + 2]);
    }

    compressFromVectors();
}

std::vector<double> crashr::Mesh::getXCoordinatesAsVector() {
    return _xCoordinates;
}

std::vector<double> crashr::Mesh::getYCoordinatesAsVector() {
    return _yCoordinates;
}

std::vector<double> crashr::Mesh::getZCoordinatesAsVector() {
    return _zCoordinates;
}

double* crashr::Mesh::getXCoordinates() { return _xCoordinates.data(); }

double* crashr::Mesh::getYCoordinates() { return _yCoordinates.data(); }

double* crashr::Mesh::getZCoordinates() { return _zCoordinates.data(); }

double* crashr::Mesh::getPrevXCoordinates() {
    return _prevxCoordinates.data();
}

double* crashr::Mesh::getPrevYCoordinates() {
    return _prevyCoordinates.data();
}

double* crashr::Mesh::getPrevZCoordinates() {
    return _prevzCoordinates.data();
}

double* crashr::Mesh::getRefXCoordinates() { return _refxCoordinates.data(); }

double* crashr::Mesh::getRefYCoordinates() { return _refyCoordinates.data(); }

double* crashr::Mesh::getRefZCoordinates() { return _refzCoordinates.data(); }

void crashr::Mesh::shiftMesh(double centre[3]) {
    crashr::operators::shiftMesh(_xCoordinates, _yCoordinates, _zCoordinates,
                                   _uniqueVertices, centre);
}

void crashr::Mesh::rotateX(double alphaX) {
    crashr::operators::rotateX(_xCoordinates, _yCoordinates, _zCoordinates,
                                 alphaX);
}

void crashr::Mesh::rotateY(double alphaY) {
    crashr::operators::rotateY(_xCoordinates, _yCoordinates, _zCoordinates,
                                 alphaY);
}

void crashr::Mesh::rotateZ(double alphaZ) {
    crashr::operators::rotateZ(_xCoordinates, _yCoordinates, _zCoordinates,
                                 alphaZ);
}

void crashr::Mesh::setCurrentCoordinatesEqualToPrevCoordinates() {
    _xCoordinates = _prevxCoordinates;
    _yCoordinates = _prevyCoordinates;
    _zCoordinates = _prevzCoordinates;
}

void crashr::Mesh::setPreviousCoordinatesEqualToCurrCoordinates() {
    _prevxCoordinates = _xCoordinates;
    _prevyCoordinates = _yCoordinates;
    _prevzCoordinates = _zCoordinates;
}

double crashr::Mesh::computeDiameter() {
    return crashr::operators::computeXYZw(_xCoordinates, _yCoordinates,
                                            _zCoordinates);
}

double crashr::Mesh::computeXYZw() {
    return crashr::operators::computeXYZw(_xCoordinates, _yCoordinates,
                                            _zCoordinates);
}

double crashr::Mesh::computeXZw() {
    return crashr::operators::computeXZw(_xCoordinates, _yCoordinates,
                                           _zCoordinates);
}

double crashr::Mesh::computeXw() {
    return crashr::operators::computeXw(_xCoordinates, _yCoordinates,
                                          _zCoordinates);
}

double crashr::Mesh::computeYw() {
    return crashr::operators::computeYw(_xCoordinates, _yCoordinates,
                                          _zCoordinates);
}

double crashr::Mesh::computeZw() {
    return crashr::operators::computeZw(_xCoordinates, _yCoordinates,
                                          _zCoordinates);
}

crashr::Vertex crashr::Mesh::computeBoundaryMinVertex() {
    return crashr::operators::computeBoundaryMinVertex(
        _xCoordinates, _yCoordinates, _zCoordinates);
}

crashr::Vertex crashr::Mesh::computeBoundaryMaxVertex() {
    return crashr::operators::computeBoundaryMaxVertex(
        _xCoordinates, _yCoordinates, _zCoordinates);
}

double crashr::Mesh::computeDiagonal() {
    return crashr::operators::computeDiagonal(_xCoordinates, _yCoordinates,
                                                _zCoordinates);
}

void crashr::Mesh::computeCenterOfGeometry(double centreOfGeometry[3]) {
    centreOfGeometry[0] = 0.0;
    centreOfGeometry[1] = 0.0;
    centreOfGeometry[2] = 0.0;

    unsigned nVertices = _xCoordinates.size();

    for (unsigned i = 0; i < nVertices; i++) {
        centreOfGeometry[0] += (_xCoordinates[i]);
        centreOfGeometry[1] += (_yCoordinates[i]);
        centreOfGeometry[2] += (_zCoordinates[i]);
    }

    centreOfGeometry[0] = centreOfGeometry[0] / (nVertices);
    centreOfGeometry[1] = centreOfGeometry[1] / (nVertices);
    centreOfGeometry[2] = centreOfGeometry[2] / (nVertices);
}

void crashr::Mesh::computeCenterOfMass(
    double& centreOfMassX, double& centreOfMassY, double& centreOfMassZ,
    double& refcentreOfMassX, double& refcentreOfMassY, double& refcentreOfMassZ) {
    centreOfMassX = 0.0;
    centreOfMassY = 0.0;
    centreOfMassZ = 0.0;

    unsigned nVertices = _xCoordinates.size();

    //#pragma omp parallel for
    for (unsigned i = 0; i < nVertices; i++) {
        centreOfMassX += _xCoordinates[i];
        centreOfMassY += _yCoordinates[i];
        centreOfMassZ += _zCoordinates[i];
    }

    centreOfMassX = centreOfMassX / (nVertices * 3);
    centreOfMassY = centreOfMassY / (nVertices * 3);
    centreOfMassZ = centreOfMassZ / (nVertices * 3);

    refcentreOfMassX = centreOfMassX;
    refcentreOfMassY = centreOfMassY;
    refcentreOfMassZ = centreOfMassZ;
}

void crashr::Mesh::computeExplode(double length) {
    std::vector<double> exCoordinates, eyCoordinates, ezCoordinates;

    //#pragma omp parallel for
    for (unsigned i = 0; i < _xCoordinates.size(); i += 3) {
        double A[3], B[3], C[3];
        A[0] = _xCoordinates[i];
        A[1] = _yCoordinates[i];
        A[2] = _zCoordinates[i];

        B[0] = _xCoordinates[i + 1];
        B[1] = _yCoordinates[i + 1];
        B[2] = _zCoordinates[i + 1];

        C[0] = _xCoordinates[i + 2];
        C[1] = _yCoordinates[i + 2];
        C[2] = _zCoordinates[i + 2];

        double V[3], W[3], N[3];
        V[0] = B[0] - A[0];
        V[1] = B[1] - A[1];
        V[2] = B[2] - A[2];

        W[0] = C[0] - B[0];
        W[1] = C[1] - B[1];
        W[2] = C[2] - B[2];

        N[0] = (V[1] * W[2]) - (V[2] * W[1]);
        N[1] = (V[2] * W[0]) - (V[0] * W[2]);
        N[2] = (V[0] * W[1]) - (V[1] * W[0]);

        double mag = std::sqrt((N[0] * N[0]) + (N[1] * N[1]) + (N[2] * N[2]));
        N[0] = N[0] / mag;
        N[1] = N[1] / mag;
        N[2] = N[2] / mag;

        // #pragma omp critical
        {
            exCoordinates.push_back(_xCoordinates[i] + length * N[0]);
            eyCoordinates.push_back(_yCoordinates[i] + length * N[1]);
            ezCoordinates.push_back(_zCoordinates[i] + length * N[2]);

            exCoordinates.push_back(_xCoordinates[i + 1] + length * N[0]);
            eyCoordinates.push_back(_yCoordinates[i + 1] + length * N[1]);
            ezCoordinates.push_back(_zCoordinates[i + 1] + length * N[2]);

            exCoordinates.push_back(_xCoordinates[i + 2] + length * N[0]);
            eyCoordinates.push_back(_yCoordinates[i + 2] + length * N[1]);
            ezCoordinates.push_back(_zCoordinates[i + 2] + length * N[2]);
        }
    }

    _xCoordinates.insert(_xCoordinates.end(), exCoordinates.begin(),
                         exCoordinates.end());
    _yCoordinates.insert(_yCoordinates.end(), eyCoordinates.begin(),
                         eyCoordinates.end());
    _zCoordinates.insert(_zCoordinates.end(), ezCoordinates.begin(),
                         ezCoordinates.end());
}

double crashr::Mesh::computeHMin() {
    double min = 1E99;

    //#pragma omp parallel for
    for (unsigned i = 0; i < _xCoordinates.size(); i += 3) {
        double A[3], B[3], C[3];
        A[0] = _xCoordinates[i];
        A[1] = _yCoordinates[i];
        A[2] = _zCoordinates[i];

        B[0] = _xCoordinates[i + 1];
        B[1] = _yCoordinates[i + 1];
        B[2] = _zCoordinates[i + 1];

        C[0] = _xCoordinates[i + 2];
        C[1] = _yCoordinates[i + 2];
        C[2] = _zCoordinates[i + 2];

        double AB =
            sqrt((A[0] - B[0]) * (A[0] - B[0]) + (A[1] - B[1]) * (A[1] - B[1]) +
                 (A[2] - B[2]) * (A[2] - B[2]));
        double BC =
            sqrt((B[0] - C[0]) * (B[0] - C[0]) + (B[1] - C[1]) * (B[1] - C[1]) +
                 (B[2] - C[2]) * (B[2] - C[2]));
        double CA =
            sqrt((C[0] - A[0]) * (C[0] - A[0]) + (C[1] - A[1]) * (C[1] - A[1]) +
                 (C[2] - A[2]) * (C[2] - A[2]));

        if (std::min(std::min(AB, BC), CA) < min) {
            //#pragma omp critical
            min = std::min(std::min(AB, BC), CA);
        }
    }

    if (min == 1E99) min = 0.0;
    return min;
}

/*
 *gets the inertia using simplex integration from solfec
 */
void crashr::Mesh::computeInertia(crashr::material::MaterialType material,
                                    double& mass, double center[3],
                                    double inertia[9]) {
    crashr::operators::computeInertia(_xCoordinates, _yCoordinates,
                                        _zCoordinates, material, mass, center,
                                        inertia);
}

double crashr::Mesh::computeMass(crashr::material::MaterialType material) {
    return crashr::operators::computeMass(_xCoordinates, _yCoordinates,
                                            _zCoordinates, material);
}

void crashr::Mesh::computeInverseInertia(double inertia[9], double inverse[9],
                                           bool isObject) {
    crashr::operators::computeInverseInertia(inertia, inverse, isObject);
}

double crashr::Mesh::computeVolume() {
    return crashr::operators::computeVolume(_xCoordinates, _yCoordinates,
                                              _zCoordinates);
}

std::vector<std::array<int, 3>> crashr::Mesh::getTriangleFaces() {
    return _triangleFaces;
}

std::vector<crashr::Vertex> crashr::Mesh::getUniqueVertices() {
    return _uniqueVertices;
}

double crashr::Mesh::getMaxMeshSize() { return _maxMeshSize; }

double crashr::Mesh::getMinMeshSize() { return _minMeshSize; }

double crashr::Mesh::getAvgMeshSize() { return _avgMeshSize; }

crashr::Vertex crashr::Mesh::getBoundaryMinVertex() { return _minBoundary; }

crashr::Vertex crashr::Mesh::getBoundaryMaxVertex() { return _maxBoundary; }

void crashr::Mesh::toString() {
    for (int i = 0; i < _xCoordinates.size(); i += 3) {
        std::cout << _xCoordinates[i] << _yCoordinates[i] << _zCoordinates[i];
        std::cout << _xCoordinates[i + 1] << _yCoordinates[i + 1]
                  << _zCoordinates[i + 1];
        std::cout << _xCoordinates[i + 2] << _yCoordinates[i + 2]
                  << _zCoordinates[i + 2];
    }
}

crashr::Mesh::Mesh::~Mesh() {}

void crashr::operators::shiftMesh(std::vector<double>& xCoordinates,
                                    std::vector<double>& yCoordinates,
                                    std::vector<double>& zCoordinates,
                                    std::vector<crashr::Vertex>& verts,
                                    double center[3]) {
#ifdef OMPProcess
    //	#pragma omp parallel for
#endif
    for (unsigned i = 0; i < xCoordinates.size(); i++) {
        xCoordinates[i] = xCoordinates[i] - center[0];
        yCoordinates[i] = yCoordinates[i] - center[1];
        zCoordinates[i] = zCoordinates[i] - center[2];
    }

    // we only need this for the visualisation.
    // there is something I can do to deal with this.
    crashr::Vertex shift(center[0], center[1], center[2]);

    for (unsigned i = 0; i < verts.size(); i++) {
        verts[i] = verts[i] - shift;
    }
}

void crashr::operators::scaleXYZ(std::vector<double>& xCoordinates,
                                   std::vector<double>& yCoordinates,
                                   std::vector<double>& zCoordinates,
                                   std::vector<crashr::Vertex>& verts,
                                   double scale, double position[3]) {
    crashr::operators::shiftMesh(xCoordinates, yCoordinates, zCoordinates,
                                   verts, position);

    for (unsigned i = 0; i < xCoordinates.size(); i++) {
        xCoordinates[i] = xCoordinates[i] * scale;
        yCoordinates[i] = yCoordinates[i] * scale;
        zCoordinates[i] = zCoordinates[i] * scale;
    }
    double backToPosition[3] = {-position[0], -position[1], -position[2]};
    crashr::operators::shiftMesh(xCoordinates, yCoordinates, zCoordinates,
                                   verts, backToPosition);
}

void crashr::operators::rotateX(std::vector<double>& xCoordinates,
                                  std::vector<double>& yCoordinates,
                                  std::vector<double>& zCoordinates,
                                  double alphaX) {
    const double pi = std::acos(-1);

    for (unsigned i = 0; i < xCoordinates.size(); i++) {
        double x = xCoordinates[i];
        double y = yCoordinates[i];
        double z = zCoordinates[i];

        double M[] = {1.0,
                     0.0,
                     0.0,
                     0.0,
                     std::cos(2 * pi * alphaX),
                     std::sin(2 * pi * alphaX),
                     0.0,
                     -std::sin(2 * pi * alphaX),
                     std::cos(2 * pi * alphaX)};

        xCoordinates[i] = M[0] * x + M[1] * y + M[2] * z;
        yCoordinates[i] = M[3] * x + M[4] * y + M[5] * z;
        zCoordinates[i] = M[6] * x + M[7] * y + M[8] * z;
    }
}

void crashr::operators::rotateY(std::vector<double>& xCoordinates,
                                  std::vector<double>& yCoordinates,
                                  std::vector<double>& zCoordinates,
                                  double alphaY) {
    const double pi = std::acos(-1);
    for (unsigned i = 0; i < xCoordinates.size(); i++) {
        double x = xCoordinates[i];
        double y = yCoordinates[i];
        double z = zCoordinates[i];

        double M[] = {std::cos(2 * pi * alphaY),
                     0.0,
                     std::sin(2 * pi * alphaY),
                     0.0,
                     1.0,
                     0.0,
                     -std::sin(2 * pi * alphaY),
                     0.0,
                     std::cos(2 * pi * alphaY)};

        xCoordinates[i] = M[0] * x + M[1] * y + M[2] * z;
        yCoordinates[i] = M[3] * x + M[4] * y + M[5] * z;
        zCoordinates[i] = M[6] * x + M[7] * y + M[8] * z;
    }
}

void crashr::operators::rotateZ(std::vector<double>& xCoordinates,
                                  std::vector<double>& yCoordinates,
                                  std::vector<double>& zCoordinates,
                                  double alphaZ) {
    const double pi = std::acos(-1);

    for (unsigned i = 0; i < xCoordinates.size(); i++) {
        double x = xCoordinates[i];
        double y = yCoordinates[i];
        double z = zCoordinates[i];

        double M[] = {std::cos(2 * pi * alphaZ),
                     std::sin(2 * pi * alphaZ),
                     0.0,
                     -std::sin(2 * pi * alphaZ),
                     std::cos(2 * pi * alphaZ),
                     0.0,
                     0.0,
                     0.0,
                     1.0};

        xCoordinates[i] = M[0] * x + M[1] * y + M[2] * z;
        yCoordinates[i] = M[3] * x + M[4] * y + M[5] * z;
        zCoordinates[i] = M[6] * x + M[7] * y + M[8] * z;
    }
}

