//
// Created by yair on 22/11/16.
//

#ifndef ADPROG1_1_POINT_H
#define ADPROG1_1_POINT_H

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

};
#endif //ADPROG1_1_POINT_H
