#pragma once
/**
* @author: Elad Shoham, 205439649
*/

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

namespace ariel {
    class Point {
    private:
        double x;
        double y;
    public:
        // Constructor 
        Point() : x(0), y(0) {}
        Point(double xloc, double yloc) : x(xloc), y(yloc) {}

        // Return the distance to the given Point
        double distance(const Point& other) const {return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));}
        // Print the coordinates
        string print() const;

        /*
        * Return the nearest point to the source point
        * that is not distanced more then the given distance from the target point
        * Throws string if distance < 0
        */
        static Point moveTowards (const Point&, const Point&, double);
    };
}