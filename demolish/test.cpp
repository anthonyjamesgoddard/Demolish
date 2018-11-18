#include "demolish.h"
#include "World.h"
#include "builder/GeometryBuilder.h"
#include <iostream>



int main() {

    


  // ***********************************
  // CUBOID COLLIDE
  // ***********************************

  int numberOfBodies = 10;


  std::vector<demolish::Vertex> meshVertices;
  std::vector<std::array<int, 3>> meshTriangles;
  std::vector<demolish::Object> objz;

  // create the box shape that will be shared by all 
  // dynamic objects in the scene
  demolish::CreateBox(10.0,10.0,10.0,meshVertices,meshTriangles);

  // all objects will have zero initial linear and angular velocity
  std::array<iREAL, 3> linear   = {0,0,0};
  std::array<iREAL, 3> angular  = {0,0,0};

  // now we define the locations and meshs the cubes
  std::vector<std::array<iREAL, 3>> locations;
  std::vector<demolish::Mesh> meshs;
  for(int i=0;i<numberOfBodies;i++)
  {
      std::array<iREAL, 3> loc = {0,10+20*i,0};
      locations.push_back(loc);
      meshs.push_back(demolish::Mesh(meshTriangles,meshVertices));
      objz.push_back(demolish::Object(i,
                                      &meshs[i],
                                      locations[i],
                                      demolish::material::MaterialType::WOOD,
                                      false,
                                      true,
                                      true,
                                      0.01,
                                      linear,
                                      angular));
      
  }
  

  demolish::World aworld(objz);
  aworld.runSimulation();
  return 0;
}

