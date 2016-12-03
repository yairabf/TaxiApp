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
     * constructor
     * @param x the x value
     * @param y the y value
     */
    Point(int x, int y);

    /**
     * getter for the x value.
     * @return
     */
    int getX();

    /**
     * getter for the y value.
     * @return
     */
    int getY();

    /**
     * returns a string of the point in the form of "(x,y)"
     * @return string that represent the value of the point
     */
    std::string toString();

};
#endif //ADPROG1_1_POINT_H
