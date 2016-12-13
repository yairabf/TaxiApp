

#include "TripInfo.h"

TripInfo::TripInfo(int id, int x_start, int y_start, int x_end, int y_end, int num_of_passenger,
                   double tariff) : id(id), numberOfPassengers(num_of_passenger),
                                                                   tariff(tariff),
                                    start(Point(x_start, y_start)), end(Point(x_end, y_end)) {
    route = NULL;

}

int TripInfo::getId() const {
    return id;
}

int TripInfo::getMetersPassed() const {
    return metersPassed;
}

const Point &TripInfo::getStart() const {
    return start;
}

const Point &TripInfo::getEnd() const {
    return end;
}

int TripInfo::getNumberOfPassengers() const {
    return numberOfPassengers;
}

double TripInfo::getTarrif() const {
    return tariff;
}

std::stack<Node *> *TripInfo::getRoute() const {
    return route;
}


