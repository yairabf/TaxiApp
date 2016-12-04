
#include <cstdlib>
#include "Passenger.h"

Passenger::Passenger(const Point &source, const Point &destination) : source(source), destination(destination) {}

int Passenger::randomScore() {
    srand((unsigned int) time(NULL));
    int score = 1 + (rand()% (5- 1 +1));
    return score;
}

Point *Passenger::getSource() {
    return &source;
}

Point *Passenger::getDestination() {
    return &destination;
}
