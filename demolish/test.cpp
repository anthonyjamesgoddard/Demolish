#include "demolish.h"
#include "World.h"
#include "builder/GeometryBuilder.h"
#include <iostream>



int main() {

    

  // ***********************************
  // CUBOID COLLIDE
  // ***********************************

  std::vector<demolish::Vertex> meshVertices;
  std::vector<std::array<int, 3>> meshTriangles;
  std::vector<demolish::Object> objz;

  // create the box shape that will be shared by all 
  // dynamic objects in the scene
  demolish::CreateBox(10.0,10.0,10.0,meshVertices,meshTriangles);

  // all objects will have zero initial linear and angular velocity
  std::array<iREAL, 3> linear   = {0,0,0};
  std::array<iREAL, 3> angular  = {0,0,0};

  // now we define the locations of the cubes
    

  demolish::Mesh m1(meshTriangles,meshVertices);
  std::array<iREAL, 3> location = {0,20,0};
  demolish::Object cuboid1(
                        0,
                        &m1,
                        location,
                        demolish::material::MaterialType::WOOD,
                        false, 
                        true,  
                        true,  
                        0.01,
                        linear,
                        angular);




    

  demolish::World aworld(objz);
  aworld.runSimulation();
  return 0;
}

