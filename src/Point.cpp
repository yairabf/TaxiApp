

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
Point::Point() {}

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

void Point::pointFromString(string string1) {
    int split = (int) string1.find(",");
    string strX = string1.substr(1, (unsigned long) split - 1);
    string strY = string1.substr((unsigned long) split + 1, string1.size() - 1);
    std::istringstream(strX) >> x; //i is 10 after this
    std::istringstream(strY) >> y; //i is 10 after this}
}
/**
 * overrides ==.
 * @param point is the point we are comparing to.
 * @return if they are eqaul.
*/
bool operator==(const Point& point, const Point &point1) {
    return point.getX() == point1.getX() && point.getY() == point1.getY();
}


