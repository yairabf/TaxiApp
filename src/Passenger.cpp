
#include <cstdlib>
#include "Passenger.h"

Passenger::Passenger(const Point &source, const Point &destination) : source(source), destination(destination) {}


int Passenger::randomScore() {
    srand((unsigned int) time(NULL));
    int score = 1 + (rand()% (5- 1 +1));
    return score;
}

const Point &Passenger::getSource() const {
    return source;
}

const Point &Passenger::getDestination() const {
    return destination;
}

using namespace std;
using namespace boost::archive;
template<class Archive>
void Passenger::serialize(Archive & ar, const unsigned int version) {
    ar & source;
    ar & destination;
}

