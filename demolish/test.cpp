#include "demolish.h"
#include "World.h"

#include <iostream>


int main() {

  // HERE WE DEFINE TWO SPHERES THAT ARE GOING TO COLLISDE.
  std::array<iREAL, 3> centre = {0,20,0};
  std::array<iREAL, 3> linear = {0,0,0};
  std::array<iREAL, 3> angular = {0,0,0};
  demolish::Object asphere(
                          10.0,
                          0,
                          centre,
                          demolish::material::MaterialType::GRAPHITE,
                          false,            // this is not an obsticle
                          true,             // we do want friction (??)
                          0.1,
                          linear,
                          angular);

  centre = {0,-20,0};
  std::array<iREAL,3> linear2 = {0,20,0};
  demolish::Object asphere2(
                          10.0,
                          1,
                          centre,
                          demolish::material::MaterialType::GRAPHITE,
                          false,
                          true,
                          0.1,
                          linear2,
                          angular);


  // HERE WE DEFINE A PLATFORM ONTO WHICH SPHERES WILL FALL ONTO.
  
  demolish::Vertex A(0.0,0.0,100.0);
  demolish::Vertex B(0.0,0.0,0.0);
  demolish::Vertex C(100.0,0.0,0.0);
  demolish::Vertex D(100.0,0.0,100.0);
  std::array<int,3> tri1 = {0,2,1};
  std::array<int,3> tri2 = {2,0,3};
  std::vector<std::array<int,3>> meshTriangles;
  std::vector<demolish::Vertex> meshVertices;
  meshVertices.push_back(A);
  meshVertices.push_back(B);
  meshVertices.push_back(C);
  meshVertices.push_back(D);
  meshTriangles.push_back(tri1);
  meshTriangles.push_back(tri2);
  demolish::Mesh m(meshTriangles,meshVertices);
  centre = {0,0,0};


  demolish::Object floor(
                        2,
                        &m,
                        centre,
                        demolish::material::MaterialType::WOOD,
                        true,       // this is an obsticle
                        true,       // we want friction
                        true,       // the object is trivially convex
                        0.1,
                        linear,
                        angular);



  std::vector<demolish::Object> objz;
  objz.push_back(asphere);
  objz.push_back(asphere2);
  objz.push_back(floor);

  demolish::World aworld(objz);
  aworld.runSimulation();
  return 0;
}

