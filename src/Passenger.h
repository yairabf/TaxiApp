
#ifndef ADPROG1_1_PASSENGER_H
#define ADPROG1_1_PASSENGER_H


#include "Point.h"

/**
 * class that represent a passenger in the world. each passenger has a source point which represent
 * the current location of the passenger' and has a destination point that represent the
 * point he wants to go.
 */
class Passenger {
private:
    Point source;
    Point destination;

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
     * getter for the source point
     * @return the current location of the passenger.
     */
    const Point &getSource() const;

    /**
     * getter.
     * @return the destination of the passenger.
     */
    const Point &getDestination() const;

    /**
     * constructor.
     * @param source is where the passenger starts.
     * @param destination where the passenger wants to drive to.
     */
    Passenger(const Point &source, const Point &destination);

    /**
     * provides a random score for the satisfaction of the passenger between 1 to 5.
     * @return the satisfaction level.
     */
    int randomScore();
};

#endif //ADPROG1_1_PASSENGER_H


