

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
//**********************************************************************
//
// DETECTION
//
//**********************************************************************
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
                                                                             0.1,       // we should get eps
                                                                             false,
                                                                             _particles[i].getGlobalParticleId(),
                                                                             std::get<0>(locationj),
                                                                             std::get<1>(locationj),
                                                                             std::get<2>(locationj),
                                                                             radj,
                                                                             0.1,       // same as above
                                                                             false,
                                                                             _particles[j].getGlobalParticleId());
               if(contactpoints.size()>0)
               {
                   _contactpoints.push_back(contactpoints[0]);
               };
               continue;
           }
           if(_particles[i].getIsSphere() || _particles[j].getIsSphere())
           {
               //we need to deduce which one is a mesh and which one is a sphere.
               int sphereIndex = (_particles[i].getIsSphere()) ? i : j;
               int meshIndex   = (i==sphereIndex)              ? j : i;

               auto locationSphere = _particles[sphereIndex].getLocation();
               auto radiusOfSphere = _particles[sphereIndex].getRad();
               int numberOfTris    = _particles[meshIndex].getMesh()->getTriangles().size();

               auto contactpoints = demolish::detection::sphereWithMesh(locationSphere[0],
                                                                        locationSphere[1],
                                                                        locationSphere[2],
                                                                        radiusOfSphere,
                                                                        0.1,
                                                                        true,
                                                                        _particles[sphereIndex].getGlobalParticleId(),
                                                                        _particles[meshIndex].getMesh()->getXCoordinates(),
                                                                        _particles[meshIndex].getMesh()->getYCoordinates(),
                                                                        _particles[meshIndex].getMesh()->getZCoordinates(),
                                                                        numberOfTris,
                                                                        0.1,
                                                                        true,
                                                                        _particles[meshIndex].getGlobalParticleId());
               if(contactpoints.size()>0)
               {
                   _contactpoints.push_back(contactpoints[0]);
               }
               continue;
           }

           // now we need to fill in the details for mesh-mesh interaction
           
        }
    }

//**********************************************************************
//
// RESOLUTION
//
//**********************************************************************

    for(int i=0;i<_contactpoints.size();i++)
    {
        std::array<iREAL, 3> force;
        std::array<iREAL, 3> torq;
        demolish::resolution::getContactForces(_contactpoints[i],
                                               _particles[contactpoints[i].indexA].getLocation().data(),
                                               _particles[contactpoints[i].indexA].getAngularVelocity().data(),
                                               _particles[contactpoints[i].indexA].getLinearVelocity().data(),
                                               _particles[contactpoints[i].indexA].getMass(),
                                               _particles[contactpoints[i].indexA].getOrientation().data(),
                                               _particles[contactpoints[i].indexA].getMaterial(),
                                               _particles[contactpoints[i].indexB].getLocation().data(),
                                               _particles[contactpoints[i].indexB].getAngularVelocity().data(),
                                               _particles[contactpoints[i].indexB].getLinearVelocity().data(),
                                               _particles[contactpoints[i].indexB].getMass(),
                                               _particles[contactpoints[i].indexB].getOrientation().data(),
                                               _particles[contactpoints[i].indexB].getMaterial(),
                                               force,
                                               torq,
                                               (_particles[contactpoints[i].indexA].getIsSphere() && _particles[contactpoints[i].indexB].getIsSphere()));

        
                                                
        if(!_particles[_contactpoints[i].indexA].getIsObstacle()) 
        {
            std::array<iREAL, 3> newVelocityOfA = {velocityOfA[0] + dt*force[0]*(1/massA),
                                                velocityOfA[1] + dt*force[1]*(1/massA),
                                                velocityOfA[2] + dt*force[2]*(1/massA)};
            _particles[_contactpoints[i].indexA].setLinearVelocity(newVelocityOfA);


            demolish::dynamics::updateAngular(_particles[_contactpoints[i].indexA].getAngularVelocity().data(),
                                              _particles[_contactpoints[i].indexA].getOrientation().data(),
                                              _particles[_contactpoints[i].indexA].getInertia().data(),
                                              _particles[_contactpoints[i].indexA].getInverse().data(),
                                              torque,
                                              dt);

        }
        if(!_particles[_contactpoints[i].indexB].getIsObstacle()) 
        {
            std::array<iREAL, 3> newVelocityOfB = {velocityOfB[0] - dt*force[0]*(1/massB),
                                                velocityOfB[1] - dt*force[1]*(1/massB),
                                                velocityOfB[2] - dt*force[2]*(1/massB)};
            _particles[_contactpoints[i].indexB].setLinearVelocity(newVelocityOfB);
            
            
            demolish::dynamics::updateAngular(_particles[_contactpoints[i].indexB].getAngularVelocity().data(),
                                              _particles[_contactpoints[i].indexB].getOrientation().data(),
                                              _particles[_contactpoints[i].indexB].getInertia().data(),
                                              _particles[_contactpoints[i].indexB].getInverse().data(),
                                              torque,
                                              dt);
        } 
        continue;

    }
    

    // the contents of delta's Engine::updatePosition() method goes here... essentially
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
