
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

public:
    /**
     * getter for the source point
     * @return the current location of the passenger.
     */
    const Point &getSource() const;

    /**
     *
     * @return
     */
    const Point &getDestination() const;

    /**
     *
     * @param source
     * @param destination
     */
    Passenger(const Point &source, const Point &destination);

    /**
     *
     * @return
     */
    int randomScore();
};

#endif //ADPROG1_1_PASSENGER_H


