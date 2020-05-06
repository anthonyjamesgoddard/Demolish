#include "point.h"
#include "../algo.h"

double crashr::detection::pt(double TP1[3], double TP2[3], double TP3[3], double cPoint[3], double tq[3])
{
  //191 flops
  double E0[3];
  E0[0] = TP2[0] - TP1[0];
  E0[1] = TP2[1] - TP1[1];
  E0[2] = TP2[2] - TP1[2];

  double E1[3];
  E1[0] = TP3[0] - TP1[0];
  E1[1] = TP3[1] - TP1[1];
  E1[2] = TP3[2] - TP1[2];

  double D[3];
  D[0] = TP1[0] - cPoint[0];
  D[1] = TP1[1] - cPoint[1];
  D[2] = TP1[2] - cPoint[2];

  double a = DOT(E0,E0);
  double b = DOT(E0,E1);
  double c = DOT(E1,E1);
  double d = DOT(E0,D);
  double e = DOT(E1,D);
  double f = DOT(D,D);

  double det = a*c - b*b; //% do we have to use abs here?
  double s   = b*e - c*d;
  double t   = b*d - a*e;

  double sqrDistance=0;

  if ((s+t) <= det){
	  if (s < 0){
		  if (t < 0){
			  //region4
			  if (d < 0){
				  t = 0;
				  if (-d >= a){
					  s = 1;
					  sqrDistance = a + 2*d + f;
				  }else {
					  s = -d/a;
					  sqrDistance = d*s + f;
				  }
			  }else {
				  s = 0;
				  if (e >= 0){
					  t = 0;
					  sqrDistance = f;
				  }else{
					  if (-e >= c){
						  t = 1;
						  sqrDistance = c + 2*e + f;
					  } else {
						  t = -e/c;
						  sqrDistance = e*t + f;
					  }
				  }
			  } //end of region 4
		  }else {
			  // region 3
			  s = 0;
			  if (e >= 0){
				  t = 0;
				  sqrDistance = f;
			  }else {
				  if (-e >= c){
					  t = 1;
					  sqrDistance = c + 2*e +f;
				  }else {
					  t = -e/c;
					  sqrDistance = e*t + f;
				  }
			  }
		  } //end of region 3
	  }else {
		  if (t < 0){
			  // region 5
			  t = 0;
			  if (d >= 0){
				  s = 0;
				  sqrDistance = f;
			  }else {
				  if (-d >= a){
					  s = 1;
					  sqrDistance = a + 2*d + f;// GF 20101013 fixed typo d*s ->2*d
				  }else {
					  s = -d/a;
					  sqrDistance = d*s + f;
				  }
			  }
		  }else {
			  // region 0
			  double invDet = 1/det;
			  s = s*invDet;
			  t = t*invDet;
			  sqrDistance = s*(a*s + b*t + 2*d) + t*(b*s + c*t + 2*e) + f;
		  }
	  }
  }else {
	  if (s < 0){
		  // region 2
		  double tmp0 = b + d;
		  double tmp1 = c + e;
		  if (tmp1 > tmp0){ // minimum on edge s+t=1
			  double numer = tmp1 - tmp0;
			  double denom = a - 2*b + c;
			  if (numer >= denom){
				  s = 1;
				  t = 0;
				  sqrDistance = a + 2*d + f; // GF 20101014 fixed typo 2*b -> 2*d
			  }else {
				  s = numer/denom;
				  t = 1-s;
				  sqrDistance = s*(a*s + b*t + 2*d) + t*(b*s + c*t + 2*e) + f;
			  }
		  }else {         // minimum on edge s=0
			  s = 0;
			  if (tmp1 <= 0) {
				  t = 1;
				  sqrDistance = c + 2*e + f;
			  }else {
				  if (e >= 0){
					  t = 0;
					  sqrDistance = f;
				  }else {
					  t = -e/c;
					  sqrDistance = e*t + f;
				  }
			  }
		  } //end of region 2
	  }else {
		  if (t < 0) {
			  //region6
			  double tmp0 = b + e;
			  double tmp1 = a + d;
			  if (tmp1 > tmp0){
				  double numer = tmp1 - tmp0;
				  double denom = a-2*b+c;
				  if (numer >= denom){
					  t = 1;
					  s = 0;
					  sqrDistance = c + 2*e + f;
				  }else {
					  t = numer/denom;
					  s = 1 - t;
					  sqrDistance = s*(a*s + b*t + 2*d) + t*(b*s + c*t + 2*e) + f;
				  }
			  }else {
				  t = 0;
				  if (tmp1 <= 0){
					  s = 1;
					  sqrDistance = a + 2*d + f;
				  }else {
					  if (d >= 0) {
						  s = 0;
						  sqrDistance = f;
					  }else {
						  s = -d/a;
						  sqrDistance = d*s + f;
					  }
				  }
			  }
			  //end of region 6
		  }else {
			  // region 1
			  double numer = c + e - b - d;
			  if (numer <= 0){
				  s = 0;
				  t = 1;
				  sqrDistance = c + 2*e + f;
			  }else {
				  double denom = a - 2*b + c;
				  if (numer >= denom){
					  s = 1;
					  t = 0;
					  sqrDistance = a + 2*d + f;
				  }else {
					  s = numer/denom;
					  t = 1-s;
					  sqrDistance = s*(a*s + b*t + 2*d) + t*(b*s + c*t + 2*e) + f;
				  }
			  } //end of region 1
		  }
	  }
  }

  // account for numerical round-off error
  if (sqrDistance < 0){
	  sqrDistance = 0;
  }

  tq[0] = TP1[0] + (E1[0] * t) + (E0[0] * s);
  tq[1] = TP1[1] + (E1[1] * t) + (E0[1] * s);
  tq[2] = TP1[2] + (E1[2] * t) + (E0[2] * s);

  return sqrt(sqrDistance);
}

std::vector<crashr::contact_point> crashr::detection::pointToGeometry(
double   xCoordinatesOfPointOfGeometryA,
double   yCoordinatesOfPointOfGeometryA,
double   zCoordinatesOfPointOfGeometryA,
int 		particleA,
double   epsilonA,

const double   *xCoordinatesOfPointsOfGeometryB,
const double   *yCoordinatesOfPointsOfGeometryB,
const double   *zCoordinatesOfPointsOfGeometryB,
int   			numberOfTrianglesOfGeometryB,
int				particleB,
double   			epsilonB)
{
  std::vector<crashr::contact_point> result;
  #pragma code_align(byteAlignment)
  #pragma omp simd
  for(int i=0; i<numberOfTrianglesOfGeometryB*3; i+=3)
  {
	double P[3], Q[3];

	double TP1[3], TP2[3], TP3[3];
	TP1[0] = xCoordinatesOfPointsOfGeometryB[i];
	TP1[1] = yCoordinatesOfPointsOfGeometryB[i];
	TP1[2] = zCoordinatesOfPointsOfGeometryB[i];

	TP2[0] = xCoordinatesOfPointsOfGeometryB[i+1];
	TP2[1] = yCoordinatesOfPointsOfGeometryB[i+1];
	TP2[2] = zCoordinatesOfPointsOfGeometryB[i+1];

	TP3[0] = xCoordinatesOfPointsOfGeometryB[i+2];
	TP3[1] = yCoordinatesOfPointsOfGeometryB[i+2];
	TP3[2] = zCoordinatesOfPointsOfGeometryB[i+2];

	P[0] = xCoordinatesOfPointOfGeometryA;
	P[1] = yCoordinatesOfPointOfGeometryA;
	P[2] = zCoordinatesOfPointOfGeometryA;

	double distance = crashr::detection::pt(TP1, TP2, TP3, P, Q);

	if(distance <= (epsilonA+epsilonB))
	{
	  crashr::contact_point newcontact_point(P[0], P[1], P[2],
                                            Q[0], Q[1], Q[2],false);
	  result.push_back( newcontact_point );
	}
  }
  return result;
}

