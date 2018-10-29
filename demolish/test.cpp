#include "demolish.h"
#include "World.h"

#include <iostream>


int main() {

  // DEFINE A SPHERE AND TRY AND DRAW IT
  std::array<iREAL, 3> centre = {1,11,0};
  std::array<iREAL, 3> linear = {0,0,0};
  std::array<iREAL, 3> angular = {0,0,0};
  demolish::Object asphere(
                          10.0,
                          0,
                          centre,
                          demolish::material::MaterialType::WOOD,
                          false,
                          false,
                          true,
                          0.01,
                          linear,
                          angular);

  centre = {1,-11,30};
  demolish::Object asphere2(
                          5.0,
                          0,
                          centre,
                          demolish::material::MaterialType::WOOD,
                          false,
                          false,
                          true,
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

