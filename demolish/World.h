

#ifndef WORLD
#define WORLD

#include <string>
#include <array>
#include <memory>
#include "Object.h"
#include "Timer.h"
#include  "visuals/DEMDriver.h"
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
    bool                                            _worldPaused;
    demolish::GameTimer                             _timer;
	std::vector<demolish::Object> 	                _particles;
    DEMDriver                                       _visuals;
};

#endif /* DELTA_WORLD_WORLD_H_ */
