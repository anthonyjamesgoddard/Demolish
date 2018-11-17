#include "GeometryBuilder.h"

void demolish::CreateBox(iREAL dim1, iREAL dim2, iREAL dim3,
      std::vector<demolish::Vertex>& meshVertices,
      std::vector<std::array<int, 3>>& meshTriangles)
{

      demolish::Vertex A(-0.5*dim1,0.5*dim2,0.5*dim3);
      demolish::Vertex B(-0.5*dim1,0.5*dim2,-0.5*dim3);
      demolish::Vertex C(0.5*dim1,0.5*dim2,-0.5*dim3);
      demolish::Vertex D(0.5*dim1,0.5*dim2,0.5*dim3);
      demolish::Vertex E(-0.5*dim1,-0.5*dim2,0.5*dim3);
      demolish::Vertex F(-0.5*dim1,-0.5*dim2,-0.5*dim3);
      demolish::Vertex G(0.5*dim1,-0.5*dim2,-0.5*dim3);
      demolish::Vertex H(0.5*dim1,-0.5*dim2,0.5*dim3);
      std::array<int,3> tri1 = {0,2,1};
      std::array<int,3> tri2 = {2,0,3};
      std::array<int,3> tri3 = {4,5,6};
      std::array<int,3> tri4 = {4,6,7};
      std::array<int,3> tri5 = {0,1,4};
      std::array<int,3> tri6 = {5,4,1};
      std::array<int,3> tri7 = {1,2,5};
      std::array<int,3> tri8 = {2,6,5};
      std::array<int,3> tri9 = {2,3,6};
      std::array<int,3> tri10 = {7,6,3};
      std::array<int,3> tri11 = {4,7,0};
      std::array<int,3> tri12 = {0,7,3};
      meshVertices.push_back(A);
      meshVertices.push_back(B);
      meshVertices.push_back(C);
      meshVertices.push_back(D);
      meshVertices.push_back(E);
      meshVertices.push_back(F);
      meshVertices.push_back(G);
      meshVertices.push_back(H);
      meshTriangles.push_back(tri1);
      meshTriangles.push_back(tri2);
      meshTriangles.push_back(tri3);
      meshTriangles.push_back(tri4);
      meshTriangles.push_back(tri5);
      meshTriangles.push_back(tri6);
      meshTriangles.push_back(tri7);
      meshTriangles.push_back(tri8);
      meshTriangles.push_back(tri9);
      meshTriangles.push_back(tri10);
      meshTriangles.push_back(tri11);
      meshTriangles.push_back(tri12);
}

