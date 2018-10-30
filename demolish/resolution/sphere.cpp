#include"sphere.h"
#include<math.h>
void demolish::resolution::springSphere(
    iREAL normal[3],
    iREAL depth,
    iREAL relativeVelocity[3],
    iREAL massA,
    iREAL massB,
    iREAL f[3],
    iREAL &forc)
{
  iREAL ma = 1.0/((1.0/massA) + (1.0/massB));

  iREAL velocity = (relativeVelocity[0]*normal[0]) + (relativeVelocity[1]*normal[1]) + (relativeVelocity[2]*normal[2]);

  iREAL damp = 2.0 * SDAMPER * sqrt(SSPRING*ma)*velocity;

  iREAL force = SSPRING*depth + damp;

  f[0] = force*normal[0];
  f[1] = force*normal[1];
  f[2] = force*normal[2];

  forc = force;

  #ifdef CONTACTSTATS
  std::cout << ", damp=" << std::fixed << std::setprecision(10) << damp << ", 1/W_NN=" << std::fixed << std::setprecision(10) << ma << std::endl;
  #endif
}

