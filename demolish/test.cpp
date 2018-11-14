#include "demolish.h"
#include "World.h"

#include <iostream>


int main() {

    

  // ***********************************
  // CUBOID COLLIDE
  // ***********************************

  iREAL lowY = -10.0;
  iREAL highY = 1.0;
  iREAL size = 10;
  demolish::Vertex A(-size,highY,size);
  demolish::Vertex B(-size,highY,-size);
  demolish::Vertex C(size,highY,-size);
  demolish::Vertex D(size,highY,size);
  demolish::Vertex E(-size,lowY,size);
  demolish::Vertex F(-size,lowY,-size);
  demolish::Vertex G(size,lowY,-size);
  demolish::Vertex H(size,lowY,size);
  std::array<int,3> tri1 = {0,1,2};
  std::array<int,3> tri2 = {2,3,0};
  std::array<int,3> tri3 = {4,6,5};
  std::array<int,3> tri4 = {4,7,6};
  std::array<int,3> tri5 = {0,4,1};
  std::array<int,3> tri6 = {5,1,4};

  std::array<int,3> tri7 = {1,5,2};
  std::array<int,3> tri8 = {2,5,6};

  std::array<int,3> tri9 = {2,6,3};
  std::array<int,3> tri10 = {7,3,6};

  std::array<int,3> tri11 = {4,0,7};
  std::array<int,3> tri12 = {0,3,7};
  std::vector<std::array<int,3>> meshTriangles;
  std::vector<demolish::Vertex> meshVertices;
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


  demolish::Mesh m1(meshTriangles,meshVertices);
  std::array<iREAL, 3> location = {1,1,1};
  std::array<iREAL, 3> linear   = {0,0,0};
  std::array<iREAL, 3> angular  = {0.001,0,0};
  demolish::Object cuboid1(
                        0,
                        &m1,
                        location,
                        demolish::material::MaterialType::WOOD,
                        false, 
                        true,  
                        true,  
                        0.1,
                        linear,
                        angular);

  demolish::Mesh m2(meshTriangles,meshVertices);
  location = {10,-50,0};
  linear   = {0,10,0};
  angular  = {0.001,0.001,0.001};
  demolish::Object cuboid2(
                        1,
                        &m2,
                        location,
                        demolish::material::MaterialType::WOOD,
                        false,
                        true, 
                        true, 
                        0.1,
                        linear,
                        angular);



  std::vector<demolish::Object> objz;
  objz.push_back(cuboid1);
  objz.push_back(cuboid2);
    

  demolish::World aworld(objz);
  aworld.runSimulation();
  return 0;
}

