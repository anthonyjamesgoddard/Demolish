#pragma once

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

namespace demolish {
    namespace operators {
		iREAL computeXYZw(
			std::vector<iREAL> xCoordinates,
			std::vector<iREAL> yCoordinates,
			std::vector<iREAL> zCoordinates);
		iREAL computeXZw(
			std::vector<iREAL> xCoordinates,
			std::vector<iREAL> yCoordinates,
			std::vector<iREAL> zCoordinates);
		iREAL computeXw(
			std::vector<iREAL> xCoordinates,
			std::vector<iREAL> yCoordinates,
			std::vector<iREAL> zCoordinates);
		iREAL computeYw(
			std::vector<iREAL> xCoordinates,
			std::vector<iREAL> yCoordinates,
			std::vector<iREAL> zCoordinates);
		iREAL computeZw(
			std::vector<iREAL> xCoordinates,
			std::vector<iREAL> yCoordinates,
			std::vector<iREAL> zCoordinates);

		demolish::Vertex computeBoundaryMinVertex(
			std::vector<iREAL> xCoordinates,
			std::vector<iREAL> yCoordinates,
			std::vector<iREAL> zCoordinates);

		demolish::Vertex computeBoundaryMaxVertex(
			std::vector<iREAL> xCoordinates,
			std::vector<iREAL> yCoordinates,
			std::vector<iREAL> zCoordinates);

		std::array<iREAL, 6> computeBbox(
			std::vector<iREAL> xCoordinates,
			std::vector<iREAL> yCoordinates,
			std::vector<iREAL> zCoordinates);

		iREAL computeDiagonal(
			std::vector<iREAL> xCoordinates,
			std::vector<iREAL> yCoordinates,
			std::vector<iREAL> zCoordinates);

		iREAL computeDistanceAB(
		    demolish::Vertex A,
		    demolish::Vertex B);

		iREAL computeMin(
			  std::vector<iREAL> coordinates);

		iREAL computeMax(
			  std::vector<iREAL> coordinates);

   } 
} 
