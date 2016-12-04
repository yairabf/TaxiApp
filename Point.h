#ifndef ADPROG1_1_POINT_H
#define ADPROG1_1_POINT_H

#include <string>

/**
 * class that represent point with x value and y value.
 */
class Point {
private:
    int x;
    int y;
public:
    /**
    * getter.
    * @return x value.
    */
    int getX() const;
    /**
    * getter.
    * @return y value.
    */
    int getY() const;
    /**
     * constructor
     * @param x the x value
     * @param y the y value
     */
    Point(int x, int y);


    /**
     * returns a string of the point in the form of "(x,y)"
     * @return string that represent the value of the point
     */
    std::string toString();
    /**
     * overrides ==.
     * @param point is the point we are comparing to.
     * @return if they are eqaul.
     */
    bool operator==(const Point &point) const;
};
#endif //ADPROG1_1_POINT_H
