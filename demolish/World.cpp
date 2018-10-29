

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
                updateWorld(_timer.DeltaTime());
                _visuals.setContactPoints(_contactpoints);
                _visuals.UpdateScene(_timer.DeltaTime());
                _visuals.RedrawTheWindow();
            }
            else
            {

            }
    }
    return 1;
}


void demolish::World::updateWorld(float dt)
{
   _contactpoints.clear();
   for(int i=0;i<_particles.size();i++)
   {
       for(int j=i+1;j<_particles.size();j++)
       {
            auto locationi = _particles[i].getCentre();
            auto locationj = _particles[j].getCentre();
            auto radi      = _particles[i].getRad();
            auto radj      = _particles[j].getRad();
            auto contactpoints = demolish::detection::spherewithsphere(std::get<0>(locationi),
                                                                          std::get<1>(locationi),
                                                                          std::get<2>(locationi),
                                                                          radi,
                                                                          0.1,
                                                                          false,
                                                                          i,
                                                                          std::get<0>(locationj),
                                                                          std::get<1>(locationj),
                                                                          std::get<2>(locationj),
                                                                          radj,
                                                                          0.1,
                                                                          false,
                                                                          j);
           if(contactpoints.size()>0)
           {
               _contactpoints.push_back(contactpoints[0]);
           };

        }
    }
    
    // update using gravity
     

    
}
                
std::vector<demolish::Object> demolish::World::getObjects()
{
    return _particles;
}

std::vector<demolish::ContactPoint> demolish::World::getContactPoints()
{
    return _contactpoints;
}

demolish::World::~World() {

}
