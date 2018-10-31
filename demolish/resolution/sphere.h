#include"../demolish.h"

#include<array>

#define SSPRING 200000
#define SDAMPER 50
#define SFRICTIONGOLD 1
#define SFRICTIONWOOD 1
#define SFRICTIONROLLING 0.5

namespace demolish{
    namespace resolution{

	  /*
	   * Spring Sphere
	   *
	   * Returns the force between two spheres
	   *
	   * @param normal is the contact normal
	   * @param depth is the penetration depth
	   * @param relativeVelocity is the relative velocity between the two spheres
	   * @param massA is the mass of particle A
	   * @param massB is the mass of particle B
	   * @param f is the vector force at the contact point
	   * @param force is the force magnitude at the contact point
	   * @return void
	   */
	  void springSphere(
		  iREAL normal[3],
		  iREAL depth,
		  iREAL relativeVelocity[3],
		  iREAL massA,
		  iREAL massB,
		  std::array<iREAL, 3> & f,
		  iREAL& forc);

    }
}
