

#ifndef WORLD
#define WORLD

#include <string>
#include <array>
#include <memory>
#include "Object.h"
#include "Timer.h"
#include "visuals/DEMDriver.h"
#include "detection/sphere.h"
#include "resolution/sphere.h"
#include "ContactPoint.h"
#include "Object.h"


namespace demolish{
	class World;
}

class demolish::World {

  public:
	World(
      std::vector<Object>&                objects);
	virtual ~World();

    int                                   runSimulation();

	std::vector<Object>                   getObjects();
    std::vector<ContactPoint>             getContactPoints();
    void                                  updateWorld(float dt);
  private:
    bool                                  _worldPaused;

    GameTimer                             _timer;
	std::vector<Object> 	              _particles;
    std::vector<ContactPoint>             _contactpoints;
    iREAL                                 _gravity;
    DEMDriver                             _visuals;
};

#endif /* DELTA_WORLD_WORLD_H_ */
