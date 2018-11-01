

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
    _timer.Start();
    while(_visuals.UpdateTheMessageQueue())
    {
        _timer.Tick();
        // updates the physics
        auto dt = _timer.DeltaTime();
        if(dt>0.5)continue;
        updateWorld(_timer.DeltaTime());
        _visuals.setContactPoints(_contactpoints);
        _visuals.UpdateScene(_particles);
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
           if(_particles[i].getIsSphere() && _particles[j].getIsSphere())
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
               continue;
           }
           if(_particles[i].getIsSphere() || _particles[j].getIsSphere()) // this should only execute if ONLY one is a sphere
           {
                std::cout << "ONLY one of us is a sphere" << std::endl;
                std::cout << i << " " << j << std::endl;
           }
           
        }
    }
    
    // now lets obtain the forces
    for(int i=0;i<_contactpoints.size();i++)
    {
        iREAL forceMagnitude;
        std::array<iREAL, 3> forceVector;
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
        //
        
        // for each contact point we are going to update the position
        // of each of the asociated with the contact points.
        
        iREAL gravity = 0*98.0;
        std::array<iREAL, 3> newVelocityOfA = {velocityOfA[0] + dt*forceVector[0]*(1/massA),
                                                velocityOfA[1] + dt*forceVector[1]*(1/massA)-gravity*dt,
                                                velocityOfA[2] + dt*forceVector[2]*(1/massA)};

        std::array<iREAL, 3> newVelocityOfB = {velocityOfB[0] - dt*forceVector[0]*(1/massB),
                                                velocityOfB[1] - dt*forceVector[1]*(1/massB)-gravity*dt,
                                                velocityOfB[2] - dt*forceVector[2]*(1/massB)};
    
        _particles[_contactpoints[i].indexA].setLinearVelocity(newVelocityOfA);
        _particles[_contactpoints[i].indexB].setLinearVelocity(newVelocityOfB);
    }

    for(int i=0;i<_particles.size();i++)
    {
        auto vel = _particles[i].getLinearVelocity();
        auto pos = _particles[i].getLocation();
        std::array<iREAL, 3> newpos = {pos[0] + vel[0]*dt,
                                       pos[1] + vel[1]*dt,
                                       pos[2] + vel[2]*dt};

        _particles[i].setLocation(newpos);
    }
    
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
