// MAKE A HARD CODED NAMESPACE THAT SPLITS THESE TEST SCENES INTO SEPERATE TESTS



#include "demolish.h"
#include "World.h"
#include "builder/GeometryBuilder.h"
#include <iostream>



int main() {

    


  // ***********************************
  // CUBOID COLLIDE
  // ***********************************

  int numberOfBodies = 4;


  std::vector<demolish::Vertex> meshVertices;
  std::vector<std::array<int, 3>> meshTriangles;
  std::vector<demolish::Object> objz;



  // ***************************************************
  // First we create the dynamic objects.
  // ***************************************************

  // create the box shape that will be shared by all 
  // dynamic objects in the scene
  demolish::CreateBox(4.0,4.0,4.0,meshVertices,meshTriangles);

  // all objects will have zero initial linear and angular velocity
  std::array<iREAL, 3> linear = {0,-5,0};
  std::array<iREAL, 3> angular = {0.1,0.1,0.1};
  // now we define the locations and meshs the cubes
  std::vector<std::array<iREAL, 3>> locations;
  std::vector<demolish::Mesh> meshs;

  for(int i=0;i<numberOfBodies;i++)
  {
      std::array<iREAL, 3> loc = {10,50+10*i,10};
      locations.push_back(loc);
      meshs.push_back(demolish::Mesh(meshTriangles,meshVertices));
  }
  for(int i =0;i<numberOfBodies;i++)
  {
      objz.push_back(demolish::Object(i,
                                      &meshs[i],
                                      locations[i],
                                      demolish::material::MaterialType::WOOD,
                                      false,
                                      true,
                                      true,
                                      1.0,
                                      linear,
                                      angular));
   }   


  // ********************************************
  // Now we create the (static) floor
  // ********************************************

  angular = {0,0,0};
  meshTriangles.clear();meshVertices.clear();
  demolish::CreateBox(50.0,0.1,50.0,meshVertices,meshTriangles);
  demolish::Mesh m(meshTriangles,meshVertices);
  std::array<iREAL, 3> locationOfFloor = {0,-30,0};
  linear = {0,0,0};
  objz.push_back(demolish::Object(numberOfBodies,
                                      &m,
                                      locationOfFloor,
                                      demolish::material::MaterialType::WOOD,
                                      true,
                                      true,
                                      true,
                                      1.0,
                                      linear,
                                      angular));
  angular = {0,0,0};
  meshTriangles.clear();meshVertices.clear();
  demolish::CreateTrunCone(40.0,
                           10.0,
                           30.0,
                           4,meshVertices,meshTriangles);
  demolish::Mesh mc(meshTriangles,meshVertices);
  std::array<iREAL, 3> locationOfCone = {0,30,0};
  linear = {0,0,0};
  objz.push_back(demolish::Object(numberOfBodies+1,
                                      &mc,
                                      locationOfCone,
                                      demolish::material::MaterialType::WOOD,
                                      true,
                                      true,
                                      true,
                                      1.0,
                                      linear,
                                      angular));
  demolish::World aworld(objz);
  aworld.runSimulation();
  return 0;
}


