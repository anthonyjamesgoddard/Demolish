#include "demolish.h"
#include "World.h"

#include <iostream>


int main() {

  // DEFINE A SPHERE AND TRY AND DRAW IT
  std::array<iREAL, 3> centre = {0,20,0};
  std::array<iREAL, 3> linear = {0,-3,0};
  std::array<iREAL, 3> angular = {0,0,0};
  demolish::Object asphere(
                          10.0,
                          0,
                          centre,
                          demolish::material::MaterialType::GRAPHITE,
                          false,
                          false,
                          0.1,
                          linear,
                          angular);

  centre = {0,-20,0};
  std::array<iREAL,3> linear2 = {0,2,0};
  demolish::Object asphere2(
                          10.0,
                          1,
                          centre,
                          demolish::material::MaterialType::GRAPHITE,
                          false,
                          false,
                          0.1,
                          linear2,
                          angular);

  std::vector<demolish::Object> objz;
  objz.push_back(asphere);
  objz.push_back(asphere2);
  demolish::World aworld(objz);
  aworld.runSimulation();
  return 0;
}

