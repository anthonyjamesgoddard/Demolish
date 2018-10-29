

#include"World.h"

#define epsilon 1E-3

demolish::World::World(
      std::vector<demolish::Object>&                 objects)
{
    _particles = objects;
    _visuals.Init();
    _visuals.BuildBuffers(objects);
    _worldPaused = false;
}
 

int demolish::World::runSimulation()
{

    _timer.Reset();

    while(_visuals.UpdateTheMessageQueue())
    {

            _timer.Tick();

            if( !_worldPaused )
            {
                // updates the physics 
                // then we update the visuals./..
                _visuals.UpdateScene(_timer.DeltaTime());
                _visuals.RedrawTheWindow();
            }
            else
            {

            }
    }
    return 1;
}

                
std::vector<demolish::Object> demolish::World::getObjects()
{
    return _particles;
}

demolish::World::~World() {

}
