
#include "mesh.h"

void demolish::operators::shiftMesh(
    std::vector<iREAL> &xCoordinates,
    std::vector<iREAL> &yCoordinates,
    std::vector<iREAL> &zCoordinates,
    std::vector<demolish::Vertex> &verts,
    iREAL center[3])
{
  #ifdef OMPProcess
//	#pragma omp parallel for
  #endif
  for(unsigned i=0;i<xCoordinates.size();i++)
  {
    xCoordinates[i] = xCoordinates[i]-center[0];
    yCoordinates[i] = yCoordinates[i]-center[1];
    zCoordinates[i] = zCoordinates[i]-center[2];
  }

// we only need this for the visualisation.
// there is something I can do to deal with this.
  demolish::Vertex shift(center[0],center[1],center[2]);

  for(unsigned i =0;i<verts.size();i++)
  {
      verts[i] = verts[i] - shift;
  }
}


void demolish::operators::scaleXYZ(
    std::vector<iREAL> &xCoordinates,
    std::vector<iREAL> &yCoordinates,
    std::vector<iREAL> &zCoordinates,
    std::vector<demolish::Vertex> &verts,
    iREAL scale,
    iREAL position[3])
{
  demolish::operators::shiftMesh(xCoordinates, yCoordinates, zCoordinates,verts, position);

  for(unsigned i=0;i<xCoordinates.size();i++)
  {
      xCoordinates[i] = xCoordinates[i]*scale;
      yCoordinates[i] = yCoordinates[i]*scale;
      zCoordinates[i] = zCoordinates[i]*scale;
  }
  iREAL backToPosition[3] = {-position[0],-position[1],-position[2]};
  demolish::operators::shiftMesh(xCoordinates, yCoordinates, zCoordinates,verts,
                                                    backToPosition);
}

void demolish::operators::rotateX(
    std::vector<iREAL> &xCoordinates,
    std::vector<iREAL> &yCoordinates,
    std::vector<iREAL> &zCoordinates,
    iREAL alphaX)
{
  const iREAL pi = std::acos(-1);

  for (unsigned i=0;i<xCoordinates.size(); i++)
  {
      iREAL x = xCoordinates[i];
      iREAL y = yCoordinates[i];
      iREAL z = zCoordinates[i];

      iREAL M[] = {
         1.0,                 0.0,                   0.0,
         0.0,  std::cos(2*pi*alphaX),  std::sin(2*pi*alphaX),
         0.0, -std::sin(2*pi*alphaX),  std::cos(2*pi*alphaX)
      };

      xCoordinates[i] =   M[0] * x + M[1] * y + M[2] * z;
      yCoordinates[i] =   M[3] * x + M[4] * y + M[5] * z;
      zCoordinates[i] =   M[6] * x + M[7] * y + M[8] * z;
  }
}

void demolish::operators::rotateY(
    std::vector<iREAL> &xCoordinates,
    std::vector<iREAL> &yCoordinates,
    std::vector<iREAL> &zCoordinates,
    iREAL alphaY)
{
  const iREAL pi = std::acos(-1);
  for (unsigned i=0;i<xCoordinates.size(); i++) {
      iREAL x = xCoordinates[i];
      iREAL y = yCoordinates[i];
      iREAL z = zCoordinates[i];

      iREAL M[] = {
        std::cos(2*pi*alphaY),  0.0, std::sin(2*pi*alphaY),
        0.0,                    1.0,                   0.0,
       -std::sin(2*pi*alphaY),  0.0, std::cos(2*pi*alphaY)
      };

      xCoordinates[i] =   M[0] * x + M[1] * y + M[2] * z;
      yCoordinates[i] =   M[3] * x + M[4] * y + M[5] * z;
      zCoordinates[i] =   M[6] * x + M[7] * y + M[8] * z;
  }
}

void demolish::operators::rotateZ(
    std::vector<iREAL> &xCoordinates,
    std::vector<iREAL> &yCoordinates,
    std::vector<iREAL> &zCoordinates,
    iREAL alphaZ)
{
  const iREAL pi = std::acos(-1);

  for (unsigned i=0;i<xCoordinates.size(); i++) {
      iREAL x = xCoordinates[i];
      iREAL y = yCoordinates[i];
      iREAL z = zCoordinates[i];

      iREAL M[] = {
        std::cos(2*pi*alphaZ),  std::sin(2*pi*alphaZ),  0.0,
       -std::sin(2*pi*alphaZ),  std::cos(2*pi*alphaZ),  0.0,
                         0.0,                   0.0,  1.0
      };

      xCoordinates[i] =   M[0] * x + M[1] * y + M[2] * z;
      yCoordinates[i] =   M[3] * x + M[4] * y + M[5] * z;
      zCoordinates[i] =   M[6] * x + M[7] * y + M[8] * z;
  }
}



