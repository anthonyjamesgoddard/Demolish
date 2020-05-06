#ifndef _VERTEX
#define _VERTEX

#include"demolish.h"

#include<vector>
#include<array>
#include<iostream>

namespace demolish{
        class Vertex;
}

class demolish::Vertex
{
private:
    iREAL _x,_y,_z;             
    iREAL _r,_theta,_phi;       
    int   _associatedSectorIndex;
public:
    Vertex(){};
    Vertex(iREAL x,iREAL y, iREAL z);

    // operator overloads
    Vertex&     operator= (const Vertex&v);
    bool        operator< (const Vertex&v) const;
    Vertex      operator+ (const Vertex&v) const; 
    Vertex      operator- (const Vertex&v) const;
    Vertex      operator* (const iREAL& a) const; 
    iREAL       operator* (const Vertex&v) const;
    Vertex&     operator+=(const Vertex&v);
    Vertex&     operator*=(const iREAL& a);
    iREAL       operator[](int          i);
    // member functions
    Vertex      perpendicular();
    iREAL       norm();
    void        normalise();

    iREAL       getTheta()
    {
        return _theta;
    }
    iREAL       getPhi()
    {
        return _phi;
    }
    float getRadius()
    {
        return _r;
    }

    iREAL       getX() const {return _x;}
    iREAL       getY() const {return _y;}
    iREAL       getZ() const {return _z;}
    int         getAssociatedSectorIndex()
    {
        return _associatedSectorIndex;
    }
    void        setX(iREAL x) {_x = x;}
    void        setY(iREAL y) {_y = y;}
    void        set(iREAL x,iREAL y,iREAL z){_x = x;_y = y;_z=z;}
    void        setAssociatedSectorIndex(int i)
    {
        _associatedSectorIndex = i;
    }
    void displayProperties()
    {
        std::cout << "cartesian " << _x << " " << _y << " " << " " << _z << '\n' 
         << "polar " << _r << " " << _theta << " " << _phi << '\n' << "sector index" << _associatedSectorIndex << std::endl;
    }

};

#endif
