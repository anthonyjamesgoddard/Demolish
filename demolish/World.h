

#ifndef WORLD
#define WORLD

#include <string>
#include <array>
#include <memory>
#include "Object.h"
#include "Timer.h"
namespace demolish{
	class World;
}

class demolish::World {

  public:
	World(
      std::vector<demolish::Object>&                objects);
	virtual ~World();

    int                                             runSimulation();

	std::vector<demolish::Object>                   getObjects();

  private:
    demolish::GameTimer                             _timer;
	std::vector<demolish::Object> 	                _particles;
    DEMDriver                                       _visuals;
};

#endif /* DELTA_WORLD_WORLD_H_ */
