//
// Created by yair on 04/12/16.
//

#ifndef ADPROG1_1_PASSENGER_H
#define ADPROG1_1_PASSENGER_H


#include "Point.h"

class Passenger {
private:
    Point source;
public:
    const Point &getSource() const;

    const Point &getDestination() const;

private:
    Point destination;

public:
    Passenger(const Point &source, const Point &destination);

    int randomScore();
};

#endif //ADPROG1_1_PASSENGER_H


