#ifndef WORLD
#define WORLD

#include <string>
#include <array>
#include <memory>
#include "Object.h"
#include "visuals/DEMDriver.h"
#include "detection/sphere.h"
#include "resolution/sphere.h"
#include "resolution/forces.h"
#include "ContactPoint.h"
#include "Object.h"
#include "resolution/dynamics.h"
#include "detection/penalty.h"


namespace demolish{
	class World;
}

class demolish::World {

  public:
	World(
    std::vector<Object>&                objects,
    iREAL                               gravity);

	virtual ~World();

    int                                   runSimulation();

	std::vector<Object>                   getObjects();
    std::vector<ContactPoint>             getContactPoints();
    void                                  updateWorld();
  private:
    bool                                  _worldPaused;
    bool                                  _timeStepAltered;

  	std::vector<Object> 	                _particles;
    std::vector<ContactPoint>             _contactpoints;
    iREAL                                 _gravity;
    iREAL                                 _timestep;
    int                                   _timeStamp;
    int                                   _lastTimeStampChanged;
    iREAL                                 _penetrationThreshold;
    DEMDriver                             _visuals;
};

#endif /* DELTA_WORLD_WORLD_H_ */
