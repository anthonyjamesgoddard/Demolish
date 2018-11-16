

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


            
         
           auto cntpnts = demolish::detection::penalty(
                          _particles[i].getMesh()->getXCoordinates(),
                          _particles[i].getMesh()->getYCoordinates(),
                          _particles[i].getMesh()->getZCoordinates(),
                          _particles[i].getMesh()->getTriangles().size(),
                          _particles[i].getEpsilon(),
                          _particles[i].getIsFriction(),
                          _particles[i].getGlobalParticleId(),
                          _particles[j].getMesh()->getXCoordinates(),
                          _particles[j].getMesh()->getYCoordinates(),
                          _particles[j].getMesh()->getZCoordinates(),
                          _particles[j].getMesh()->getTriangles().size(),
                          _particles[j].getEpsilon(),
                          _particles[j].getIsFriction(),
                          _particles[j].getGlobalParticleId());
           
           if(cntpnts.size()>0)
           {
               _contactpoints.push_back(cntpnts[0]);
           }

           
        }
    }
    

    // we look at the details of the contact point
    for(int i=0;i< _contactpoints.size();i++)
    {
        //_contactpoints[i].printInformation();
    }


    if(true){
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
                                               _particles[_contactpoints[i].indexA].getLocation().data(),
                                               _particles[_contactpoints[i].indexA].getAngularVelocity().data(),
                                               _particles[_contactpoints[i].indexA].getLinearVelocity().data(),
                                               _particles[_contactpoints[i].indexA].getMass(),
                                               _particles[_contactpoints[i].indexA].getInverse().data(),
                                               _particles[_contactpoints[i].indexA].getOrientation().data(),
                                               int(_particles[_contactpoints[i].indexA].getMaterial()),
                                               _particles[_contactpoints[i].indexB].getLocation().data(),
                                               _particles[_contactpoints[i].indexB].getAngularVelocity().data(),
                                               _particles[_contactpoints[i].indexB].getLinearVelocity().data(),
                                               _particles[_contactpoints[i].indexB].getMass(),
                                               _particles[_contactpoints[i].indexB].getInertia().data(),
                                               _particles[_contactpoints[i].indexB].getOrientation().data(),
                                               int(_particles[_contactpoints[i].indexB].getMaterial()),
                                               force,
                                               torq,
                                               (_particles[_contactpoints[i].indexA].getIsSphere() && _particles[_contactpoints[i].indexB].getIsSphere()));

        if(!_particles[_contactpoints[i].indexA].getIsObstacle()) 
        {
            auto velocityOfA = _particles[_contactpoints[i].indexA].getLinearVelocity();
            auto massA = _particles[_contactpoints[i].indexA].getMass();

            std::array<iREAL, 3> newVelocityOfA = {velocityOfA[0] + dt*force[0]*(1/massA),
                                                velocityOfA[1] + dt*force[1]*(1/massA),
                                                velocityOfA[2] + dt*force[2]*(1/massA)};
            _particles[_contactpoints[i].indexA].setLinearVelocity(newVelocityOfA);


            auto ang = _particles[_contactpoints[i].indexA].getReferenceAngularVelocity();
            
            demolish::dynamics::updateAngular(ang.data(),
                                              _particles[_contactpoints[i].indexA].getOrientation().data(),
                                              _particles[_contactpoints[i].indexA].getInertia().data(),
                                              _particles[_contactpoints[i].indexA].getInverse().data(),
                                              torq.data(),
                                              dt);          
            _particles[_contactpoints[i].indexA].setReferenceAngularVelocity(ang);
            
            
            
        }
        if(!_particles[_contactpoints[i].indexB].getIsObstacle()) 
        {
            auto velocityOfB = _particles[_contactpoints[i].indexB].getLinearVelocity();
            auto massB     = _particles[_contactpoints[i].indexB].getMass();

            std::array<iREAL, 3> newVelocityOfB = {velocityOfB[0] - dt*force[0]*(1/massB),
                                                velocityOfB[1] - dt*force[1]*(1/massB),
                                                velocityOfB[2] - dt*force[2]*(1/massB)};

            _particles[_contactpoints[i].indexB].setLinearVelocity(newVelocityOfB);
    
            auto ang = _particles[_contactpoints[i].indexB].getReferenceAngularVelocity();
           
            // we may have to change this!
            //
            // is this physical?!
            demolish::dynamics::updateAngular(ang.data(),
                                              _particles[_contactpoints[i].indexB].getOrientation().data(),
                                              _particles[_contactpoints[i].indexB].getInertia().data(),
                                              _particles[_contactpoints[i].indexB].getInverse().data(),
                                              torq.data(),
                                              dt);          
            _particles[_contactpoints[i].indexB].setReferenceAngularVelocity(ang);
        } 
        
    }
 
    iREAL gravity = -0;

    for(int i=0;i<_particles.size();i++)
    {
       if(_particles[i].getIsObstacle()) continue;
       auto loc    = _particles[i].getLocation();
       auto refLoc = _particles[i].getReferenceLocation();
       auto linVel = _particles[i].getLinearVelocity();
       linVel[1] += dt*gravity;
       _particles[i].setLinearVelocity(linVel);
       loc[0] += dt*linVel[0];
       loc[1] += dt*linVel[1];
       loc[2] += dt*linVel[2];
       _particles[i].setLocation(loc);
      
      // update rotation matrix
      auto ori = _particles[i].getOrientation();

      demolish::dynamics::updateRotationMatrix(
                                               _particles[i].getAngularVelocity().data(),
                                               _particles[i].getReferenceAngularVelocity().data(),
                                               ori.data(),
                                               dt);
      _particles[i].setOrientation(ori);
      
      // update verts
      
      for(int j=0;j<(_particles[i].getMesh())->getTriangles().size()*3;j++)
      {
          demolish::dynamics::updateVertices(&_particles[i].getMesh()->getXCoordinates()[j],
                                             &_particles[i].getMesh()->getYCoordinates()[j],
                                             &_particles[i].getMesh()->getZCoordinates()[j],
                                             &_particles[i].getMesh()->getRefXCoordinates()[j],
                                             &_particles[i].getMesh()->getRefYCoordinates()[j],
                                             &_particles[i].getMesh()->getRefZCoordinates()[j],
                                             _particles[i].getOrientation().data(),
                                             loc.data(),refLoc.data());

      }
      
    }
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
