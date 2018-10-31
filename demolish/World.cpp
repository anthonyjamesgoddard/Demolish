

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
                _visuals.UpdateScene(_timer.DeltaTime(),_particles);
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
            auto locationi = _particles[i].getLocation();
            auto locationj = _particles[j].getLocation();
            auto radi      = _particles[i].getRad();
            auto radj      = _particles[j].getRad();
            auto contactpoints = demolish::detection::spherewithsphere(std::get<0>(locationi),
                                                                          std::get<1>(locationi),
                                                                          std::get<2>(locationi),
                                                                          radi,
                                                                          0.1,
                                                                          false,
                                                                          _particles[i].getGlobalParticleId(),
                                                                          std::get<0>(locationj),
                                                                          std::get<1>(locationj),
                                                                          std::get<2>(locationj),
                                                                          radj,
                                                                          0.1,
                                                                          false,
                                                                          _particles[j].getGlobalParticleId());
           if(contactpoints.size()>0)
           {
               _contactpoints.push_back(contactpoints[0]);
           };
        }
    }
    
    // now lets obtain the forces
    for(int i=0;i<_contactpoints.size();i++)
    {
        iREAL forceMagnitude;
        iREAL forceVector[3];
        iREAL relativeVelocity[3];
        auto velocityOfA = _particles[_contactpoints[i].indexA].getLinearVelocity();
        auto velocityOfB = _particles[_contactpoints[i].indexB].getLinearVelocity();
        auto massA       = _particles[_contactpoints[i].indexA].getMass();
        auto massB       = _particles[_contactpoints[i].indexB].getMass();

        relativeVelocity[0] = std::get<0>(velocityOfB)-std::get<0>(velocityOfA);
        relativeVelocity[1] = std::get<1>(velocityOfB)-std::get<1>(velocityOfA);
        relativeVelocity[2] = std::get<2>(velocityOfB)-std::get<2>(velocityOfA);

        demolish::resolution::springSphere(_contactpoints[i].normal,
                                           _contactpoints[i].distance,
                                           relativeVelocity,
                                           massA,
                                           massB,
                                           forceVector,
                                           forceMagnitude);
        // lets update the velocities and positions of the particles
        // we have to reverse the vels right?
    
    }
    auto temp = _particles[1].getLocation();
    std::get<0>(temp) += 0.001;
    std::get<2>(temp) += 0.001;
    _particles[1].setCentre(temp);
    temp = _particles[2].getLocation();
    std::get<0>(temp) += 0.001;
    std::get<2>(temp) += 0.001;
    _particles[2].setCentre(temp);
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
