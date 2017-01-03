

#include "TripInfo.h"

TripInfo::TripInfo(int id, int x_start, int y_start, int x_end, int y_end, int num_of_passenger,
                   double tariff, int start_time) : id(id), numberOfPassengers(num_of_passenger), tariff(tariff),
                                    start(new Point(x_start, y_start)), end(new Point(x_end, y_end)),
                                                    start_time(start_time) {
    route = NULL;
    done = false;
    metersPassed = 0;
}

int TripInfo::getId() const {
    return id;
}

int TripInfo::getMetersPassed() const {
    return metersPassed;
}

Point* TripInfo::getStart() {
    return start;
}

Point* TripInfo::getEnd() {
    return end;
}

int TripInfo::getNumberOfPassengers() const {
    return numberOfPassengers;
}

double TripInfo::getTarrif() const {
    return tariff;
}

void TripInfo::setRoute(std::deque<Node*> *route1) {
    route = route1;
}

std::deque<Node *> *TripInfo::getRoute() const {
    return route;
}

bool TripInfo::isDone() const {
    return done;
}

void TripInfo::setDone(bool done) {
    TripInfo::done = done;
}

TripInfo::~TripInfo() {
    delete(start);
    delete(end);
    delete(route);
}

TripInfo::TripInfo() {}

int TripInfo::getStart_time() const {
    return start_time;
}

bool TripInfo::isAssigned() const {
    return assigned;
}

void TripInfo::setAssigned(bool assigned) {
    TripInfo::assigned = assigned;
}





