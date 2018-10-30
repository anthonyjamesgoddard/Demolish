#include "demolish.h"
#include "World.h"

#include <iostream>


int main() {

  // DEFINE A SPHERE AND TRY AND DRAW IT
  std::array<iREAL, 3> centre = {0,10,0};
  std::array<iREAL, 3> linear = {0,0,0};
  std::array<iREAL, 3> angular = {0,0,0};
  demolish::Object asphere(
                          10.0,
                          0,
                          centre,
                          demolish::material::MaterialType::WOOD,
                          false,
                          false,
                          0.01,
                          linear,
                          angular);

  centre = {0,-10.1,0};
  demolish::Object asphere2(
                          10.0,
                          1,
                          centre,
                          demolish::material::MaterialType::WOOD,
                          false,
                          false,
                          0.01,
                          linear,
                          angular);

  std::vector<demolish::Object> objz;
  objz.push_back(asphere);
  objz.push_back(asphere2);
  demolish::World aworld(objz);
  aworld.runSimulation();
  return 0;
}

