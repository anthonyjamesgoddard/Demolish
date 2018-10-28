#include"Vertex.h"

#include<cmath>

using demolish::Vertex;

Vertex::Vertex(iREAL x,iREAL y,iREAL z)
{
    _x = x; _y = y; _z = z;
    _r = 0; _theta = 0; _phi = 0;
    _associatedSectorIndex = 0;
}

Vertex& Vertex::operator=(const Vertex& v)
{
   _x                       =     v._x;
   _y                       =     v._y;
   _z                       =     v._z;
   _r                       =     v._r;
   _theta                   =     v._theta;
   _associatedSectorIndex   =     v._associatedSectorIndex;
   return *this;
}

// lexicographic ordering
bool Vertex::operator<(const Vertex&v) const
{
    return _x < v._x ||
          (_x == v._x && _y <  v._y) ||
          (_x == v._x && _y == v._y && _z < v._z);
}


/**
 * We have not found that we need to update the radial
 * and angular component of the vector as of yet. Although,
 * we do suspect that we will need to soon. 
 */

Vertex Vertex::operator+(const Vertex&v) const
{
    iREAL X = _x + v._x, Y = _y + v._y, Z = _z + v._z;
    Vertex w = Vertex(X,Y,Z);
    return w;
}

Vertex Vertex::operator-(const Vertex&v) const
{
    iREAL X = _x - v._x, Y = _y - v._y, Z = _z - v._z;
    Vertex w = Vertex(X,Y,Z);
    return w;
}

Vertex Vertex::operator*(const iREAL&a) const
{
    iREAL X = _x*a, Y = _y*a, Z = _z*a;
    Vertex v = Vertex(X,Y,Z);
    return v;
}

iREAL Vertex::operator*(const Vertex&v) const
{
    return v._x*_x + v._y*_y + v._z*_z;
}

Vertex& Vertex::operator*=(const iREAL&a)
{
    _x*=a;_y*=a;_z*=a;
    return *this;
}

iREAL   Vertex::operator[](int         i)
{
    if(i==0)return _x;
    if(i==1)return _y;
    if(i==2)return _z;
    else return -1;
}



iREAL Vertex::norm()
{
    return std::sqrt(_x*_x+_y*_y+_z*_z);
}

void Vertex::normalise()
{
    iREAL norm = this->norm();
    _x /= norm;_y/=norm;_z/=norm;
}

