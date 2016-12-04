//
// Created by yair on 04/12/16.
//

#ifndef ADPROG1_1_PASSENGER_H
#define ADPROG1_1_PASSENGER_H


#include "Point.h"

class Passenger {
private:
    Point source;
    Point destination;

public:
    Passenger(const Point &source, const Point &destination);

    int randomScore();

    Point* getSource();

    Point* getDestination();

};


#endif //ADPROG1_1_PASSENGER_H


