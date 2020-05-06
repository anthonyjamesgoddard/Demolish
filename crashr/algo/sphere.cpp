#include"sphere.h"
#include<math.h>
#include<iostream>
void crashr::resolution::springSphere(
    double normal[3],
    double depth,
    double relativeVelocity[3],
    double massA,
    double massB,
    std::array<double, 3>& f,
    double &forc)
{
  double ma = 1.0/sqrt((1.0/massA) + (1.0/massB));

  double velocity = (relativeVelocity[0]*normal[0]) + (relativeVelocity[1]*normal[1]) + (relativeVelocity[2]*normal[2]);


  double damp = 2.0 * SDAMPER * sqrt(ma)*velocity;

  double force = SSPRING*sqrt(SSPRING)*depth + damp;

  f[0] = force*normal[0];
  f[1] = force*normal[1];
  f[2] = force*normal[2];

  forc = force;

  #ifdef CONTACTSTATS
  std::cout << ", damp=" << std::fixed << std::setprecision(10) << damp << ", 1/W_NN=" << std::fixed << std::setprecision(10) << ma << std::endl;
  #endif
}

