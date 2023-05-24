/**
* @author: Elad Shoham, 205439649
*/

#include "Point.hpp"

using namespace std;
using namespace ariel;

namespace ariel {
    string Point::print() const {
        string str = "(" + to_string(x) + ", " + to_string(y) + ")\n";
        cout << str;
        return str; 
    }

    Point Point::moveTowards (const Point& p1, const Point& p2, double d) {
        if (d < 0) throw invalid_argument("Distance cant be negative");

        double realD = p1.distance(p2);
        if (realD <= d) return p2;

        double newX = p1.x + ((p2.x - p1.x) * (long double)(d / realD));
        double newY = p1.y + ((p2.y - p1.y) * (long double)(d / realD));

        return Point(newX, newY);
    }
}