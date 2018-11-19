// MAKE A HARD CODED NAMESPACE THAT SPLITS THESE TEST SCENES INTO SEPERATE TESTS



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



  // ***************************************************
  // First we create the dynamic objects.
  // ***************************************************

  // create the box shape that will be shared by all 
  // dynamic objects in the scene
  demolish::CreateBox(2.9,4.0,3.9,meshVertices,meshTriangles);

  // all objects will have zero initial linear and angular velocity
  std::array<iREAL, 3> linear = {0,0,0};
  std::array<iREAL, 3> angular = {0.1,0.1,0.1};
  // now we define the locations and meshs the cubes
  std::vector<std::array<iREAL, 3>> locations;
  std::vector<demolish::Mesh> meshs;
  for(int i=0;i<numberOfBodies;i++)
  {
      std::array<iREAL, 3> loc = {0,10+10*i,0};
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
                                      0.01,
                                      linear,
                                      angular));
   }   


  // ********************************************
  // Now we create the (static) floor
  // ********************************************

  angular = {0,0,0};
  meshTriangles.clear();meshVertices.clear();
  demolish::CreateBox(20.0,0.50,20.0,meshVertices,meshTriangles);
  demolish::Mesh m(meshTriangles,meshVertices);
  std::array<iREAL, 3> locationOfFloor = {0,-10,0};
  linear = {0,3,0};
  objz.push_back(demolish::Object(numberOfBodies,
                                      &m,
                                      locationOfFloor,
                                      demolish::material::MaterialType::WOOD,
                                      true,
                                      true,
                                      true,
                                      0.5,
                                      linear,
                                      angular));
  demolish::World aworld(objz);
  aworld.runSimulation();
  return 0;
}

/*
#include "demolish.h"
#include "World.h"
#include "builder/GeometryBuilder.h"
#include <iostream>



int main() {



  std::vector<std::array<int,3>> meshTriangles;
  std::vector<demolish::Vertex> meshVertices;
  demolish::CreateBox(10,10,10,meshVertices,meshTriangles);
  demolish::Mesh m1(meshTriangles,meshVertices);
  std::array<iREAL, 3> location = {0,20,0};
  std::array<iREAL, 3> linear   = {0,0,0};
  std::array<iREAL, 3> angular  = {0,0,1};
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

  demolish::Mesh m2(meshTriangles,meshVertices);
  location = {5,-10,0};
  linear   = {0,6,0};
  angular  = {1,0,0};
  demolish::Object cuboid2(
                        1,
                        &m2,
                        location,
                        demolish::material::MaterialType::WOOD,
                        false,
                        true,
                        true,
                        0.01,
                        linear,
                        angular);



  std::vector<demolish::Object> objz;
  objz.push_back(cuboid1);
  objz.push_back(cuboid2);


  demolish::World aworld(objz);
  aworld.runSimulation();
  return 0;
}
*/
