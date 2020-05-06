#include "physics.h"

double crashr::operators::computeVolume(
	std::vector<double>& xCoordinates,
	std::vector<double>& yCoordinates,
	std::vector<double>& zCoordinates)
{

  double vol=0, a[3], b[3], c[3], J;

  double zero[3];
  zero[0] = 0;
  zero[1] = 0;
  zero[2] = 0;

  for (unsigned i=0;i<xCoordinates.size(); i+=3)
  {
    a[0] = xCoordinates[i];
    a[1] = yCoordinates[i];
    a[2] = zCoordinates[i];

    b[0] = xCoordinates[i+1];
    b[1] = yCoordinates[i+1];
    b[2] = zCoordinates[i+1];

    c[0] = xCoordinates[i+2];
    c[1] = yCoordinates[i+2];
    c[2] = zCoordinates[i+2];

    J = simplex_J (zero, a, b, c);

    vol += simplex_1 (J, zero, a, b, c);
  }

  return vol;
}

/*
 * gets the inertia using simplex integration from solfec
 */
void crashr::operators::computeInertia(
	std::vector<double>& xCoordinates,
	std::vector<double>& yCoordinates,
	std::vector<double>& zCoordinates,
	crashr::material::MaterialType material,
	double& mass,
	double center[3],
	double inertia[9])
{

  double me, sx, sy, sz, euler[9], a[3], b[3], c[3], J;

  double zero[3];
  zero[0] = 0;
  zero[1] = 0;
  zero[2] = 0;

  me = sx = sy = sz = 0.0;
  euler[0] = euler[1] = euler[2] =
  euler[3] = euler[4] = euler[5] =
  euler[6] = euler[7] = euler[8] = 0.0;

  double rho = double(crashr::material::materialToDensitymap.find(material)->second);	

  for (unsigned i=0;i<xCoordinates.size(); i+=3)
  {
    a[0] = xCoordinates[i];
    a[1] = yCoordinates[i];
    a[2] = zCoordinates[i];

    b[0] = xCoordinates[i+1];
    b[1] = yCoordinates[i+1];
    b[2] = zCoordinates[i+1];

    c[0] = xCoordinates[i+2];
    c[1] = yCoordinates[i+2];
    c[2] = zCoordinates[i+2];

    J = rho * simplex_J (zero, a, b, c);

    me += simplex_1 (J, zero, a, b, c);

    sx += simplex_x (J, zero, a, b, c);
    sy += simplex_y (J, zero, a, b, c);
    sz += simplex_z (J, zero, a, b, c);
    euler[0] += simplex_xx (J, zero, a, b, c);
    euler[3] += simplex_xy (J, zero, a, b, c);
    euler[4] += simplex_yy (J, zero, a, b, c);
    euler[6] += simplex_xz (J, zero, a, b, c);
    euler[7] += simplex_yz (J, zero, a, b, c);
    euler[8] += simplex_zz (J, zero, a, b, c);
  }

  mass = me;
  //printf("mass:%f\n", mass);
//#ifdef STATS
  //printf("sx:%f sy:%f sz:%f\n", sx, sy, sz);
//#endif
  center[0] = (sx / me);
  center[1] = (sy / me);
  center[2] = (sz / me);
//#ifdef STATS
  //printf("c %f c %f c %f\n", center[0], center[1], center[2]);
//#endif

#ifdef STATS
  //printf("euler %f %f %f %f %f %f %f %f %f\n", euler[0], euler[1], euler[2], euler[3], euler[4], euler[5], euler[6], euler[7], euler[8]);
#endif
  euler[0] -= (2*sx - center[0]*me)*center[0];
  euler[4] -= (2*sy - center[1]*me)*center[1];
  euler[8] -= (2*sz - center[2]*me)*center[2];
  euler[3] -= center[0]*sy + center[1]*sx - center[0]*center[1]*me;
  euler[6] -= center[0]*sz + center[2]*sx - center[0]*center[2]*me;
  euler[7] -= center[1]*sz + center[2]*sy - center[1]*center[2]*me;
  euler[1] = euler[3];
  euler[2] = euler[6];
  euler[5] = euler[7];

  /* convert Euler tensor to the inertia tensor */
  double trace = TRACE (euler);
  inertia[0] = trace - euler[0];
  inertia[4] = trace - euler[4];
  inertia[8] = trace - euler[8];
  inertia[1] = -euler[1];
  inertia[2] = -euler[2];
  inertia[3] = -euler[3];
  inertia[5] = -euler[5];
  inertia[6] = -euler[6];
  inertia[7] = -euler[7]; /* inertia = tr(euler)*one - euler */
//#ifdef STATS
  //printf("Inertia %e %e %e %e %e %e %e %e %e\n", inertia[0], inertia[1], inertia[2], inertia[3], inertia[4], inertia[5], inertia[6], inertia[7], inertia[8]);
//#endif
}

double crashr::operators::computeMass(
	std::vector<double>& xCoordinates,
	std::vector<double>& yCoordinates,
	std::vector<double>& zCoordinates,
    crashr::material::MaterialType material)
{

  double me=0, a[3], b[3], c[3], J;

  double zero[3];
  zero[0] = 0;
  zero[1] = 0;
  zero[2] = 0;

  int rho= int(crashr::material::materialToDensitymap.find(material)->second);

  for (unsigned i=0;i<xCoordinates.size(); i+=3)
  {
    a[0] = xCoordinates[i];
    a[1] = yCoordinates[i];
    a[2] = zCoordinates[i];

    b[0] = xCoordinates[i+1];
    b[1] = yCoordinates[i+1];
    b[2] = zCoordinates[i+1];

    c[0] = xCoordinates[i+2];
    c[1] = yCoordinates[i+2];
    c[2] = zCoordinates[i+2];

    J = rho * simplex_J (zero, a, b, c);
    me += simplex_1 (J, zero, a, b, c);
  }

  return me;
}

void crashr::operators::computeInverseInertia(
    double inertia[9],
    double inverse[9],
    bool isObject)
{
  double det;

  double a[9], x[9];

  for (int j = 0; j < 9; j++)
  {
    a[j] = inertia[j];
  }

  INVERT (a, x, det);

  if(isObject)
  {
	for (int j = 0; j < 9; j++)
	{
		inverse[j] = 0.0;
	}
  } else {
	for (int j = 0; j < 9; j++)
	{
	  inverse[j] = x[j];
	}
  }
}

double crashr::operators::simplex_J (
    double *a, double *b, double *c, double *d)
{
  double q [9], J;

  q [0] = b [0] - a [0];
  q [1] = c [0] - a [0];
  q [2] = d [0] - a [0];
  q [3] = b [1] - a [1];
  q [4] = c [1] - a [1];
  q [5] = d [1] - a [1];
  q [6] = b [2] - a [2];
  q [7] = c [2] - a [2];
  q [8] = d [2] - a [2];

  J = q [0]*q [4]*q [8] + q [3]*q [7]*q [2] + q [6]*q [1]*q [5] -
      q [6]*q [4]*q [2] - q [0]*q [7]*q [5] - q [3]*q [1]*q [8];

  return J;
}

#define TRACE(A) ((A)[0] + (A)[4] + (A)[8])
