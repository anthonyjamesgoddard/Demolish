#pragma once

#include"crashr.h"

#include<vector>
#include<array>
#include<iostream>

namespace crashr{
        class Vertex;
}

class crashr::Vertex
{
private:
    double _x,_y,_z;             
    double _r,_theta,_phi;       
    int   _associatedSectorIndex;
public:
    Vertex(){};
    Vertex(double x,double y, double z);

    // operator overloads
    Vertex&     operator= (const Vertex&v);
    bool        operator< (const Vertex&v) const;
    Vertex      operator+ (const Vertex&v) const; 
    Vertex      operator- (const Vertex&v) const;
    Vertex      operator* (const double& a) const; 
    double       operator* (const Vertex&v) const;
    Vertex&     operator+=(const Vertex&v);
    Vertex&     operator*=(const double& a);
    double       operator[](int          i);
    // member functions
    Vertex      perpendicular();
    double       norm();
    void        normalise();

    double       getTheta()
    {
        return _theta;
    }
    double       getPhi()
    {
        return _phi;
    }
    float getRadius()
    {
        return _r;
    }

    double       getX() const {return _x;}
    double       getY() const {return _y;}
    double       getZ() const {return _z;}
    int         getAssociatedSectorIndex()
    {
        return _associatedSectorIndex;
    }
    void        setX(double x) {_x = x;}
    void        setY(double y) {_y = y;}
    void        set(double x,double y,double z){_x = x;_y = y;_z=z;}
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

namespace crashr {
    namespace operators {
		double computeXYZw(
			std::vector<double> xCoordinates,
			std::vector<double> yCoordinates,
			std::vector<double> zCoordinates);
		double computeXZw(
			std::vector<double> xCoordinates,
			std::vector<double> yCoordinates,
			std::vector<double> zCoordinates);
		double computeXw(
			std::vector<double> xCoordinates,
			std::vector<double> yCoordinates,
			std::vector<double> zCoordinates);
		double computeYw(
			std::vector<double> xCoordinates,
			std::vector<double> yCoordinates,
			std::vector<double> zCoordinates);
		double computeZw(
			std::vector<double> xCoordinates,
			std::vector<double> yCoordinates,
			std::vector<double> zCoordinates);

		crashr::Vertex computeBoundaryMinVertex(
			std::vector<double> xCoordinates,
			std::vector<double> yCoordinates,
			std::vector<double> zCoordinates);

		crashr::Vertex computeBoundaryMaxVertex(
			std::vector<double> xCoordinates,
			std::vector<double> yCoordinates,
			std::vector<double> zCoordinates);

		std::array<double, 6> computeBbox(
			std::vector<double> xCoordinates,
			std::vector<double> yCoordinates,
			std::vector<double> zCoordinates);

		double computeDiagonal(
			std::vector<double> xCoordinates,
			std::vector<double> yCoordinates,
			std::vector<double> zCoordinates);

		double computeDistanceAB(
		    crashr::Vertex A,
		    crashr::Vertex B);

		double computeMin(
			  std::vector<double> coordinates);

		double computeMax(
			  std::vector<double> coordinates);

   } 
} 
