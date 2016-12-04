

#include "Point.h"
#include <string>
#include <sstream>

using namespace std;

Point::Point(int x, int y) : x(x), y(y) {}


std::string Point::toString() {
    std::ostringstream x;
    std::ostringstream y;
    x << Point::x;
    y << Point::y;
    std::string str = "(" + x.str() + "," + y.str() + ")";
    return str;
}
/**
 * getter.
 * @return x value.
 */
int Point::getX() const {
    return x;
}
/**
 * getter.
 * @return y value.
 */
int Point::getY() const {
    return y;
}

/**
 * overrides ==.
 * @param point is the point we are comparing to.
 * @return if they are eqaul.
*/
bool operator==(const Point& point, const Point &point1) {
    return point.getX() == point1.getX() && point.getY() == point1.getY();
}
