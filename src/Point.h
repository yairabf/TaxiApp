#ifndef ADPROG1_1_POINT_H
#define ADPROG1_1_POINT_H

#include <string>
#include <boost/serialization/access.hpp>

/**
 * class that represent point with x value and y value.
 */
class Point {
private:
    int x;
    int y;

    friend class boost::serialization::access;
    /**
     * serialization of the class
     * @param ar is the serializing object.
     * @param version is the version of serializing object.
     */
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
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

};

/**
 * overrides ==.
 * @param point is the point we are comparing to.
 * @return if they are eqaul.
 */
bool operator==(const Point &point, const Point &point1);
#endif //ADPROG1_1_POINT_H
